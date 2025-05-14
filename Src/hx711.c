/*
 * HX711.c
 *
 *  Created on: 16 nov. 2021
 *      Author: PCov3r
 */

#include <HX711.h>
#include <math.h>
#include <stdio.h>

extern UART_HandleTypeDef huart1;
//#############################################################################################
void hx711_init(hx711_t *hx711, GPIO_TypeDef *clk_gpio, uint16_t clk_pin, GPIO_TypeDef *dat_gpio, uint16_t dat_pin) {
    // Setup the pin connections with the STM Board
    hx711->clk_gpio = clk_gpio;
    hx711->clk_pin = clk_pin;
    hx711->dat_gpio = dat_gpio;
    hx711->dat_pin = dat_pin;

    GPIO_InitTypeDef gpio = {0};
    gpio.Mode = GPIO_MODE_OUTPUT_PP;
    gpio.Pull = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio.Pin = clk_pin;
    HAL_GPIO_Init(clk_gpio, &gpio);
    gpio.Mode = GPIO_MODE_INPUT;
    gpio.Pull = GPIO_PULLUP;
    gpio.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio.Pin = dat_pin;
    HAL_GPIO_Init(dat_gpio, &gpio);
}

//#############################################################################################
void set_scale(hx711_t *hx711, float Ascale, float Bscale) {
    // Set the scale. To calibrate the cell, run the program with a scale of 1, call the tare function and then the get_units function.
    // Divide the obtained weight by the real weight. The result is the parameter to pass to scale
    hx711->Ascale = Ascale;
    hx711->Bscale = Bscale;
}

//#############################################################################################
void set_gain(hx711_t *hx711, uint8_t Again, uint8_t Bgain) {
    // Define A channel's gain
    switch (Again) {
        case 128: // channel A, gain factor 128
            hx711->Again = 1;
            break;
        case 64: // channel A, gain factor 64
            hx711->Again = 3;
            break;
    }
    hx711->Bgain = 2;
}

//#############################################################################################
void set_offset(hx711_t *hx711, long offset, uint8_t channel) {
    if (channel == CHANNEL_A) hx711->Aoffset = offset;
    else hx711->Boffset = offset;
}

//############################################################################################
uint8_t shiftIn(hx711_t *hx711, uint8_t bitOrder) {
    uint8_t value = 0;
    uint8_t i;

    for (i = 0; i < 8; ++i) {
        HAL_GPIO_WritePin(hx711->clk_gpio, hx711->clk_pin, SET);
        if (bitOrder == 0)
            value |= HAL_GPIO_ReadPin(hx711->dat_gpio, hx711->dat_pin) << i;
        else
            value |= HAL_GPIO_ReadPin(hx711->dat_gpio, hx711->dat_pin) << (7 - i);
        HAL_GPIO_WritePin(hx711->clk_gpio, hx711->clk_pin, RESET);
    }
    return value;
}

//############################################################################################
bool is_ready(hx711_t *hx711) {
    if (HAL_GPIO_ReadPin(hx711->dat_gpio, hx711->dat_pin) == GPIO_PIN_RESET) {
        return 1;
    }
    return 0;
}

//############################################################################################
void wait_ready(hx711_t *hx711) {
    // Wait for the chip to become ready.
    while (!is_ready(hx711)) {
        HAL_Delay(0);
    }
}

//############################################################################################
long read(hx711_t *hx711, uint8_t channel) {
    wait_ready(hx711);
    unsigned long value = 0;
    uint8_t data[3] = {0};
    uint8_t filler = 0x00;

    noInterrupts();

    data[2] = shiftIn(hx711, 1);
    data[1] = shiftIn(hx711, 1);
    data[0] = shiftIn(hx711, 1);

    uint8_t gain = 0;
    if (channel == 0) gain = hx711->Again;
    else gain = hx711->Bgain;

    for (unsigned int i = 0; i < gain; i++) {
        HAL_GPIO_WritePin(hx711->clk_gpio, hx711->clk_pin, SET);
        HAL_GPIO_WritePin(hx711->clk_gpio, hx711->clk_pin, RESET);
    }

    interrupts();

    // Replicate the most significant bit to pad out a 32-bit signed integer
    if (data[2] & 0x80) {
        filler = 0xFF;
    } else {
        filler = 0x00;
    }

    // Construct a 32-bit signed integer
    value = ((unsigned long) (filler) << 24
        | (unsigned long) (data[2]) << 16
        | (unsigned long) (data[1]) << 8
        | (unsigned long) (data[0]));

    return (long) (value);
}

//############################################################################################
long read_average(hx711_t *hx711, int8_t times, uint8_t channel) {
    long sum = 0;
    for (int8_t i = 0; i < times; i++) {
        sum += read(hx711, channel);
        HAL_Delay(0);
    }
    return sum / times;
}

//############################################################################################
double get_value(hx711_t *hx711, int8_t times, uint8_t channel) {
    long offset = 0;
    if (channel == CHANNEL_A) offset = hx711->Aoffset;
    else offset = hx711->Boffset;
    return read_average(hx711, times, channel) - offset;
}

