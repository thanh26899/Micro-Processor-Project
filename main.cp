#line 1 "E:/Desktop/LCD_Driver_Example.X/main.c"
#line 1 "e:/desktop/lcd_driver_example.x/lcd.h"
#line 25 "e:/desktop/lcd_driver_example.x/lcd.h"
void LCD_Init();
void LCD_Clear();
void LCD_SL();
void LCD_SR();

void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
void LCD_Set_Cursor(unsigned char, unsigned char);
void LCD_Write_Char(char);
void LCD_Write_String(char*);
#line 1 "e:/desktop/lcd_driver_example.x/config.h"
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF
#line 10 "E:/Desktop/LCD_Driver_Example.X/main.c"
void main() {
 ADC_Init();
 LCD_Init();
 __delay_ms(500);
 LCD_Clear();
 LCD_Set_Cursor(1,1);
 LCD_Write_String("SURPRISE");
 __delay_ms(3000);
 LCD_Set_Cursor(2,1);
 LCD_Write_String("MOTHERFUCKER");
 __delay_ms(2000);

 int gas_value;

 while(1)
 {
 gas_value = ADC_Read(2);
 if(gas_value > 200)
 {
  RD3  = 1;
 LCD_Set_Cursor(1,1);
 LCD_Write_String("GAS DETECTED");
 __delay_ms(3000);
 }
 else
 {
  RD3  = 0;
 LCD_Set_Cursor(1,1);
 LCD_Write_String("NO GAS");
 __delay_ms(3000);
 }
 LCD_Clear();
 }

 return;

}
