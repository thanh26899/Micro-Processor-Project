#ifndef UART_16F877A_H
#define UART_16F877A_H

/**
 * To use this library, you have to define one of available UART modes:
 * - UART_TRANSMIT
 * - UART_RECEIVE
 * - UART_BOTH
 * You also have to call the UART_isr() in your main ISR if you want to use it
 */
//#define UART_TRANSMIT
//#define UART_RECEIVE
#define UART_BOTH

//#include <xc.h>
#include <stdint.h>
#ifndef _XTAL_FREQ
    #define _XTAL_FREQ 4000000
#endif

#ifndef BAUD_RATE
    #define BAUD_RATE 9600
#endif

#ifdef UART_BOTH
    #define UART_TRANSMIT
    #define UART_RECEIVE
#endif

#ifndef UART_BUFFER_SIZE
    #define UART_BUFFER_SIZE 10
#endif

/**
 * @brief      Init UART
 */
void UART_Init(void);
#ifdef UART_TRANSMIT
/**
 * @brief      Write a byte
 *
 * @param[in]  data    Data to write
 */
void UART_Write(uint8_t data);
/**
 * @brief      Write a series of bytes
 *
 * @param      text   Pointer to the start of data  
 * @param[in]  size     Size of the data
 */
void UART_Write_Bytes(char *text, uint8_t size);
#endif

#ifdef UART_RECEIVE
/**
 * @brief      Read a byte
 *
 * @return     The value of received data
 */
uint8_t UART_read(void);
/**
 * @brief      Read a string 
 *
 * @param      des   The destination
 * @param[in]  max   The maximum length of a string
 */
void UART_read_a_string(uint8_t* des, uint8_t max);
/**
 * @brief      Read a series of bytes
 *
 * @param      des   The destinatino
 * @param[in]  size  The size of the data to read
 */
void UART_read_bytes(uint8_t* des, uint8_t size);
/**
 * @brief      Size of available data
 *
 * @return     size of the received data
 */
uint8_t UART_read_available(void);
/**
 * UART interrupt service routine
 */
void inline UART_isr(void);
#endif

#endif