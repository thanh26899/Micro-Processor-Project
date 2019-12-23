#include<pic16f877a.h>
#include "uart.h"

void UART_Init(void)
{
    //--[ Set The RX-TX Pins to be in UART mode (not io) ]--
    TRISC6 = 0;  // As stated in the datasheet
    TRISC7 = 1;  // As stated in the datasheet

    SPBRG = ((_XTAL_FREQ / 16) / BAUD_RATE) - 1;
    BRGH = 1;   // High Baud Rate
    //--[ Enable The Ascynchronous Serial Port ]--
    SYNC = 0;
    SPEN = 1;
    #ifdef UART_TRANSMIT
        TXEN = 1; // Enable UART Transmission
        TX9 = 0;  // 8-bit mode
    #endif
    #ifdef UART_RECEIVE
        //--[ Enable UART Receiving Interrupts ]--
        RCIE = 1; // UART Receving Interrupt Enable Bit
        PEIE = 1; // Peripherals Interrupt Enable Bit
        GIE = 1; // Global Interrupt Enable Bit
        //------------------
        CREN = 1; // Enable Data Continous Reception
        RX9 = 0; // 8-bit mode
    #endif
}

#ifdef UART_TRANSMIT
    void UART_Write(uint8_t data)
    {
        while(!TRMT);
        TXREG = data;
    }
     
    void UART_Write_Bytes(char *text, uint8_t size)
    {
        uint8_t i;
        for(i = 0; i < size; i++)
        {
            UART_Write(text[i]);
        }
    }
#endif

#ifdef UART_RECEIVE
    // Globals
    uint8_t UART_Buffer[UART_BUFFER_SIZE], UART_front = 0, UART_rear = 0, UART_size = 0;
     
    void inline UART_isr(void)
    {
        if (RCIF == 1)
        {
            UART_Buffer[UART_rear] = RCREG; // Read The Received Data Buffer
            UART_rear = (UART_rear + 1) % UART_BUFFER_SIZE;
            UART_size = (UART_size + 1) % UART_BUFFER_SIZE;
            RCIF = 0; // Clear The Flag
        }
    }

    uint8_t UART_read(void)
    {
        if (UART_size > 0)
        {
            uint8_t result = UART_Buffer[UART_front];
            UART_front = (UART_front + 1) % UART_BUFFER_SIZE;
            UART_size--;
            return result;
        }
        return 0;
    }

    void UART_read_bytes(uint8_t* des, uint8_t size)
    {
        if (UART_size < size)
        {
            return;
        }
        uint8_t i;
        for (i = 0; i < size; i++)
        {
            des[i] = UART_read();
        }
    }

    void UART_read_a_string(uint8_t* des, uint8_t max)
    {
        uint8_t i = 0;
        while (UART_size > 0 && i < max)
        {
            des[i] = UART_read();
            if (des[i])
            {
                i++;
            }
            else
            {
                break;
            }
        }
    }

    uint8_t UART_read_available(void)
    {
        return UART_size;
    }
#endif