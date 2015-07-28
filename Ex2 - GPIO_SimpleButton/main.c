
/*
      
      GPIO_SimpleButton for STM32F072RB nucleo board with Standard Peripheral
 Library
      
      This example toggles the LED everytime you press the button.

Outputs:
      PA5 - Green LED on board

Inputs:
      PC13 - On board user button (the blue one)

  Uses template "Custom_Template1"

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

// This is to toggle the LED
uint32_t LED_State; 
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
  
  GPIO_InitTypeDef GPIO_InitStructure;

  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f0xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f0xx.c file
     */ 
      
  /* Add your application code here
     */
  
  /* Configures the Systick to interrupt every 1ms */
  SystickConfigure();
  
  /* GPIOC Periph clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE); 
  
  /* Configure PA5 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  
  /*
    Button pin configuration.
    Complete it yourself to see if you understood the previous example.1
  */
  RCC_AHBPeriphClockCmd(_______, ENABLE); //Enable the clock for GPIO module
  
  /* Configure button pin in input mode with pull up */
  GPIO_InitStructure.GPIO_Pin = _______;//which pin?
  GPIO_InitStructure.GPIO_Mode = _______; // Set as input
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // doesn't really matter
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //Just set to the maximum
  GPIO_InitStructure.GPIO_PuPd = _______; // Set to have a pull-up
  GPIO_Init(_______, &GPIO_InitStructure); //What GPIO module is it?
  
  //Turn off the LED while waiting for the first button press
  LED_State = 0;
  GPIO_WriteBit(GPIOA,GPIO_Pin_5,LED_State);
  
  
  /* Infinite loop */
  while (1)
  {
     uint32_t Button_State;
     do{
           //This is how you 1 input state.
           Button_State = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13);
     }while(Button_State != 0);
     
     LED_State ^= 1; // this will toggle the variable between 1 and 0.
     GPIO_WriteBit(GPIOA,GPIO_Pin_5,LED_State);
     
     do{
           Button_State = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13);
     }while(Button_State == 0);
     Delay(100);
     
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
