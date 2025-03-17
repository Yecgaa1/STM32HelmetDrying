#include "stm32g4xx_hal.h"
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2))
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr))
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum))

#define PEout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出
#define PEin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入
#define HX711_SCK_01 PEout(1)// PA1
#define HX711_DOUT_01 PEin(0)// PA0
#define GPIOA_ODR_Addr    (GPIOA_BASE+20) //0x40021014
#define GPIOA_IDR_Addr    (GPIOA_BASE+16) //0x40021010

#define CPU_FREQUENCY_MHZ    160		// 定义自己STM32的主频

//延迟us函数
void delay_us(__IO uint32_t delay)
{
  int last, curr, val;
  int temp;

  while (delay != 0)
  {
    temp = delay > 900 ? 900 : delay;
    last = SysTick->VAL;
    curr = last - CPU_FREQUENCY_MHZ * temp;
    if (curr >= 0)
    {
      do
      {
        val = SysTick->VAL;
      }
      while ((val < last) && (val >= curr));
    }
    else
    {
      curr += CPU_FREQUENCY_MHZ * 1000;
      do
      {
        val = SysTick->VAL;
      }
      while ((val <= last) || (val > curr));
    }
    delay -= temp;
  }
}


unsigned long HX711_Read_01()
{
  unsigned long count;
  unsigned char i;

  // HX711_SCK_01=0; //拉低时钟引脚
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0,GPIO_PIN_SET);
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
  count=0;
  delay_us(1);
  // while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)==GPIO_PIN_SET){}
  for(i=0;i<24;i++)
  {
    // HX711_SCK_01=1;
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
    count=count<<1;
    delay_us(1);
    // HX711_SCK_01=0;
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
    if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0)==GPIO_PIN_SET) count++;
    delay_us(1);
  }
  // HX711_SCK_01=1;
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
  count=count^0x800000;//第25个脉冲信号到来，进行数据转换
  //获得24位的数据，对0x800000异或相当于把最高位取反。
  //把符号位当做有效位，防止突然出现负值波动
  delay_us(1);
  // HX711_SCK_01=0;
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
  return(count);
}

float HX711_GapValue=1000.0;
float Weight_Maopi=100;
float Get_Weight()
{
  float Weight = 0;
  unsigned long HX711_Real_Weight = HX711_Read_01();
  if(HX711_Real_Weight > Weight_Maopi)
  {
    Weight = HX711_Real_Weight - Weight_Maopi;

    Weight = (float)(Weight/HX711_GapValue);
  }
  return Weight;
}


