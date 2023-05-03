#ifndef UART_INIT_H
#define UART_INIT_H

void UART0_init_fifo(int BR);
char UART0_READ_BYTE();
void UART0_WRITE_BYTE (char data);

#endif
