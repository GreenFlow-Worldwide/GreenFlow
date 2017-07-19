/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define backButton_Pin GPIO_PIN_0
#define backButton_GPIO_Port GPIOA
#define backButton_EXTI_IRQn EXTI0_1_IRQn
#define downButton_Pin GPIO_PIN_1
#define downButton_GPIO_Port GPIOA
#define downButton_EXTI_IRQn EXTI0_1_IRQn
#define upButton_Pin GPIO_PIN_4
#define upButton_GPIO_Port GPIOA
#define upButton_EXTI_IRQn EXTI4_15_IRQn
#define nextbutton_Pin GPIO_PIN_5
#define nextbutton_GPIO_Port GPIOA
#define nextbutton_EXTI_IRQn EXTI4_15_IRQn
#define ADC_Activate_Pin GPIO_PIN_4
#define ADC_Activate_GPIO_Port GPIOC
#define LED_Red_Pin GPIO_PIN_0
#define LED_Red_GPIO_Port GPIOB
#define LED_Blue_Pin GPIO_PIN_1
#define LED_Blue_GPIO_Port GPIOB
#define LED_Green_Pin GPIO_PIN_2
#define LED_Green_GPIO_Port GPIOB
#define LCD_Clock_Pin GPIO_PIN_10
#define LCD_Clock_GPIO_Port GPIOB
#define Charger_FLT_Pin GPIO_PIN_12
#define Charger_FLT_GPIO_Port GPIOB
#define Charger_FLT_EXTI_IRQn EXTI4_15_IRQn
#define Charger_STAT_Pin GPIO_PIN_13
#define Charger_STAT_GPIO_Port GPIOB
#define Charger_STAT_EXTI_IRQn EXTI4_15_IRQn
#define Charger_ADPP_Pin GPIO_PIN_14
#define Charger_ADPP_GPIO_Port GPIOB
#define Charger_ADPP_EXTI_IRQn EXTI4_15_IRQn
#define LCD_Data_Pin GPIO_PIN_15
#define LCD_Data_GPIO_Port GPIOB
#define LCD_LED_Pin GPIO_PIN_6
#define LCD_LED_GPIO_Port GPIOC
#define LED_LCK_Pin GPIO_PIN_7
#define LED_LCK_GPIO_Port GPIOC
#define LCD__OE_Pin GPIO_PIN_8
#define LCD__OE_GPIO_Port GPIOC
#define uartTX_Pin GPIO_PIN_9
#define uartTX_GPIO_Port GPIOA
#define uartRx_Pin GPIO_PIN_10
#define uartRx_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