//############################################################################################
void tare(hx711_t *hx711, uint8_t times, uint8_t channel) {
    read(hx711, channel); // Change channel
    double sum = read_average(hx711, times, channel);
    set_offset(hx711, sum, channel);
}

//############################################################################################
void tare_all(hx711_t *hx711, uint8_t times) {
    tare(hx711, times, CHANNEL_A);
    tare(hx711, times, CHANNEL_B);
}

//############################################################################################
float get_weight(hx711_t *hx711, int8_t times, uint8_t channel) {
    // Read load cell
    read(hx711, channel);
    float scale = 0;
    if (channel == CHANNEL_A) scale = hx711->Ascale;
    else scale = hx711->Bscale;
    return get_value(hx711, times, channel) / scale;
}

void init_weight(hx711_t *hx711, GPIO_TypeDef *clk_gpio, uint16_t clk_pin, GPIO_TypeDef *dat_gpio, uint16_t dat_pin) {
    char buffer[128] = {0};

    sprintf(buffer, "HX711 initialization\n\r");
    HAL_UART_Transmit(&huart1, (uint8_t *) (buffer), sizeof(buffer), 100);

    /* Initialize the hx711 sensors */
    hx711_init(hx711, clk_gpio, clk_pin, dat_gpio, dat_pin);

    /* Configure gain for each channel (see datasheet for details) */
    set_gain(hx711, 64, 32);

    float gain = 1;
    /* Set HX711 scaling factor (see README for procedure) */
    set_scale(hx711, gain, 96);
    tare_all(hx711, 10);
    // float tmp = 0;
    // int tryTimes = 0;
    // while (!measure_weight(*hx711, &tmp)) {
    //     if (tryTimes++ > 10) {
    //         sprintf(buffer, "HX711 module initialization failed\n\r");
    //         HAL_UART_Transmit(&huart1, (uint8_t *) (buffer), sizeof(buffer), 100);
    //         return;
    //     }
    // }
    // /* Tare weight */
    // set_offset(hx711, (long) (tmp * gain), CHANNEL_A);

    sprintf(buffer, "HX711 module has been initialized\n\r");
    HAL_UART_Transmit(&huart1, (uint8_t *) (buffer), sizeof(buffer), 100);
}

int middle(float a, float b, float c, float *medianOut) {
    // 计算平均值
    const float avg = (a + b + c) / 3.0f;

    // 计算最大偏差
    float dev_a = fabsf(a - avg);
    float dev_b = fabsf(b - avg);
    float dev_c = fabsf(c - avg);

    float maxDev = dev_a;
    if (dev_b > maxDev) maxDev = dev_b;
    if (dev_c > maxDev) maxDev = dev_c;

    // 检查偏差是否超过平均值的10%
    int exceedsThreshold;
    if (fabsf(avg) < 1e-6f) {
        // 处理平均值接近零的情况
        exceedsThreshold = !(fabsf(a) < 1e-6f && fabsf(b) < 1e-6f && fabsf(c) < 1e-6f);
    } else {
        exceedsThreshold = (maxDev > 0.1f * fabsf(avg));
    }

    // 如果偏差超过10%且需要返回中位数
    if (exceedsThreshold && medianOut != NULL) {
        // 使用原始逻辑计算中位数
        if (a >= b) {
            if (b >= c) *medianOut = b;
            else if (a >= c) *medianOut = c;
            else *medianOut = a;
        } else {
            if (a >= c) *medianOut = a;
            else if (b >= c) *medianOut = c;
            else *medianOut = b;
        }
    }

    // 如果偏差超过10%返回1(true)，否则返回0(false)
    return exceedsThreshold;
}

bool measure_weight(hx711_t hx711, float *weight) {
    float a = 0, b = 0, c = 0;
    const int max_attempts = 5; // Maximum attempts to avoid infinite loop

    for (int attempt = 0; attempt < max_attempts; attempt++) {
        // Get three weight readings with delays
        a = get_weight(&hx711, 1, CHANNEL_A);
        HAL_Delay(1);
        b = get_weight(&hx711, 1, CHANNEL_A);
        HAL_Delay(1);
        c = get_weight(&hx711, 1, CHANNEL_A);

        // Find max and min values
        float max_val = a;
        if (b > max_val) max_val = b;
        if (c > max_val) max_val = c;

        float min_val = a;
        if (b < min_val) min_val = b;
        if (c < min_val) min_val = c;

        // Check if difference exceeds 20%
        if (min_val != 0 && (max_val - min_val) > (min_val * 0.2)) {
            // Values differ by more than 20%, try again
            HAL_Delay(1); // Wait a bit longer before retry
        } else {
            break;
        }
    }

    // If we've reached maximum attempts, return the median anyway
    float median = 0;
    if (middle(a, b, c, &median)) {
        *weight = median;
        return true;
    }
    *weight = median;
    return true  ;
    // return false;
}
