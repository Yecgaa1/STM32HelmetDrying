/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <retarget.h>
#include <stdbool.h>

#include "stm32g4xx_hal_uart.h"
#include "TJCScreen.h"
#include "Work.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_rx;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int recLen = 100;
char rec[100] = {0};
volatile bool nowExit[6];
volatile bool isWorking = {false};
static float YuZhi = 1000.0f;

void Check() {
    if (HAL_GPIO_ReadPin(IN1_GPIO_Port, IN1_Pin) == GPIO_PIN_RESET) {
        nowExit[0] = true;
        TJCSendAnyProperty("toukui1", "bco", "63488");
    } else {
        nowExit[0] = false;
        TJCSendAnyProperty("toukui1", "bco", "65535");
    }
    if (HAL_GPIO_ReadPin(IN2_GPIO_Port, IN2_Pin) == GPIO_PIN_RESET) {
        nowExit[1] = true;
        TJCSendAnyProperty("toukui2", "bco", "63488");
    } else {
        nowExit[1] = false;
        TJCSendAnyProperty("toukui2", "bco", "65535");
    }
    if (HAL_GPIO_ReadPin(IN3_GPIO_Port, IN3_Pin) == GPIO_PIN_RESET) {
        nowExit[2] = true;
        TJCSendAnyProperty("toukui3", "bco", "63488");
    } else {
        nowExit[2] = false;
        TJCSendAnyProperty("toukui3", "bco", "65535");
    }
    if (HAL_GPIO_ReadPin(IN4_GPIO_Port, IN4_Pin) == GPIO_PIN_RESET) {
        nowExit[3] = true;
        TJCSendAnyProperty("toukui4", "bco", "63488");
    } else {
        nowExit[3] = false;
        TJCSendAnyProperty("toukui4", "bco", "65535");
    }
    if (HAL_GPIO_ReadPin(IN5_GPIO_Port, IN5_Pin) == GPIO_PIN_RESET) {
        nowExit[4] = true;
        TJCSendAnyProperty("toukui5", "bco", "63488");
    } else {
        nowExit[4] = false;
        TJCSendAnyProperty("toukui5", "bco", "65535");
    }
    if (HAL_GPIO_ReadPin(IN6_GPIO_Port, IN6_Pin) == GPIO_PIN_RESET) {
        nowExit[5] = true;
        TJCSendAnyProperty("toukui6", "bco", "63488");
    } else {
        nowExit[5] = false;
        TJCSendAnyProperty("toukui6", "bco", "65535");
    }
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_DMA_Init();
    MX_USART1_UART_Init();
    MX_USART2_UART_Init();
    /* USER CODE BEGIN 2 */
    __HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE);
    HAL_UART_Receive_DMA(&huart2, (uint8_t *) rec, recLen);

    HAL_GPIO_WritePin(Hot0_GPIO_Port, Hot0_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(Hot1_GPIO_Port, Hot1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(Hot2_GPIO_Port, Hot2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(Hot3_GPIO_Port, Hot3_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(Hot4_GPIO_Port, Hot4_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(Hot5_GPIO_Port, Hot5_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(Hot6_GPIO_Port, Hot6_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(Light1_GPIO_Port, Light1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(Light2_GPIO_Port, Light2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(Light3_GPIO_Port, Light3_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(Light4_GPIO_Port, Light4_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(Light5_GPIO_Port, Light5_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(Light6_GPIO_Port, Light6_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(DoorLight_GPIO_Port, DoorLight_Pin, GPIO_PIN_SET);
    HAL_Delay(1000);
    HAL_GPIO_WritePin(Hot0_GPIO_Port, Hot0_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Hot1_GPIO_Port, Hot1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Hot2_GPIO_Port, Hot2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Hot3_GPIO_Port, Hot3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Hot4_GPIO_Port, Hot4_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Hot5_GPIO_Port, Hot5_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Hot6_GPIO_Port, Hot6_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DoorLight_GPIO_Port, DoorLight_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(Light1_GPIO_Port, Light1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Light2_GPIO_Port, Light2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Light3_GPIO_Port, Light3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Light4_GPIO_Port, Light4_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Light5_GPIO_Port, Light5_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(Light6_GPIO_Port, Light6_Pin, GPIO_PIN_RESET);
    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    RetargetInit(&huart1);
    TJCScreenInit(&huart2);
    while (1) {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
        HAL_Delay(200);
        Check();
    }
    /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
    */
    HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV3;
    RCC_OscInitStruct.PLL.PLLN = 85;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
    RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
        | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK) {
        Error_Handler();
    }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void) {
    /* USER CODE BEGIN USART1_Init 0 */

    /* USER CODE END USART1_Init 0 */

    /* USER CODE BEGIN USART1_Init 1 */

    /* USER CODE END USART1_Init 1 */
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
    huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    if (HAL_UART_Init(&huart1) != HAL_OK) {
        Error_Handler();
    }
    if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK) {
        Error_Handler();
    }
    if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK) {
        Error_Handler();
    }
    if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK) {
        Error_Handler();
    }
    /* USER CODE BEGIN USART1_Init 2 */

    /* USER CODE END USART1_Init 2 */
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void) {
    /* USER CODE BEGIN USART2_Init 0 */

    /* USER CODE END USART2_Init 0 */

    /* USER CODE BEGIN USART2_Init 1 */

    /* USER CODE END USART2_Init 1 */
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
    huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    if (HAL_UART_Init(&huart2) != HAL_OK) {
        Error_Handler();
    }
    if (HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK) {
        Error_Handler();
    }
    if (HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK) {
        Error_Handler();
    }
    if (HAL_UARTEx_DisableFifoMode(&huart2) != HAL_OK) {
        Error_Handler();
    }
    /* USER CODE BEGIN USART2_Init 2 */

    /* USER CODE END USART2_Init 2 */
}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void) {
    /* DMA controller clock enable */
    __HAL_RCC_DMAMUX1_CLK_ENABLE();
    __HAL_RCC_DMA1_CLK_ENABLE();
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    /* USER CODE BEGIN MX_GPIO_Init_1 */
    /* USER CODE END MX_GPIO_Init_1 */

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOC, Light1_Pin | Light2_Pin | Light3_Pin | Light4_Pin
                      | Light5_Pin | Light6_Pin | Beep_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOB, Hot1_Pin | Hot2_Pin | Hot3_Pin | Hot4_Pin
                      | Hot5_Pin | Hot6_Pin | Hot0_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(DoorLight_GPIO_Port, DoorLight_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pins : Light1_Pin Light2_Pin Light3_Pin Light4_Pin
                             Light5_Pin Light6_Pin Beep_Pin */
    GPIO_InitStruct.Pin = Light1_Pin | Light2_Pin | Light3_Pin | Light4_Pin
        | Light5_Pin | Light6_Pin | Beep_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /*Configure GPIO pins : IN1_Pin IN2_Pin IN3_Pin IN4_Pin */
    GPIO_InitStruct.Pin = IN1_Pin | IN2_Pin | IN3_Pin | IN4_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pins : IN5_Pin IN6_Pin */
    GPIO_InitStruct.Pin = IN5_Pin | IN6_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /*Configure GPIO pins : Hot1_Pin Hot2_Pin Hot3_Pin Hot4_Pin
                             Hot5_Pin Hot6_Pin Hot0_Pin */
    GPIO_InitStruct.Pin = Hot1_Pin | Hot2_Pin | Hot3_Pin | Hot4_Pin
        | Hot5_Pin | Hot6_Pin | Hot0_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /*Configure GPIO pin : DoorIN_Pin */
    GPIO_InitStruct.Pin = DoorIN_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(DoorIN_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pin : DoorLight_Pin */
    GPIO_InitStruct.Pin = DoorLight_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(DoorLight_GPIO_Port, &GPIO_InitStruct);

    /* EXTI interrupt init*/
    HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

    /* USER CODE BEGIN MX_GPIO_Init_2 */
    /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
volatile bool isBeeping = false;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == DoorIN_Pin) {
        if (HAL_GPIO_ReadPin(DoorIN_GPIO_Port,DoorIN_Pin) == GPIO_PIN_RESET) {
            //有人开门
            if (isWorking) {
                Stop();
                TJCSendAny("noOpen.en=1");
                TJCSendAny("WorkingTIM.en=0");
                TJCSendTxt("t5", "继续");
                isBeeping = true;
                HAL_GPIO_WritePin(Beep_GPIO_Port,Beep_Pin, GPIO_PIN_SET);
            }
        } else if (HAL_GPIO_ReadPin(DoorIN_GPIO_Port,DoorIN_Pin) == GPIO_PIN_SET) {
            if (isBeeping) {
                //关门了
                isBeeping = false;
                HAL_GPIO_WritePin(Beep_GPIO_Port,Beep_Pin, GPIO_PIN_RESET);
            }
        }
        __HAL_GPIO_EXTI_CLEAR_IT(DoorIN_Pin);
    }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void) {
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
