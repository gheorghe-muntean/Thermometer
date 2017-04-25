/*
 * uart_drv.c
 *
 * Created: 4/26/2016 9:53:08 PM
 *  Author: Gigi
 */ 

 #include "uart_drv.h"
 #include "avr/io.h"


void USART_Init();
void USART_Transmit(T_UBYTE data);
T_UBYTE USART_Receive(void);
void USART_Flush(void);

 /* USART0 initialization */
void USART_Init()
 {
	 /* Set baud rate */
	 UBRR0H = (T_UBYTE)(UART_PC_UBRR_9600>>8);
	 UBRR0L = (T_UBYTE)UART_PC_UBRR_9600;
	 /* Enable receiver and transmitter */
	 UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	 /* Set frame format: */
	 //UCSR0C |= (1<<USBS0); /* 2stop bit */
	 UCSR0C |= (3<<UCSZ00); /* 8data */
 }
 /* USART0 Transmission 8 data bit at once */
void USART_Transmit( T_UBYTE data )
 {
	 /* Wait for empty transmit buffer */
	 while ( !( UCSR0A & (1<<UDRE0)) )
	 ;
	 /* Put data into buffer, sends the data */
	 UDR0 = data;
 }
 /* USART0 Reception 8 bit of data */
T_UBYTE USART_Receive(void)
 {
	 /* Wait for data to be received */
	 while ( !(UCSR0A & (1<<RXC0)) )
	 ;
	 /* Get and return received data from buffer */
	 return UDR0;
 }
 /* USART0 Flush of data */
void USART_Flush( void )
 {
	 while ( UCSR0A & (1<<RXC0) )
	 (void)UDR0;
 }