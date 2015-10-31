#include "stm32f4xx_hal.h"
#include "4_bit_lcd.h"

void delay(int ticks) //us seviyesinde beklme suresi

{

while(ticks--);

}

void lcd_init() //lcd ayarlai set ediliyor

{

CMD_PORT &= ~(LCD_E); //LCD_E = 0; //Enable 0 la

CMD_PORT &= ~(LCD_RS); //LCD_RS = 0; //yazmaya hazirlan

DelayMS(30); //BASLAMADAN ÖNCE STABILIZASYON AYARI

LCD_NYB(0x30,0); //BASLAMA SATIRI

DelayMS(5);

LCD_NYB(0x30,0); //BASLAMA SATIRI

DelayMS(1);

LCD_DATA(0x02,0); //4 BIT GÖNDERILECEK HAZIRLAN, 1 lin


LCD_DATA(0x28,0); //4 BIT GÖNDERILECEK HAZIRLAN, 2 line and 5*10 font

LCD_DATA(0x0c,0); //4 BIT GÖNDERILECEK HAZIRLAN, 2 line and 5*7 font

LCD_DATA(0x01,0); //EKRANI TEMIZLE

LCD_DATA(0x06,0); //move cursor right after write

}

//——————————————————————————–//

void LCD_DATA(unsigned char data,unsigned char type){

WaitLCDBusy(); //MESGUL OLABILIR BIRAZ GECIKME KOYDUK

if(type == CMD){

CMD_PORT &= ~(LCD_RS); //KOMUT MOD

} else {

CMD_PORT |= LCD_RS; //KARAKTER/DATA MOD

}

LCD_NYB(data>>4,type); //WRITE THE UPPER NIBBLE

LCD_NYB(data,type); //WRITE THE LOWER NIBBLE

}

//——————————————————————————–//

void WaitLCDBusy(void){

DelayMS(2); //DELAY 1 MILISANIYE

}

//————————————————————————-——-//

void LCD_NYB(unsigned char nyb,unsigned char type){

DATA_PORT &= DATA_CLR; //LCD_PORT &= 0xF0; //CLEAR LOWER PORT NIBBLE

DATA_PORT |= (nyb<<DATA); //LCD_PORT |= (nyb & 0x0F); //SATIR BILGISI GÖDNER

if(type == CMD){

CMD_PORT &= ~(LCD_RS); //KOMUT MOD

} else {

CMD_PORT |= LCD_RS; //KARAKTER/DATA MOD

}

CMD_PORT |= LCD_E; //LCD_E = 1; //AKTIF LCD DATA LINE

delay(100);

CMD_PORT &= ~(LCD_E); //LCD_E = 0; //DEAKTIF LCD DATA LINE

}

//————————————————————————-——-//

void LCD_STR(const char *text){ // lcd 1. satir yazmak icin

while(*text){

LCD_DATA(*text++,1);

}

}

void LCD_STR2(unsigned char *text){ //lcd 2. satir için yaz

while(*text)

{

LCD_DATA(*text++,1);

}

}

//——————————————————————————–//

void LCD_LINE(char line){ //lcd goto yerine line olarak belirledik

switch(line){

case 0:

case 1:

LCD_DATA(LINE1,0);

break;

case 2:

LCD_DATA(LINE2,0);

break;

}

}

//——————————————————————————–//

//——————————————————————————–//

void DelayMS(unsigned int ms){

unsigned int x;

for(x=0;x<ms;x++)

delay(600);

}


void initDiscovery(void)

{

RCC->CFGR = RCC_CFGR_SW_HSE;

RCC->AHB1ENR = RCC_AHB1ENR_GPIOAEN|RCC_AHB1ENR_GPIOCEN;

RCC->CR |= RCC_CR_HSEON;

while((RCC->CR & RCC_CR_HSERDY)==0);

GPIOC->MODER=GPIO_MODER_MODER6_0|GPIO_MODER_MODER7_0|GPIO_MODER_MODER8_0|GPIO_MODER_MODER9_0;

GPIOA->MODER=GPIO_MODER_MODER8_0|GPIO_MODER_MODER9_0;

GPIOC->OSPEEDR = GPIO_OSPEEDER_OSPEEDR6_1 |

GPIO_OSPEEDER_OSPEEDR7_1 | GPIO_OSPEEDER_OSPEEDR8_1 | GPIO_OSPEEDER_OSPEEDR9_1;

GPIOA->OSPEEDR = GPIO_OSPEEDER_OSPEEDR8_1 | GPIO_OSPEEDER_OSPEEDR9_1;

}

int main()

{

initDiscovery();

lcd_init();

DelayMS(3);

LCD_LINE(1);

LCD_STR((const char*)"STM32F4 Discovery");

DelayMS(100);

LCD_LINE(2);

LCD_STR((const char*)"Kaan Kandemir");

DelayMS(100);

while(1)

{

}

}

uint16_t EVAL_AUDIO_GetSampleCallBack(void)

{

return 0; // ses çipini kullaniyorsaniz tek sample veriyi burada return ile döndürün.

}

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size)

{

return; // ses çipini kullaniyorsaniz burada çipe veri aktarimi DMA sona ermis

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  __PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1
                              |RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __GPIOH_CLK_ENABLE();
  __GPIOC_CLK_ENABLE();
  __GPIOA_CLK_ENABLE();

  /*Configure GPIO pins : PC6 PC7 PC8 PC9 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA8 PA9 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
