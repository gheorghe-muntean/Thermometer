/*
 * adc_drv.c
 *
 * Created: 4/26/2016 9:52:26 PM
 *  Author: Gigi
 */ 

 #include "adc_drv.h"
#include <avr/io.h>


void adc_initialisation();



typedef struct  
{
	E_ADC_CH e_ch;
	T_UWORD luw_mV[10];
}S_ADC_FILTER;


T_UWORD luw_get_result = 0, ruw_sample = 0;
S_ADC_FILTER s_filtered_adc[8];
	T_UWORD luw_result = 0x0000;


void adc_initialisation()
{
	/* Select ADC Channel ADC0 enabled */
	ADMUX = 0x00;

	/* set pre-scaler with ADCSRA bits to 128 */
	ADCSRA|=(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);

	/* Enable Interrupt Flag */
	//ADCSRA|=(1<<ADIF);

	/* Enable Interrupt Enable */
	//ADCSRA|=(1<<ADIE);

	/* Switch ON ADC */
	ADCSRA|=(1<<ADEN);
}



T_UWORD adc_get_mv(T_UBYTE channel)
{
	channel=channel & 0b00000111;		//Select ADC Channel, channel must be 0-7
	ADMUX = 0;
	//ADMUX |= (1<<MUX0);        //Clear the older channel that was read
	ADMUX|= channel;

	if(!(ADCSRA & (1<<ADSC)))
	{
		luw_get_result=ADC;
		ADCSRA |=(1<<ADSC);	// enable ADC and start single conversion
		luw_get_result = (luw_get_result * 4.887585532746823) ; // 4.887585532746823 is quanta of convertor
	}

return luw_get_result;
}

T_UWORD adc_get_mv_filtered_value(E_ADC_CH channel)
{
	luw_result =
	(s_filtered_adc[channel].luw_mV[0] +
	s_filtered_adc[channel].luw_mV[1] +
	s_filtered_adc[channel].luw_mV[2] +
	s_filtered_adc[channel].luw_mV[3] +
	s_filtered_adc[channel].luw_mV[4] +
	s_filtered_adc[channel].luw_mV[5] +
	s_filtered_adc[channel].luw_mV[6] +
	s_filtered_adc[channel].luw_mV[7] +
	s_filtered_adc[channel].luw_mV[8] +
	s_filtered_adc[channel].luw_mV[9])
	/ 10;

return luw_result;
}


void adc_update_filtered_result(void)
{
	unsigned char ch;
	for(ch=0;ch<ADC_max_ch;ch++)
	{
		s_filtered_adc[ch].luw_mV[ruw_sample] = adc_get_mv(ch);
	}

	if(ruw_sample>=9)
	{
		ruw_sample = 0;
	}
	else
	{
		ruw_sample++;
	}
}