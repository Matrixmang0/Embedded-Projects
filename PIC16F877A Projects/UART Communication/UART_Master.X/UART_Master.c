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

#define _XTAL_FREQ 6000000      // Setting up the Fosc to 6000000

void init(void);                // Declaring the initi function

unsigned char data;             // Initializing the data variable

void main() {

    init();                         // Calling th init function
    
    while (1) {
      
      unsigned char data = PORTB;   // Assigning the value of PORTB to data variable
      switch(data) {
        
        case(0x0E) : {
            TXREG = 'A';            // Passing the value 'A' to the transmit buffer
            break;  }
        case(0x0D) : {
            TXREG = 'B';            // Passing the value 'B' to the transmit buffer
            break;  }
        case(0x0B) : {
            TXREG = 'C';            // Passing the value 'C' to the transmit buffer
            break;  }   
        case(0x07) :  {
            TXREG = 'D';            // Passing the value 'D' to the transmit buffer
            break;  }
      }
      
      unsigned char led = RCREG;    // Assigning the value of PORTB to led variable
      switch(led) {
          
          case('a'):
              PORTD = 0x02;         // 0000 0010 Setting up the RD1 pin
              break;
          case('b'):
              PORTD = 0x01;         // 0000 0001 Setting up the RD0 pin 
              break;
          case('c'):
              PORTD = 0x00;         // 0000 0010 Setting down both RD0 and RD1 pin
              break;
          case('d'):
              PORTD = 0x03;         // 0000 0011 Setting up both RD0 and RD1 pin
              break;
      
      }
    }
}

void init() {

    TRISB = 0x0F;                   // 0000 1111 Setting the four LSB bits to input other all to output
    PORTB = 0x00;                   // 0000 0000 Initializing all the PORTB pins to zero
    TRISC = 0x80;                   // 1000 0000 Setting the RC7 to input other all to output
    PORTC = 0x00;                   // 0000 0000 Initializing all the PORTC pins to zero  
    TRISD = 0x00;                   // 0000 0000 Setting all the PORTD pins to output
    PORTD = 0x00;                   // 0000 0000 Initializing all the PORTD pins to zero
    
    OPTION_REG &= ~0x80;            // 0111 1111 Setting up the inbuilt pull up registers in the four LSBs of PORTB
    
    TXSTA = 0x20;                   // 0010 0000 Setting up the Transmitter Status and Control register
    RCSTA = 0x90;                   // 1001 0000 Setting up the Receiver Status and Control register
    SPBRG = 0x09;                   // 0000 1001 Setting up the baud rate to 9600
}