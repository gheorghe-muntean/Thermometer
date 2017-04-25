/*
 * a_temp_regulator.h
 *
 * Created: 5/3/2016 9:01:38 PM
 *  Author: Gigi
 */ 


#ifndef A_TEMP_REGULATOR_H_
#define A_TEMP_REGULATOR_H_

#include "std_types.h"

extern void tr_update_temp(void);
extern void tr_get_updated_adc_values(void);

#endif /* A_TEMP_REGULATOR_H_ */