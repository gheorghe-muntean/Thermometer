/*
 * timers_drv.c
 *
 * Created: 4/26/2016 9:58:20 PM
 *  Author: Gigi
 */ 
 #include "timers_drv.h"
 #include <avr/interrupt.h>

 typedef struct{
	 unsigned int ms;
	 unsigned char sec;
	 unsigned char min;
 }S_TIME;

 S_TIME system_time;
 unsigned int timers_get_miliseconds(void);
 unsigned char timers_get_seconds(void);
 unsigned char timers_get_minutes(void);
void timers_timer0_initialize_FAST_PWM(void);
 static unsigned char lub_timers_25micro_step = 0;

 /* initialization of TIMER0 in FAST PWM Mode */
void timers_timer0_initialize_FAST_PWM(void)
 {
	 // initialize timer0 in PWM mode
	 TCCR0A |= (1<<WGM00)| (1<<COM0A1) | (1<<WGM01);
	 TCCR0B |= (1<<CS00);
	 // make sure to make OC0 pin (pin PB3 for atmega32) as output pin
	 DDRB |= (1<<PINB3);
 }

 /* Set Duty Cycle for TIMER0 */
 static void timers_timer0_set_duty_cycle(T_UBYTE duty)
 {
	 // Set duty cycle
	 OCR0A = duty;
 }

 /* System time timer */
void timers_timer3_init()
{
	// clear on compare match
	TCCR3A |= (1<<COM3A1);
	TCCR3B |= (1<<WGM32);
	// set up timer with no presscaler count to 500
	TCCR3B |= (1 << CS30);
	
	//set up compare value
	OCR3AH = 0x01;
	OCR3AL = 0xF4;
	
	// initialize counter
	TCNT3H = 0;
	TCNT3L = 0;

	TIMSK3 |= (1<<OCIE3A) | (1<<TOIE3);
}

/* Interrupt generated at every 25 microseconds */
ISR(TIMER3_COMPA_vect)
{
	
	// initialize counter
	TCNT3H = 0;
	TCNT3L = 0;
	// keep a track of number of overflows
	lub_timers_25micro_step++;

	if(lub_timers_25micro_step>=40) /* 1ms counted */
	{	
	
		system_time.ms++;

		if (system_time.ms >= 1000 )/* 1 second counted */
		{
			system_time.sec++;
			system_time.ms=0;

			if(system_time.sec >= 60 ) /* 1 minute counted */
			{
				system_time.min++;
				system_time.sec=0;
				
				if(system_time.min >= 60) /* 1 hour counted */
				{
					system_time.min=0;
				}
				else
				{
					/* Do Nothing */
				}
			}
			else
			{
				/* Do Nothing */
			}
		}
		else
		{
			/* Do Nothing */
		}
		lub_timers_25micro_step=0;	/* reset 25micro step */
	}
	else
	{
		/* Do Nothing */
	}
}


unsigned int timers_get_miliseconds()
{	
	unsigned int luw_temp_ms;
	luw_temp_ms = system_time.ms;
return luw_temp_ms;
}

unsigned char timers_get_seconds()
{
	unsigned char luw_temp_sec;
	luw_temp_sec = system_time.sec;
	return luw_temp_sec;
}

unsigned char timers_get_minutes()
{
	unsigned char luw_temp_min;
	luw_temp_min = system_time.sec;
	return luw_temp_min;
}