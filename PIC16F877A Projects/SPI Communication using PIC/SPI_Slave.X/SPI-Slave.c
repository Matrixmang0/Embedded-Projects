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

#define _XTAL_FREQ 6000000

void LED_INIT(void);                // Function to initialize and set up the pins for LED and Switch
void SPI_SLAVE_INIT(void);          // Function to initialize the the pins and register for SPI Slave mode

void main() {
    
    LED_INIT();                     // Calling the function to initialize and set up the pins for LED and Switch
    SPI_SLAVE_INIT();               // Calling the function to initialize the the pins and register for SPI Slave mode
    
    while(1) {
        
        if (SSPSTAT&0x01) {         // XXXX XXX1 Checcking if BF=1 (Receive is complete or SSPBUF is full) 
            PORTB = SSPBUF;         // Transferring the data from SSPBUF to showup LED to check if the data is correctly received
            
            // XXXX XXX0 BF=0 Setting down the data receive flag
            SSPSTAT&=~0x01;
            
            // X0XX XXXX SSPOV=0 Used in only slave mode - Receive overflow indicator bit (Clearing this bit after receiving the data) 
            SSPCON &=~0x40;
        }
    
    }
}

void LED_INIT(void) {

    TRISB = 0x00;                   // 0000 0000 Setting the PORTB pins to output
    PORTB = 0x00;                   // 0000 0000 Initializing the PORTB pins to zero
    
}

void SPI_SLAVE_INIT(void) {

    TRISC = 0x18;                  // 0001 1000 Setting the RC3 and RC4 as INPUT others all to OUTPUT
    PORTC = 0x00;                  // 0000 0000 Initializing the PORTC pins to zero
    
    // XXXX 0100 Setting the SPI mode to slave and ~SS pin control enabled
    // XX1X XXXX SSPEN=1 Enables serial port and configures SCK, SDO, SDI & ~SS as Serial port pins
    // XXX1 XXXX CKP=1 Clock polarity select bit (IDLE state for clock is HIGH)
    SSPCON &= ~0x0B;               // XXXX 0X00
    SSPCON |= 0x34;                // XX11 X1XX
    
    // 0XXX XXXX SMP=0 Sample bit (In master mode input is sampled at middle of the data output time)
    // X1XX XXXX CKE=1 SPI CLock Select bit (Transmit occurs on transmission from Idle to active clock state)
    SSPSTAT &= ~0x80;              // 0XXX XXXX
    SSPSTAT |= 0x40;               // X1XX XXXX
}

