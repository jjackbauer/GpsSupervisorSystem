#ifndef UART_H_
#define UART_H_

#include "definitions.h"			//necessário conhecer a FCPU

#define BAUD 9600					// taxa de comunicação
#define UART_CD  FCPU/16/BAUD
#define tam_bufferRX 10				// tamanho do buffer de recepcao de dados

void UART_Handler();
void limpaBufferRX();
void inic_UART();
void inic_Interrupt_RX();
void escreve_UARTcarac(char c);
void escreve_UARTmsg(char * msg);
char * returnBufferRX();
void escreve_bufferRX();
uint32_t returnStatusBufferRx();
uint32_t le_UARTcarac();

#endif /* UART_H_ */