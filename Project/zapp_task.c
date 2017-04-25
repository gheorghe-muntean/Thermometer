/*
 * zapp_task.c
 *
 * Created: 4/26/2016 9:51:32 PM
 *  Author: Gigi
 */ 
#include "zapp_task.h"
#include "a_temp_regulator.h"
#include "adc_drv.h"
#include "rf_433b_drv.h"

unsigned int	lub_1ms = 0,
				lub_5ms = 0,
				lub_10ms = 0,
				lub_20ms = 0,
				lub_50ms = 0,
				lub_100ms = 0,
				lub_1sec = 0;

unsigned char rub_count_1sec = 0;
T_UBYTE luw_test = 0;

 void zapp_1ms_TASK();
 void zapp_5ms_TASK();
 void zapp_10ms_TASK();
 void zapp_20ms_TASK();
 void zapp_50ms_TASK();
 void zapp_100ms_TASK();
 void zapp_1sec_TASK();



void zapp_1ms_TASK()
{
	lub_1ms++;
}

void zapp_5ms_TASK()
{
	lub_5ms++;
}

void zapp_10ms_TASK()
{
	lub_10ms++;
}

void zapp_20ms_TASK()
{
	lub_20ms++;
}

void zapp_50ms_TASK()
{
	lub_50ms++;
}

void zapp_100ms_TASK()
{
	lub_100ms++;
	adc_update_filtered_result();
}

void zapp_1sec_TASK()
{
	lub_1sec;
	//tr_update_temp();
	tr_get_updated_adc_values();
}