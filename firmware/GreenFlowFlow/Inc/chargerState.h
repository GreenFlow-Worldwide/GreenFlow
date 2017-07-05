#ifndef _CHARGER_STATE_H_ 
#define _CHARGER_STATE_H_
#include "stdint.h"

uint8_t cs_getUpdatedHubCharger(uint8_t * chargerFlag);
uint8_t cs_initChargerState();

#endif