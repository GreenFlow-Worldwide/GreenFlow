ifndef _FLAG_TIMER_H_ 
#define _FLAG_TIMER_H_

#include <stdint.h>
#include <stdbool.h>
uint8_t ft_initFlag(TIM_HandleTypeDef * TimerHandler);
uint8_t ft_checkTimerFlag(bool * isUpdateScreenFlag)

#endif