/*
 * rf_433b_drv.c
 *
 * Created: 5/3/2016 11:00:10 PM
 *  Author: Gigi
 */ 

 // http://winavr.scienceprog.com/example-avr-projects/running-tx433-and-rx433-rf-modules-with-avr-microcontrollers.html


#include <avr/io.h>
#include "avr/interrupt.h"
#include "rf_433b_drv.h"


//set desired baud rate
#define BAUDRATE_1200_UBRR_VAL 1042

//define receive parameters
#define SYNC 0XAA// synchro signal
#define RADDR 0x44
#define LEDON 0x11//switch led on command
#define LEDOFF 0x22//switch led off command

void rf_USART_Init(void)
{
	//Set baud rate	
	UBRR1L=(T_UBYTE)BAUDRATE_1200_UBRR_VAL;		//low byte	
	UBRR1H=(T_UBYTE)BAUDRATE_1200_UBRR_VAL;	//high byte	
	//Set data frame format: asynchronous mode,no parity, 1 stop bit, 8 bit size	
	UCSR1C=(0<<UMSEL11)|(0<<UMSEL10)|(0<<UPM11)|(0<<UPM10) |	(0<<USBS1)|(0<<UCSZ12)|(1<<UCSZ11)|(1<<UCSZ10);		
	//Enable Transmitter and Receiver and Interrupt on receive complete	
	UCSR1B=(1<<RXEN1)|(1<<RXCIE1)|(1<<TXEN1);
}

T_UBYTE rf_USART_vReceiveByte(void)
{
	// Wait until a byte has been received
	while((UCSR1A&(1<<RXC1)) == 0);
	// Return received data
	return UDR1;
}

void rf_USART_vSendByte(T_UBYTE u8Data)
{    
	T_UBYTE data = 0;
	// Wait if a byte is being transmitted    
	while((UCSR1A&(1<<UDRE1)) == 0);    
	
	// Transmit data    
	UDR1 = u8Data;  
	data = u8Data;
	u8Data = 0;
}

void rf_Send_Packet(T_UBYTE addr, T_UBYTE cmd)
{
	rf_USART_vSendByte(SYNC);//send synchro byte		
	rf_USART_vSendByte(addr);//send receiver address	
	rf_USART_vSendByte(cmd);//send increment command	
	rf_USART_vSendByte((addr+cmd));//send checksum
}

ISR(USART1_RX_vect)
{
	//define variables
	T_UBYTE data[5]={0,0,0,0,0};	//transmitter address

	data[0]=rf_USART_vReceiveByte();
	data[1]=rf_USART_vReceiveByte();
	data[2]=rf_USART_vReceiveByte();
	data[3]=rf_USART_vReceiveByte();
	data[4]=rf_USART_vReceiveByte();
}