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

# define _XTAL_FREQ 6000000   // setting up the input frequency for 6MHz

void main()

{

    TRISC = 0xBD; //Setting the RC1 and RC6 pin to output
    
    while(1) 
    {
        PORTC=0x02;         // setting high for RC1 pin and low for RC6 pin
        __delay_ms(1000);   // Freezing the above output for 1 sec
        PORTC=0x40;         // setting low for RC1 pin and high for RC6 pin
        __delay_ms(1000);
        PORTC=0x42;         // setting high for both RC1 and RC6 pin
        __delay_ms(1000);
        PORTC=0x00;         // setting low for both RC1 and RC6 pin
        __delay_ms(1000);
    
    }


}