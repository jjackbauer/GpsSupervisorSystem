#ifndef USART_H_
#define USART_H_

#include "definitions.h"

//  Werte fuer die Baudraten des U(S)ART      --> BR = BaudRate   MCK = MasterClocK   CD = ClockDivisor
#define   BAUD_9600     547   //  Wert fuer   9600 Baud ( BR = MCK / (16 * CD) --> CD = MCK / (16 * BR) --> CD = 84.000.000 / (16 *   9600) =  546875)

#define   USART0_PMC_ENABLE           0x00020000    //  P_ID  17
#define   USART0_PIN_CONTROL_TO_PERI  0x00000C00    //  Pin 10 und 11
#define   USART0_TX_OUTPUT            0x00000800    //  Pin 11
#define   USART0_PINS_TO_PERI_A      ~0x00000C00    //  Pin 10 und 11
#define   ENABLE_RX                   0x00000010    //
#define   USART_MODE_REG              0x000008C0    //  normal mode - 1-8-N-1
#define   RXRDY_IRQ_ENABLE            0x00000001    //
#define   TXEMPTY_IRQ_ENABLE          0x00000200    //

void init_usart0(void);
uint32_t le_USARTcarac();

#endif /* USART_H_ */