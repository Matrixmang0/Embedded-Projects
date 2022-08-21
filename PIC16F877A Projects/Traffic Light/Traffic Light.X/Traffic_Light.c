
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

#define _XTAL_FREQ 6000000 //Setting up the frequency to 6MHz

void main() 

{
    
    TRISB = 0xF8;    // Setting up RB0, RB1, RB2 to output and other all pins to input
    
    while(1)
    {
        PORTB = 0x01;       // Setting the RB0 pin HIGH, RB1 and RB2 pins LOW (RED signal)
        __delay_ms(10000);  // Holding the above output for 10 sec
        
        PORTB = 0x02;       // Setting the RB1 pin HIGH, RB0 and RB2 pins LOW (YELLOW signal)
        __delay_ms(5000);   // Holding the above output for 5 sec
        
        PORTB = 0x04;       // Setting the RB2 pin HIGH, RB1 and RB2 pins LOW (GREEN signal)
        __delay_ms(10000);  // Holding the above output for 10 sec
    }
    
    
}