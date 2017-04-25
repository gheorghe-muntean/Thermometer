/*
 * uart_drv.h
 *
 * Created: 4/26/2016 9:53:18 PM
 *  Author: Gigi
 */ 

#ifndef UART_DRV_H_
#define UART_DRV_H_

#define UART_PC_UBRR_9600 130
 #include "std_types.h"

extern void USART_Init();
extern void USART_Transmit(T_UBYTE data);
extern T_UBYTE USART_Receive(void);
extern void USART_Flush(void);

#endif /* UART_DRV_H_ */