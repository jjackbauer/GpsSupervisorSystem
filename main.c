#include "definitions.h"
#include "UART.h"
#include "USART.h"
#include "nmeaScanner.h"


void init(void)
{
	SystemInit();
	WDT->WDT_MR = WDT_MR_WDDIS;//Disable watchdog timer
	init_UART();
	init_usart0();
	init_Interrupt_RX();
}

int main(void)
{
	init();
	escreve_UARTmsg("GPSSupervisor Embedded Code V0.4\n");
	while (1)
	{
		escreve_UARTmsg(scanNmea("$GPRMC"));
	}
}
