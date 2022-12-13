
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

#define _XTAL_FREQ 6000000    // Setting the Fosc to be 6 MHz

void init();                  // Declaring the init() function 

void main(void) {
    init();
    
    while(1) {
    
        PORTC = 0x08;         // 0000 1000 Setting up the RC3 to HIGH others all to LOW
        __delay_ms(200);     
        PORTC = 0x04;         // 0000 0100 Setting up the RC2 to HIGH others all to LOW
        __delay_ms(200);
        PORTC = 0x02;         // 0000 0010 Setting up the RC1 to HIGH others all to LOW
        __delay_ms(200);      
        PORTC = 0x01;         // 0000 0001 Setting up the RC0 to HIGH others all to LOW
        __delay_ms(200);
        
    }
}

void init() {

    TRISB = 0xF0;             // 1111 0000 PORTB<0:3> to OUTPUT PORTB<4:7> to INPUT
    TRISC = 0x00;             // 0000 0000 PORTC<0:7> to OUTPUT
    PORTB = 0x00;             // Initializing all the PORTB pins to LOW
    PORTC = 0x00;             // Initializing all the PORTC pins to LOW
    OPTION_REG &= ~0x80;      // 0XXX XXXX Setting up the internal pull-ups in PORTB
    INTCON |= 0x88;           // 1XXX 1XXX Initializing the interrupt for port change in PORTB
}

void __interrupt() ISR() {

    while (INTCON & 0x01){      // Checking if the flag bit is set to 1
    
        switch(PORTB) {
        
            case(0x70): {
                PORTC |= 0x80;  // 1XXX XXXX Setting the RC7 to HIGH
                break;
            }
            case(0xB0): {
                PORTC |= 0x40;  // X1XX XXXX Setting the RC6 to HIGH
                break;
            }
            case(0xD0): {
                PORTC |= 0xC0;  // 11XX XXXX Setting the RC7 and RC6 to HIGH
                break;                
            }
            case(0xE0): {
                PORTC |= 0x00;  // XXXX XXXX No change
                break;
            }
            default: {
                INTCON &= ~0x01; // XXXX XXX0 Setting up the flag bit to LOW
            }
        }
    }
    
}