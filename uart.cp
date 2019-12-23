#line 1 "E:/Desktop/LCD_Driver_Example.X/uart.c"
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
#line 3 "E:/Desktop/LCD_Driver_Example.X/uart.c"
void UART_Init(void)
{

 TRISC6 = 0;
 TRISC7 = 1;

 SPBRG = (( 4000000  / 16) /  9600 ) - 1;
 BRGH = 1;

 SYNC = 0;
 SPEN = 1;

 TXEN = 1;
 TX9 = 0;



 RCIE = 1;
 PEIE = 1;
 GIE = 1;

 CREN = 1;
 RX9 = 0;

}


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




 uint8_t UART_Buffer[ 10 ], UART_front = 0, UART_rear = 0, UART_size = 0;

 void inline UART_isr(void)
 {
 if (RCIF == 1)
 {
 UART_Buffer[UART_rear] = RCREG;
 UART_rear = (UART_rear + 1) %  10 ;
 UART_size = (UART_size + 1) %  10 ;
 RCIF = 0;
 }
 }

 uint8_t UART_read(void)
 {
 if (UART_size > 0)
 {
 uint8_t result = UART_Buffer[UART_front];
 UART_front = (UART_front + 1) %  10 ;
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
