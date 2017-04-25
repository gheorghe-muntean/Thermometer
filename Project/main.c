/*
 * GccApplication1.c
 *
 * Created: 3/16/2016 11:22:40 PM
 * Author : Gigi
 */ 

 #include <avr/interrupt.h>
 #include "std_types.h"
 #include "zapp_init.h"
 #include "zapp_task.h"
 #include "timers_drv.h"

 	T_UWORD luw_previous_ms = 0;
	T_UBYTE luw_previous_sec = 0;
 	T_UWORD luw_CURRENT_ms = 0;
	T_UBYTE luw_CURRENT_sec = 0;
 	T_UWORD luw_previous_5ms_counter = 0;
 	T_UWORD luw_previous_10ms_counter = 0;
 	T_UWORD luw_previous_100ms_counter = 0;

int main(void)
{
	T_UBYTE lub_5ms_flag = FALSE, 
			lub_10ms_flag = FALSE,
			lub_20ms_flag = FALSE,
			lub_50ms_flag = FALSE,
			lub_100ms_flag = FALSE,
			lub_1sec_flag = FALSE;

	luw_previous_ms = 0;
	luw_previous_sec = 0;
 	luw_CURRENT_ms = 0;
	luw_CURRENT_sec = 0;
 	luw_previous_5ms_counter = 0;
 	luw_previous_10ms_counter = 0;
 	luw_previous_100ms_counter = 0;

	zinit_app_init_function();
	
	while(1)
	{
	//cli();	// DISABLE INTERRUPTS
		luw_CURRENT_ms = timers_get_miliseconds();
		luw_CURRENT_sec = timers_get_seconds();

		if(luw_previous_ms != luw_CURRENT_ms)
		{
			zapp_1ms_TASK();
			luw_previous_ms = luw_CURRENT_ms;
			lub_5ms_flag = TRUE;
		}

		if( ((luw_CURRENT_ms % 5) == 0x00) && lub_5ms_flag ) /* 5 milliseconds passed */
		{
			zapp_5ms_TASK();
			lub_5ms_flag = FALSE;
			lub_10ms_flag = TRUE;

		}

		if( ((luw_CURRENT_ms % 10) == 0x00) && lub_10ms_flag ) /* 5 milliseconds passed */
		{
			zapp_10ms_TASK();
			lub_10ms_flag = FALSE;
			lub_20ms_flag = TRUE;
			lub_50ms_flag = FALSE;
			lub_100ms_flag = TRUE;
		}

		if( ((luw_CURRENT_ms % 20) == 0x00) && lub_20ms_flag ) /* 5 milliseconds passed */
		{
			zapp_20ms_TASK();
			lub_20ms_flag = FALSE;
		}

		if( ((luw_CURRENT_ms % 20) == 0x00) && lub_50ms_flag ) /* 5 milliseconds passed */
		{
			zapp_50ms_TASK();
			lub_50ms_flag = FALSE;
			lub_100ms_flag = TRUE;
		}

		if(  ((luw_CURRENT_ms % 100) == 0x00) && lub_100ms_flag ) /* 5 milliseconds passed */
		{
			zapp_100ms_TASK();
			lub_1sec_flag++;
			lub_100ms_flag = FALSE;
		}

		if((luw_previous_sec < luw_CURRENT_sec) && (lub_1sec_flag >= 10) )
		{
			zapp_1sec_TASK();
			lub_1sec_flag = FALSE;
			luw_previous_sec = luw_CURRENT_sec;
		}
		//sei(); // ENABLE_INTERRUPTS
	}
}
