#define F_CPU  8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "SENSOR.h"


int main(void)
{	
  unsigned int status_sens[8] = {0};
	unsigned char calibration_arr[8] = {0};
	
	calibration(calibration_arr);
	int eqeq = 0;
	while (1) 
  {
	  sensor_scan(status_sens, calibration_arr);
		eqeq += incod(status_sens);  //Возвращает -1, 0, 1 в зависимости от определённого ею движения
		
  }
}

