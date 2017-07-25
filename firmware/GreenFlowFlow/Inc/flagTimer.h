#ifndef _FLAG_TIMER_H_ 
#define _FLAG_TIMER_H_

#include <stdint.h>
#include <stdbool.h>
uint8_t ft_initFlag();
uint8_t ft_checkTimerFlag(bool * isTimerFlag);
uint8_t ft_checkResetVolumeFlag(const bool newVolume, bool * isResetVolumeFlag);

#endif