#ifndef UART_INIT_H
#define UART_INIT_H

void UART0_init_fifo(int BR);
char UART0_READ_BYTE(void);
void UART0_WRITE_BYTE (char data);


void UART1_init_fifo(int BR);
char UART1_READ_BYTE(void);
void UART1_WRITE_BYTE (char data);
#endif
