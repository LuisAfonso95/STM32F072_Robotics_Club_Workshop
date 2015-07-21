 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"

#ifdef USE_STM320518_EVAL
 #include "stm320518_eval.h"
 #include "stm320518_eval_lcd.h"
#endif /* USE_STM320518_EVAL */

#ifdef USE_STM32072B_EVAL
 #include "stm32072b_eval.h"
 #include "stm32072b_eval_lcd.h"
#endif /* USE_STM32072B_EVAL */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
