/*
 * zapp_init.h
 *
 * Created: 4/26/2016 10:01:09 PM
 *  Author: Gigi
 */ 


#ifndef ZAPP_INIT_H_
#define ZAPP_INIT_H_

typedef enum
{
	RS_NO_RESET,
	RS_POWER_ON_RESET,
	RS_EXTERNAL_RESET,
	RS_BROWN_OUT_RESET,
	RS_WATCHDOG_RESET,
	RS_JTAG_RESET,
	RS_UNKNOWN_RESET
}E_RESET_SOURCE;

extern unsigned char zinit_app_init_function();


#endif /* ZAPP_INIT_H_ */