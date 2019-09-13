#include "SENSOR.h"

void calibration(unsigned char * compa_arr)
{
	signed char sensor_pin;
	
	cli();
	for(signed char j = 0; j < 3; j++)
	{
		sensor_pin = FIRST;
		for (signed char i = 0; i < ALL_SENS; i++)
		{
			compa_arr[i] += charge(sensor_pin);
			sensor_pin++;
		}
	}
	for(signed char q = 0; q < ALL_SENS; q++)
		compa_arr[q] = compa_arr[q] / 3 + 1;
}



signed char incod(unsigned int *mass)
{
	signed char j = 0;
	signed char i = 0;
	static char old = SENS + 1;
	signed char mai = 0;
	signed char index_max = 0;
	
	
	mai = mass[0];
	for (signed char q = 0; q < SENS; q++)
	{
		if(mass[q] >= mai)
		{
			mai = mass[q];
			index_max = q;
		}	
	}

	if(mai < 60)
		return 0;
		
	i = index_max + 1;
	j = index_max - 1;		
	
	if(index_max == SENS - 1)
		i = FIRST;
	else if(index_max == FIRST)
		j = SENS - 1;

	if(index_max != old && mass[index_max] > mass[i] && mass[i] > BORDER)
	{
		old = index_max;
		mass[index_max] = 0;
		return 1;
	}	
	else if(index_max != old && mass[index_max] > mass[j] && mass[j] > BORDER)
	{
		old = index_max;
		mass[index_max] = 0;
		return -1;		
	}


	return 0;
}


unsigned char charge(signed char sensor_pin)
{
	register unsigned char count_charge = 0;

	TOUCH_DDR |= (1 << sensor_pin);
	
	// переводим пин на вывод чтобы разрядить кондей.
	while((TOUCH_PIN & (1 << sensor_pin))) // ждём когда на пине будет лог 0. кондей разряжен.
		;
	
	TOUCH_DDR  &= ~(1 << sensor_pin); // переводим пин в высокоимпедансное состояние (ну и слово)
	while(!(TOUCH_PIN & (1 << sensor_pin))) // ждём когда на пине будет лог 1 и увеличиваем переменую
		count_charge++;
	
	return count_charge; // измеренное время в попугаях
}


void sensor_scan(unsigned int *sens, unsigned char *compa_arr)
{
	int i = 0;
	
	for(int sensor_pin = FIRST; sensor_pin < LAST; sensor_pin++)
	{
		if(charge(sensor_pin) > compa_arr[i]) // сравниваем измеренное время с пороговым
		{
			if(sens[i] < 3000)// Если больше - увеличиваем значение в массиве для этого сенсора. Иначе - уменьшаем.
			sens[i] += 1;
		}
		else if(sens[i] > 0)
			sens[i] -= 1;
		i++;
	}
}


void result_null (unsigned int *mass)
{
	for(signed char i = 0; i < SENS; i++)
	mass[i] = 0;
}
