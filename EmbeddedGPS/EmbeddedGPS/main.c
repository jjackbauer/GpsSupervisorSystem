#include "definitions.h"
#include "UART.h"
#include "USART.h"
#include "nmeaScanner.h"


void init(void)
{
	SystemInit();
	WDT->WDT_MR = WDT_MR_WDDIS;//Disable watchdog timer
	inic_UART();
	init_usart0();
	inic_Interrupt_RX();
}

int main(void)
{
	init();
	escreve_UARTmsg("AQUI!\n");
	while (1)
	{
		escreve_UARTmsg(scanNmea("$GPRMC"));
		//escreve_UARTmsg(scanNmea("$GPGLL"));
		if(returnStatusBufferRx())
		{
			//escreve_UARTmsg(returnBufferRX());
			escreve_bufferRX();
			limpaBufferRX();
		}
	}
}
