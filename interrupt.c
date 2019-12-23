#include "interrupt.h"

void __interrupt() ISR(void)
{
    #ifdef UART_RECEIVE
        UART_isr();
    #endif
    #ifdef SPI_ISR
        SPI_isr();
    #endif
}