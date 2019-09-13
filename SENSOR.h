#ifndef SENSOR_H_
#define SENSOR_H_

#include <avr/interrupt.h>

								// НАСТРОЙКА //
/**///////////////////////////////////////////////////////////////////////////////////////**/
/**/#define TOUCH_PORT PORTB														                                /**/
/**/#define TOUCH_DDR DDRB	 // порт к которому подключены сенсоры					           /**/
/**/#define TOUCH_PIN PINB														                                /**/
/**/#define SENS 8			 // количество сенсоров в ползунке или крутилке		           /**/
/**/#define ALL_SENS 8      // всего сенсоров										                    /**/
/**/#define FIRST  0         // Номер пина на порте с которого начинается отсчёт   /**/ 
/**/#define TRASH_HOLD 20    //порог выше которого счиатем что произошло залипание/**/ 
/**/#define BORDER 30 		 // порог срабатывания сенсоров						             /**/
/**/																			                                      /**/
/**/						  												                                     /**/
/**////////////////////////////////////////////////////////////////////////////**/

#define LAST FIRST + ALL_SENS
#define NEXT SENS - 1


void calibration(unsigned char * compa_arr);
void sensor_scan(unsigned int *stat_sens, unsigned char * compa_arr);
void result_null (unsigned int *mass);
unsigned char charge(signed char sensor_pin);
signed char incod(unsigned int *mass);






#endif /* SENSOR_H_ */
