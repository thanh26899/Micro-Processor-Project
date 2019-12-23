#include <xc.h>
#include<pic16f877a.h>
#include "LCD.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SBIT_ADON     0
#define SBIT_CHS0     3
#define SBIT_ADFM     7

void init_uart(void) {
    TXSTAbits.TXEN = 1;               // enable transmitter
    RCSTAbits.SPEN = 1;               // enable serial port
}

void ADC_Init()
 {
   ADCON0=0x00;  // sampling freq=osc_freq/2,ADC off initially
   ADCON1=(1<<SBIT_ADFM);  // All pins are configured as Analog pins and ADC result is right justified  
}


int ADC_Read(int adcChannel)
 {  
    ADCON0 = (1<<SBIT_ADON) | (adcChannel<SBIT_CHS0);  //select required channel and turn ON adc

    __delay_ms(1000);                   //Acquisition Time(Wait for Charge Hold Capacitor to get charged )
   
    GO=1;                           // Start ADC conversion
    while(GO_DONE==1);              // Wait for the conversion to complete
                                    // GO_DONE bit will be cleared once conversion is complete

    return((ADRESH<<8) + ADRESL);   // return right justified 10-bit result
 }



////// MQ-2 gas sensor interfacing with pic microcontroller ///////

void main() {
    ADC_Init();  // it will initialize the adc module
    TRISD = 0X00;
    PORTD = 0X00;
    LCD_Init();
    __delay_ms(5000);
    LCD_Clear();
    LCD_Set_Cursor(1,1);
    LCD_Write_String("Ly-Thanh-Toan");
    __delay_ms(1000);
    LCD_Set_Cursor(2,1);
    LCD_Write_String("GAS SENSOR");
    __delay_ms(8000);
    LCD_Clear();
    int gas_value;
    
    while(1)
    {
        gas_value = ADC_Read(2); // read the gas value of sensor 
        
        if (gas_value > 400)
        {
            LED = 1;
            LCD_Set_Cursor(1,1);
            LCD_Write_String("WARNING");
            LCD_Set_Cursor(2,1);
            LCD_Write_String("GAS DETECTED");
        }
        else
        {
            LED = 0;
            LCD_Set_Cursor(1,1);
            LCD_Write_String("NO GAS");
        }
        LCD_Clear();     
    }
    return;     
}