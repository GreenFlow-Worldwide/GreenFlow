#ifndef _GRAB_DATA_H_
#define _GRAB_DATA_H_

typedef struct
{
  double volume;
  char flowFlags;
  char hubCharger;
  char hubBattery;

}gd_lcdData;

char gd_getDisplayData(gd_lcdData * displayData);
#endif