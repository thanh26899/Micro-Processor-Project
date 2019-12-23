
#include "LCD.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void LCD_DATA(unsigned char Data)
{
    if(Data & 1) 
        D4 = 1;
    else
        D4 = 0;
    if(Data & 2)
        D5 = 1;
    else
        D5 = 0;
    if(Data & 4)
        D6 = 1;
    else
        D6 = 0;
    if(Data & 8) 
        D7 = 1;
    else
        D7 = 0;
}
void LCD_CMD(unsigned char CMD)
{
    // Select Command Register
    RS = 0;           
    // Move The Command Data To LCD
    LCD_DATA(CMD);
    // Send The EN Clock Signal
    EN  = 1;         
    __delay_us(LCD_EN_Delay);
    EN  = 0;         
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
      Temp  = 0x80 + c - 1; //0x80 is used to move the cursor
      High4 = Temp >> 4;
      Low4  = Temp & 0x0F;
      LCD_CMD(High4);
      LCD_CMD(Low4);
    }
    if(r == 2)
    {
      Temp  = 0xC0 + c - 1;
      High4 = Temp >> 4;
      Low4  = Temp & 0x0F;
      LCD_CMD(High4);
      LCD_CMD(Low4);
    }
}
void LCD_Init()
{
  // IO Pin Configurations
  LCD_DATA_PORT_D = 0x00;
  LCD_RS_D = 0;
  LCD_EN_D = 0;
  // The Init. Procedure As Described In The Datasheet
  
  //Special case Function set
  LCD_CMD(0x03);
  __delay_ms(5);
  LCD_CMD(0x03);
  __delay_us(100);
  LCD_CMD(0x03); 
  __delay_us(100);
  LCD_CMD(0x02);
  __delay_us(100);
  
  //function set
  LCD_CMD(0x02);
  LCD_CMD(0x08);
   __delay_us(53);
   
  //Display on/off
  LCD_CMD(0x00);
  LCD_CMD(0x08);
  __delay_us(53);
  
  //Clear Display
  LCD_CMD(0x00);
  LCD_CMD(0x01);
  __delay_ms(3);

  //Entry mode set
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
   Low4  = Data & 0x0F;
   High4 = Data & 0xF0;
   RS = 1;        
   LCD_DATA(High4>>4);  
   EN = 1;
   __delay_us(LCD_EN_Delay); 
   EN = 0;
   __delay_us(LCD_EN_Delay); 
   LCD_DATA(Low4); 
   EN = 1;
   __delay_us(LCD_EN_Delay); 
   EN = 0;
   __delay_us(LCD_EN_Delay); 
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

void lcd_float(float number)
{
     char ch[20];
     sprintf(ch,"%0.2f",number);
     LCD_Write_String(ch);
}