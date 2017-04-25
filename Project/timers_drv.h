/*
 * timers_drv.h
 *
 * Created: 4/26/2016 9:58:32 PM
 *  Author: Gigi
 */ 


#ifndef TIMERS_DRV_H_
#define TIMERS_DRV_H_
#include "std_types.h"

extern unsigned int timers_get_miliseconds();
extern unsigned char timers_get_seconds();
extern unsigned char timers_get_minutes();
extern void timers_timer3_init();
extern void timers_timer0_initialize_FAST_PWM(void);

#endif /* TIMERS_DRV_H_ */