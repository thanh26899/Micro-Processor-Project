#line 1 "E:/Desktop/LCD_Driver_Example.X/LCD.c"
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
#line 5 "E:/Desktop/LCD_Driver_Example.X/LCD.c"
void LCD_DATA(unsigned char Data)
{
 if(Data & 1)
  RD4  = 1;
 else
  RD4  = 0;
 if(Data & 2)
  RD5  = 1;
 else
  RD5  = 0;
 if(Data & 4)
  RD6  = 1;
 else
  RD6  = 0;
 if(Data & 8)
  RD7  = 1;
 else
  RD7  = 0;
}
void LCD_CMD(unsigned char CMD)
{

  RD1  = 0;

 LCD_DATA(CMD);

  RD0  = 1;
 __delay_us( 10000 );
  RD0  = 0;
}
void LCD_Clear()
{
 LCD_CMD(0x00);
 LCD_CMD(0x01);
}
void LCD_Set_Cursor(unsigned char r, unsigned char c)
{
 unsigned char Temp,Low4,High4;
 if(r == 1)
 {
 Temp = 0x80 + c - 1;
 High4 = Temp >> 4;
 Low4 = Temp & 0x0F;
 LCD_CMD(High4);
 LCD_CMD(Low4);
 }
 if(r == 2)
 {
 Temp = 0xC0 + c - 1;
 High4 = Temp >> 4;
 Low4 = Temp & 0x0F;
 LCD_CMD(High4);
 LCD_CMD(Low4);
 }
}
void LCD_Init()
{

  TRISD  = 0x00;
  TRISD2  = 0;
  TRISD3  = 0;



 LCD_CMD(0x03);
 __delay_ms(5);
 LCD_CMD(0x03);
 __delay_us(100);
 LCD_CMD(0x03);
 __delay_us(100);
 LCD_CMD(0x02);
 __delay_us(100);


 LCD_CMD(0x02);
 LCD_CMD(0x08);
 __delay_us(53);


 LCD_CMD(0x00);
 LCD_CMD(0x08);
 __delay_us(53);


 LCD_CMD(0x00);
 LCD_CMD(0x01);
 __delay_ms(3);


 LCD_CMD(0x00);
 LCD_CMD(0x06);
 __delay_us(53);

 LCD_CMD(0x00);
 LCD_CMD(0x0C);
 __delay_us(53);
}
void LCD_Write_Char(char Data)
{
 char Low4,High4;
 Low4 = Data & 0x0F;
 High4 = Data & 0xF0;
  RD1  = 1;
 LCD_DATA(High4>>4);
  RD0  = 1;
 __delay_us( 10000 );
  RD0  = 0;
 __delay_us( 10000 );
 LCD_DATA(Low4);
  RD0  = 1;
 __delay_us( 10000 );
  RD0  = 0;
 __delay_us( 10000 );
}
void LCD_Write_String(char *str)
{
 int i;
 for(i=0;str[i]!='\0';i++)
 LCD_Write_Char(str[i]);
}
void LCD_SL()
{
 LCD_CMD(0x01);
 LCD_CMD(0x08);
}
void LCD_SR()
{
 LCD_CMD(0x01);
 LCD_CMD(0x0C);
}
