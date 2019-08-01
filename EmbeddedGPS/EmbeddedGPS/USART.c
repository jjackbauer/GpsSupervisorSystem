#include "USART.h"

void init_usart0(void)
{
	PMC->PMC_PCER0  |= USART0_PMC_ENABLE;
	PIOA->PIO_PDR   |= USART0_PIN_CONTROL_TO_PERI;
	PIOA->PIO_OER   |= USART0_TX_OUTPUT;
	PIOA->PIO_ABSR  &= USART0_PINS_TO_PERI_A;

	USART0->US_CR    = ENABLE_RX;
	USART0->US_MR    = USART_MODE_REG;
	USART0->US_BRGR  = BAUD_9600;
	//USART0->US_IDR = 0xffffffff; //US_IDR_RXRDY | US_IDR_TXRDY ;//Desabilita interrupção do TX e RX
	USART0->US_IER   = RXRDY_IRQ_ENABLE;
	
	//NVIC_EnableIRQ(USART0_IRQn);
}

uint32_t le_USARTcarac()
{
	while(!(USART0->US_CSR &  US_CSR_RXRDY));
	return (USART0->US_RHR & 0xff);
}
