#include "UART_init.h"
#include "TM4C123GH6PM.h"
#include "../utils/bit_utils.h"
void UART0_init_fifo(int BR)
{
	 double I_FBRD = 0;    
    SET_BIT(SYSCTL->RCGCUART, UART_0);
    SET_BIT(SYSCTL->RCGCGPIO, UART0_GPIO);
    while(!GET_BIT(SYSCTL->PRGPIO, UART0_GPIO));
	
		UART0 -> CTL = 0;
	
    I_FBRD= (16000000 / 16.0) / BR;
	
		UART0 -> IBRD = (int)I_FBRD;
		UART0 -> FBRD = (int)((I_FBRD - ((int)I_FBRD))*64 +0.5);
	
    UART0->LCRH = 0x70; // 8-bit, no parity, 1-stop bit, FIFO
    UART0->CTL = 0x301; // enable UART0, TXE, RXE
    UART0->CC = 0;      // use system clock
    SET_BIT(GPIOA->DEN, PA0);
	SET_BIT(GPIOA->DEN, PA1);
    SET_BIT(GPIOA->AFSEL, PA0);
    SET_BIT(GPIOA->AFSEL, PA1);
    SET_H_BYTE(GPIOA->PCTL, PA0, 1); //set 4 bits for alternative function (UART) of pin PA0
    SET_H_BYTE(GPIOA->PCTL, PA1, 1); //set 4 bits for alternative function (UART) of pin PA1
	CLR_BIT(GPIOA->AMSEL, PA0);
	 CLR_BIT(GPIOA->AMSEL, PA1);
}


char UART0_READ_BYTE()
{
	while(GET_BIT(UART0->FR, 4));
	return (char)(UART0->DR & 0xFF);
}

void UART0_WRITE_BYTE (char data)
{
    while((UART0-> FR & 0x20)!=0);
    UART0->DR = data;
}