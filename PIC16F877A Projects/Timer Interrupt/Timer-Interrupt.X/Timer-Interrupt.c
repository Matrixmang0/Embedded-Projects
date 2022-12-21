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

#define _XTAL_FREQ 6000000   // Setting up the Fosc to be 6MHz


void init();                 // Declaring the init() function
void LED_blink();            // Declaring the LED_blink() function

unsigned int counter;        // Declaring the counter variable


void main(void) {
    init();                 // Calling the init() function
    while(1){
     LED_blink();           // Calling the LED_Blink function
    }
}

void init() {
    

    TRISC = ~0x81;          // 0111 1110 Setting the RC0 and RC7 to OUTPUT others all to INPUT
    PORTC = 0x00;           // 0000 0000 Setting all the bits from PORTC register to LOW
    OPTION_REG &= ~0x38;    // XX00 0XXX T0CS=0, T0SE=0, PSA=0
    OPTION_REG |= 0x07;     // XXXX X111 (PS2,PS1,PS0) = (1,1,1) Setting the prescaler to 1:256
    INTCON |= 0xA0;         // 1X1X XXXX GIE=1, TMR0IE=1
    TMR0 = 0x00;            // 0000 0000 Initializing the TIMER0 to 0
}

void LED_blink() {

    PORTC |= 0x80;          // 1XXX XXXX Setting RC7=1
    __delay_ms(500);
    PORTC &= ~0x80;         // 0XXX XXXX Setting RC7=0
    __delay_ms(500);
    
}

void __interrupt() ISR() {

    if (INTCON & 0x04) {

        counter++;                // Increment the counter variable by 1
        if (counter==46) {
            
            if (PORTC & 0x01) {
            
                PORTC &= ~0x01;   // XXXX XXX0 Setting the RC0=0
            }
            else {
            
                PORTC |= 0x01;    // XXXX XXX1 Setting the RC0=1
            }
            counter = 0;          // Assigning 0 to the variable counter
        }
        INTCON &= ~0x04;          // XXXX X0XX TMR0IF=0 Removing the overflow flag
    }
}


