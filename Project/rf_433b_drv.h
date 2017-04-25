/*
 * rf_433b_drv.h
 *
 * Created: 5/3/2016 10:59:55 PM
 *  Author: Gigi
 */ 


#ifndef RF_433B_DRV_H_
#define RF_433B_DRV_H_
#include "std_types.h"
#include "uart_drv.h"


extern void rf_USART_Init(void);
extern void rf_USART_vSendByte(T_UBYTE u8Data);
extern void rf_Send_Packet(T_UBYTE addr, T_UBYTE cmd);
extern T_UBYTE rf_USART_vReceiveByte(void);



#endif /* RF_433B_DRV_H_ */