/*
 * std_types.h
 *
 * Created: 3/14/2016 6:21:54 PM
 *  Author: Gigi
 */ 
 
#ifndef STD_TYPES_H_
#define STD_TYPES_H_

#define TRUE 0x01
#define FALSE 0x00

#define SET_BIT(port,pin) (port|=(1<<pin))
#define CLEAR_BIT(port,pin) (port&=~(1<<pin))
#define TOGLE_BIT(port,pin) (port^=(1<<pin))

typedef unsigned char T_UBYTE;
typedef unsigned int  T_UWORD;

#endif /* STD_TYPES_H_ */