/*
 * a_temp_regulator.c
 *
 * Created: 5/3/2016 9:01:24 PM
 *  Author: Gigi
 */ 
 #include "a_temp_regulator.h"
 #include "a_LM50_temp_sensor.h"
 #include "uart_drv.h"
 #include <avr/io.h>


 #define TRESHOLD_CELSIUS 25
 #define MIN_LEVEL (TRESHOLD_CELSIUS - 1)
 #define MAX_LEVEL (TRESHOLD_CELSIUS + 1)


 T_UBYTE lub_temp_val;
 T_UBYTE caub_adc_mv[8];
 void tr_update_temp(void)
 {
	unsigned int whole_val = LM50_get_temp();
	lub_temp_val = whole_val / 10 ;

	if(lub_temp_val > MAX_LEVEL)
	{
		//PORTB &= ~(1<<PINB0);	// STOP HEATING
	}
	else if(lub_temp_val < MIN_LEVEL)
	{
		//PORTB |= (1<< PINB0);	// START HEATING
	}
	else
	{
		/* Nothing to do */
	}
	USART_Transmit(whole_val / 10);
	USART_Transmit(whole_val % 10);
 }
 
 void tr_get_updated_adc_values()
 {
	 caub_adc_mv[0] = adc_get_mv_filtered_value(0);
	 caub_adc_mv[1] = adc_get_mv_filtered_value(1);
	 caub_adc_mv[2] = adc_get_mv_filtered_value(2);
	 caub_adc_mv[3] = adc_get_mv_filtered_value(3);
	 caub_adc_mv[4] = adc_get_mv_filtered_value(4);
	 caub_adc_mv[5] = adc_get_mv_filtered_value(5);
	 caub_adc_mv[6] = adc_get_mv_filtered_value(6);
	 caub_adc_mv[7] = adc_get_mv_filtered_value(7);
 }