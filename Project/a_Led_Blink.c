/*
 * a_Led_Blink.c
 *
 * Created: 4/26/2016 10:59:09 PM
 *  Author: Gigi
 */ 
 #include <avr/io.h>
  #include "a_LM50_temp_sensor.h"

 unsigned int rub_temperature = 0;

 void Led_Blink_main()
 {
	rub_temperature = LM50_get_temp();
	if(rub_temperature >= 240)
	{
		turn_off_led();
	}
	else
	{
		turn_on_led();
	}
 }

void turn_off_led()
{
	PORTB &=~(1<<PINB0);
}

void turn_on_led()
{
	PORTB |=(1<<PINB0);
}