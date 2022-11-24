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

#define _XTAL_FREQ 6000000       // Setting up the Fosc to 6MHz

unsigned int data;               // Declaring the variable data 
void init();                     // Declaring the init function

void main() {
    
    init();                      // Calling the init function
    while(1) {
        data = PORTB;
        switch(data) {
    
            case(0x0E):{         // 0000 1110
              TXREG = 'A';
              break;
            }
            case(0x0D):{
              TXREG = 'B';      // 0000 1101
              break;
            }
            case(0x0B):{        // 0000 1011 
              TXREG = 'C';
              break;
            }
            case(0x07): {       // 0000 0111
              TXREG = 'D';
              break;
            }
        } 
    }

}

void init() {

    TRISB = 0x0F;              // 0000 1111 Setting the four LSBs of PORTB to INPUT 
    PORTB = 0x00;              // 0000 0000 Initializing all the PORTB pins to 0
    
    OPTION_REG &= ~0x80;       // 0111 1111 Setting up the internal pull up resistors at four LSBs in PORTB
    
    TXSTA = 0x20;              // 0010 0000 Setting up the Transmitter Status and Control register
    RCSTA = 0x90;              // 1001 0000 Setting up the Receiver Status and Control register
    SPBRG = 0x09;              // 0000 1001 Setting up the baud rate to be 9600
}