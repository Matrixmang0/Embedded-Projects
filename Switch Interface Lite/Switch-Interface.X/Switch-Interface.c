
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

# define _XTAL_FREQ 6000000

void main()
{
    TRISC=0x0F;   // setting the pins RC0 to RC3 to input and others to output
    TRISD=0x00;   // setting the pins RD0 to RD7 to output
    
    unsigned char val;  // initializing the variable val
    PORTC = 0x00;       // initializing the portC pins
    PORTD = 0x00;       // initializing the portD pins
    
    // initializing the port pins doesn't change the output, but it is a
    // good practice as the output may not get affected by the previous session  
    
    while(1)
    {
    
    val = PORTC;
    switch(val)
    {
        case 0x0E : PORTD = 0x20; // turning on LED1 at RD5 for switch 1
        break;
        
        case 0x0D : PORTD = 0x02; // turning on LED2 at RD1 for switch 2
        break;
        
        case 0x0B : PORTD = 0x22;  // turning on both LED 1 and LED 2 at RD5 and RD1 respectively for switch 3
        break;
        
        case 0x07 : PORTD = 0x00;  // turning off both LEDs for switch 3
        break; 
        
        default : PORTD = 0x00;   // turning off both LEDs by default
    }
    
    }
}