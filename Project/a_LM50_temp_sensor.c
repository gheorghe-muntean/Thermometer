/*
 * a_LM50_temp_sensor.c
 *
 * Created: 5/3/2016 6:48:53 PM
 *  Author: Gigi
 */ 
 #include "a_LM50_temp_sensor.h"
 #include "adc_drv.h"

T_UWORD ruw_mV = 0, 
		temp = 0;

T_UWORD LM50_get_temp()
{
	ruw_mV = adc_get_mv_filtered_value(0);
	temp = ruw_mV - 485; // 500 value defined by datasheet
	ruw_mV = 0;
	return temp;
}