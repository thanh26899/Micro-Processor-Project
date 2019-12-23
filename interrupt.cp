#line 1 "E:/Desktop/LCD_Driver_Example.X/interrupt.c"
#line 1 "e:/desktop/lcd_driver_example.x/interrupt.h"
#line 1 "e:/desktop/lcd_driver_example.x/uart.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for pic/include/stdint.h"




typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int int32_t;


typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long int uint32_t;


typedef signed char int_least8_t;
typedef signed int int_least16_t;
typedef signed long int int_least32_t;


typedef unsigned char uint_least8_t;
typedef unsigned int uint_least16_t;
typedef unsigned long int uint_least32_t;



typedef signed char int_fast8_t;
typedef signed int int_fast16_t;
typedef signed long int int_fast32_t;


typedef unsigned char uint_fast8_t;
typedef unsigned int uint_fast16_t;
typedef unsigned long int uint_fast32_t;


typedef signed int intptr_t;
typedef unsigned int uintptr_t;


typedef signed long int intmax_t;
typedef unsigned long int uintmax_t;
#line 37 "e:/desktop/lcd_driver_example.x/uart.h"
void UART_Init(void);
#line 44 "e:/desktop/lcd_driver_example.x/uart.h"
void UART_Write(uint8_t data);
#line 51 "e:/desktop/lcd_driver_example.x/uart.h"
void UART_Write_Bytes(char *text, uint8_t size);
#line 60 "e:/desktop/lcd_driver_example.x/uart.h"
uint8_t UART_read(void);
#line 67 "e:/desktop/lcd_driver_example.x/uart.h"
void UART_read_a_string(uint8_t* des, uint8_t max);
#line 74 "e:/desktop/lcd_driver_example.x/uart.h"
void UART_read_bytes(uint8_t* des, uint8_t size);
#line 80 "e:/desktop/lcd_driver_example.x/uart.h"
uint8_t UART_read_available(void);
#line 84 "e:/desktop/lcd_driver_example.x/uart.h"
void inline UART_isr(void);
#line 6 "e:/desktop/lcd_driver_example.x/interrupt.h"
void __interrupt() ISR(void);
#line 3 "E:/Desktop/LCD_Driver_Example.X/interrupt.c"
void __interrupt() ISR(void)
{

 UART_isr();
#line 11 "E:/Desktop/LCD_Driver_Example.X/interrupt.c"
}
