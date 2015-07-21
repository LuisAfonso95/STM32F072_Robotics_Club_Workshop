/*
  GPIO_LEDToggle
  This blinks the On-board LED on PA5 for STM32F072RB nucleo board with
Standard Peripheral Library

Outputs:
      PA5 - Green LED on board
    
A little exercise:
      The debuging features of this MCU and this IDE are very usefull!!
      When in debug go to "View->Live Watch". In there add the variable 
     "time_delay". You should be able to see the value of the variable (by
     default it should be 1000). 
      Start the code and you should see the LED blink every 1 second. Try click 
     on the "time_delay" value and you should be able to change it. Change it to
     500 and you should see the LED now blink every 0.5s. Try out other value.

  

  Luís Afonso
*/

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup STM32F0xx_StdPeriph_Templates
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

volatile uint32_t Millis =0;

/* This variable is used to control the LED blink rate */
uint32_t time_delay = 1000;

/* Private function prototypes -----------------------------------------------*/
void Delay(__IO uint32_t nTime);
void SystickConfigure(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */


int main(void)
{
  

  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f0xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f0xx.c file
     */ 
      
  
  /* Configures the Systick to interrupt every 1ms */
  SystickConfigure();
  
  /* GPIOA Periph clock enable
      Remember to enable the clock
      All GPIO are on the AHB bus so use the AHB function. Later you will see
    the other busses.
  */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE); 
  
  /* Configure PA5 in output pushpull mode
      This is how you will mostly configure any peripheral.
      There's a struct for each peripheral initialization.
      You can consult the manual or the source code for each peripheral.
      After seting up the configs on the struct you call a Init function.      
  */
  GPIO_InitTypeDef GPIO_InitStructure;
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; // <- this is the pins to configure
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT; // <- Mode like input, output, alternate and analog
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // <- this is the outpu type, push-pull or open drain
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // <- the interface speed, usually this setup is good
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; // no need for pull-ups or pull-downs
  GPIO_Init(GPIOA, &GPIO_InitStructure); // all set up on the struct, now configure GPIO A with those configs.
  /* Infinite loop */
  while (1)
  {
     //This function sets to 1 or 0 a single pin.
     GPIO_WriteBit(GPIOA,GPIO_Pin_5,Bit_SET);
     //This is the function to create delays in milliseconds.
     Delay(time_delay);
     GPIO_WriteBit(GPIOA,GPIO_Pin_5,Bit_RESET);
     Delay(time_delay);
  }
}







/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{ 
  uint32_t _time = Millis;

  while(Millis- _time < nTime);
}

void SystickConfigure(){
     /* Setup SysTick Timer for 1 msec interrupts.
     ------------------------------------------
    1. The SysTick_Config() function is a CMSIS function which configure:
       - The SysTick Reload register with value passed as function parameter.
       - Configure the SysTick IRQ priority to the lowest value (0x0F).
       - Reset the SysTick Counter register.
       - Configure the SysTick Counter clock source to be Core Clock Source (HCLK).
       - Enable the SysTick Interrupt.
       - Start the SysTick Counter.
    
    2. You can change the SysTick Clock source to be HCLK_Div8 by calling the
       SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8) just after the
       SysTick_Config() function call. The SysTick_CLKSourceConfig() is defined
       inside the misc.c file.

    3. You can change the SysTick IRQ priority by calling the
       NVIC_SetPriority(SysTick_IRQn,...) just after the SysTick_Config() function 
       call. The NVIC_SetPriority() is defined inside the core_cm0.h file.

    4. To adjust the SysTick time base, use the following formula:
                            
         Reload Value = SysTick Counter Clock (Hz) x  Desired Time base (s)
    
       - Reload Value is the parameter to be passed for SysTick_Config() function
       - Reload Value should not exceed 0xFFFFFF
   */
  if (SysTick_Config(SystemCoreClock / 1000))
  { 
    /* Capture error */ 
    while (1);
  }  
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
