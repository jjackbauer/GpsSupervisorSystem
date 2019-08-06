#ifndef UART_H_
#define UART_H_

#include "definitions.h"
#define BAUD 9600
#define UART_CD  FCPU/16/BAUD
#define tam_bufferRX 10

void UART_Handler();
void limpaBufferRX();
void init_UART();
void init_Interrupt_RX();
void escreve_UARTcarac(char c);
void escreve_UARTmsg(char * msg);
char * returnBufferRX();
void escreve_bufferRX();
uint32_t returnStatusBufferRx();
uint32_t le_UARTcarac();

#endif /* UART_H_ */