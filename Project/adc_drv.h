/*
 * adc_drv.h
 *
 * Created: 4/26/2016 9:52:41 PM
 *  Author: Gigi
 */ 


#ifndef ADC_DRV_H_
#define ADC_DRV_H_


#include "std_types.h"

typedef enum
{
	ADC_Ch0,
	ADC_Ch1,
	ADC_Ch2,
	ADC_Ch3,
	ADC_Ch4,
	ADC_Ch5,
	ADC_Ch6,
	ADC_Ch7,
	ADC_max_ch
}E_ADC_CH;



extern void adc_initialisation();

extern T_UWORD adc_get_LM50_temp();
extern void adc_update_filtered_result(void);
extern T_UWORD adc_get_mv_filtered_value(E_ADC_CH channel);
#endif /* ADC_DRV_H_ */