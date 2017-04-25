/*
 * zapp_init.c
 *
 * Created: 4/26/2016 10:01:18 PM
 *  Author: Gigi
 */ 

 #include "zapp_init.h"
 #include <avr/io.h>
 #include <avr/interrupt.h>
 #include "std_types.h"
 #include "timers_drv.h"
 #include "adc_drv.h"
 #include "rf_433b_drv.h"

 E_RESET_SOURCE reset_cause = RS_NO_RESET;


 static void reset_reason(void);
 unsigned char zinit_app_init_function();


 unsigned char zinit_app_init_function()
 {
	PORTB=0x00;
		
	reset_reason();
	timers_timer3_init();
	

	timers_timer0_initialize_FAST_PWM();
	USART_Init();	
	rf_USART_Init();
	adc_initialisation();
	sei();
	return 0;
 }



 /* read last reset reason */
 static void reset_reason(void)
 {
	 if (MCUSR & 1)
	 {
		 // Power-on Reset
		 reset_cause = RS_POWER_ON_RESET;
	 }
	 else if (MCUSR & 2)
	 {
		 // External Reset
		 reset_cause = RS_EXTERNAL_RESET;
	 }
	 else if (MCUSR & 4)
	 {
		 // Brown-Out Reset
		 reset_cause = RS_BROWN_OUT_RESET;
	 }
	 else if (MCUSR & 8)
	 {
		 // Watchdog Reset
		 reset_cause = RS_WATCHDOG_RESET;
	 }
	 else if (MCUSR & 0x10)
	 {
		 // JTAG Reset
		 reset_cause = RS_JTAG_RESET;
	 }
	 else
	 {
		 reset_cause = RS_UNKNOWN_RESET; // undetermined (runaway code)
	 }
	 MCUSR&=0xE0;
 }