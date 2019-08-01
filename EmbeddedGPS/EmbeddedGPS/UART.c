#include "UART.h"

char bufferRX[tam_bufferRX+1];				// buffer para a recepção, coloca caractere nulo no final da string
volatile uint32_t flag_bufferCheio=0;

void UART_Handler()
{
	static uint32_t i =0;
	
	
	if(flag_bufferCheio == 0)
	{
		bufferRX[i] = UART->UART_RHR;		// leitura do dado recebido
		i++;
		
		if(i==tam_bufferRX)
		{
			flag_bufferCheio=1;
			i=0;
		}
	}
	else
	{
		uint32_t lixo;
		lixo = UART->UART_RHR;					// o registrador UART_RHR sempre deve ser lido
	}
}
//-------------------------------------------------------------------------------------------
void limpaBufferRX()						// limpa buffer e libera nova escrita de dados
{
	for(uint32_t i=0; i< tam_bufferRX+1; i++)
	{
		bufferRX[i]=0;
		flag_bufferCheio = 0;
	}
}
//-------------------------------------------------------------------------------------------
char * returnBufferRX()
{
	return bufferRX;
}
//-------------------------------------------------------------------------------------------
uint32_t returnStatusBufferRx()
{
	if(flag_bufferCheio==0)
	return 0;
	else return 1;
}
//-------------------------------------------------------------------------------------------
void inic_UART()
{
	PIOA->PIO_ABSR &=~ (PIO_PA9 | PIO_PA8);						// seleção do periferico UART no PIOA, pinos PA8 e PA9 (periférico A)
	PIOA->PIO_PDR = PIO_PA9 | PIO_PA8;							// moves pins control from PIO controller to Peripheral

	PMC->PMC_PCER0 = 1 << ID_UART;								// the UART clock must be enable in the PMC
	
	UART->UART_BRGR = UART_CD;									// ajuste da taxa de comunicacao
	UART->UART_CR = UART_CR_RXEN | UART_CR_TXEN;				// Habilita transmissão e recepção
	UART->UART_MR = UART_MR_CHMODE_NORMAL | UART_MR_PAR_NO;		// sem paridade, modo normal
	
	limpaBufferRX();
}


//-------------------------------------------------------------------------------------------
void inic_Interrupt_RX()
{
	// Habilitando a interrupção da UART na recepção
	UART->UART_IER =  UART_IER_RXRDY;					// Habilita interrupção após recepção
	NVIC_EnableIRQ((IRQn_Type) ID_UART);				// Habilitação do NVIC - função padrão (CMSIS library)
}
//-------------------------------------------------------------------------------------------
void escreve_UARTcarac(char c)
{
	while(!(UART->UART_SR & UART_SR_TXRDY));	// wait until previous character is processed
	UART->UART_THR = c;
}
//-------------------------------------------------------------------------------------------
void escreve_UARTmsg(char * msg)
{
	for (; *msg!=0; msg++) 	 escreve_UARTcarac(*msg);
}
//-------------------------------------------------------------------------------------------
void escreve_bufferRX()						// se houver dados no buffer, escreve
{
	uint32_t i=0;
	
	while(bufferRX[i]!=0)
	{
		escreve_UARTcarac(bufferRX[i]);
		i++;
	}
}
//-------------------------------------------------------------------------------------------
uint32_t le_UARTcarac()
{
	while(!(UART->UART_SR &  UART_SR_RXRDY));
	return UART->UART_RHR;
}
//-------------------------------------------------------------------------------------------
