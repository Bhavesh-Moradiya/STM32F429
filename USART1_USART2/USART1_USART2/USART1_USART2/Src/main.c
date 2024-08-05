#include "stm32f4xx_hal.h"

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

int i = 0;

uint8_t Temp1[1], Temp2[1];
uint8_t data_receive_USART1[10], data_receive_USART2[10];

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);

void send_USART1(uint8_t *send);
void receive_USART1(void);
void send_USART2(uint8_t *send);
void receive_USART2(void);

//////////////////////////////////USART1////////////////////////////////////////
void send_USART1(uint8_t *send)
{
  i = 0;
  while(*send != '\0')
  {  
    HAL_UART_Transmit(&huart1, send++, 1, 100);
    receive_USART2();
  }
}

void receive_USART1(void)
{
  HAL_UART_Receive(&huart1, Temp1, 1, 100);
  data_receive_USART1[i] = Temp1[0];
  i++;
  if(i >= 10)
  {
    i = 0;
  }
}

//////////////////////////////////USART2////////////////////////////////////////
void send_USART2(uint8_t *send)
{
  i = 0;
  while(*send != '\0')
  {  
    HAL_UART_Transmit(&huart2, send++, 1, 100);
    receive_USART1();
  }
}

void receive_USART2(void)
{
  HAL_UART_Receive(&huart2, Temp2, 1, 100);
  data_receive_USART2[i] = Temp2[0];
  i++;
  if(i >= 10)
  {
    i = 0;
  }
}

////////////////////////////////MAIN BODY///////////////////////////////////////
int main(void)
{
  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();

  //__HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
  while (1)
  {
    send_USART1("Good Luck");
    //due to PA10 is possibly use on board and due to it was embbed receive task can not work
    //thus it's need to configure on alternate pin 
  }
}

void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  __PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 96;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

void MX_USART1_UART_Init(void)
{
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_8;
  HAL_UART_Init(&huart1);
}

void MX_USART2_UART_Init(void)
{
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_8;
  HAL_UART_Init(&huart2);

}

void MX_GPIO_Init(void)
{
  __GPIOA_CLK_ENABLE();
}

#ifdef USE_FULL_ASSERT

void assert_failed(uint8_t* file, uint32_t line)
{
}

#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
