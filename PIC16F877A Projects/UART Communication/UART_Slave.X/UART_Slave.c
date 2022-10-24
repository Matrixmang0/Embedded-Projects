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

#define _XTAL_FREQ 6000000           // Setting up the oscillation frequency

void init(void);                     // Declaring the init function
void displayUp(unsigned char);       // Declaring the displayUp function
void displayDown(unsigned char);     // Declaring the displayDown function
void lcd_init(void);                 // Declaring the lcd_init function
void command(unsigned char);         // Declaring the command function
void data(unsigned char);            // Declaring the data function

unsigned int rxd;                    // Declaring the rxd variable

void main() {

    init();                          // Calling the init function
    lcd_init();                      // Calling the lcd_init function
    
    while(1) {
        
        unsigned int rxd = RCREG ;   // Assigning value of RCREG register to rxd variable
        switch(rxd) {
        
            case('A'):{
                TXREG = 'a';         // Assigning 'a' to the TXREG register
                displayUp(rxd);      // Calling the displayUp function with the argument rxd
                displayDown('a');    // Calling the displayDown function with the argument 'a'
                break;}
            case('B'):{
                TXREG = 'b';         // Assigning 'b' to the TXREG register
                displayUp(rxd);      // Calling the displayUp function with the argument rxd
                displayDown('b');    // Calling the displayDown function with the argument 'b' 
                break;}
            case('C'):{
                TXREG = 'c';         // Assigning 'c' to the TXREG register
                displayUp(rxd);      // Calling the displayUp function with the argument rxd
                displayDown('c');    // Calling the displayDown function with the argument 'c'
                break;}
            case('D'):{
                TXREG = 'd';         // Assigning 'd' to the TXREG register
                displayUp(rxd);      // Calling the displayUp function with the argument rxd
                displayDown('d');    // Calling the displayDown function with the argument 'd'
                break;}
        }
    }

}

void displayUp(unsigned char dat) {

    command(0x80);                           // Calling the command function with argument 1000 0000
    unsigned char arr[] = {"RECEIVED : "};
    
    for(int i=0; i<=10; i++) {
        
        data(arr[i]);                        // Calling the data function with each character of array as argument
    }
    data(dat);                               // Calling the data function with the received data as argument
}

void displayDown(unsigned char dat) {

    command(0xC0);                           // Calling the command function with argument 1100 0000
    unsigned char arr[] = {"SENT     : "};
    
    for(int i=0; i<=10; i++) {
        
        data(arr[i]);                        // Calling the data function with each character of array as argument
    }
    data(dat);                               // Calling the data function with the transmitted data as argument
}


void init() {
   
    TRISB = 0x00;                           // 0000 0000 Setting all the portB pins to output
    PORTB = 0x00;                           // 0000 0000 Initializing all the portB pins to zero
    TRISC = 0x80;                           // 1000 0000 Setting RC7 to input other all pins to output
    PORTC = 0x00;                           // 0000 0000 Initializing all the PortC pins to zero
    
    TXSTA = 0x20;                           // 0010 0000 Setting up the Transmitter status and control register
    RCSTA = 0x90;                           // 1001 0000 Setting up the receiver status and control register
    SPBRG = 0x09;                           // 0000 1001 Setting up the baud rate to 9600
}
void lcd_init() {
    command(0x30);                          // 0011 0000 Function set command
    __delay_ms(10);
    command(0x30);                          // 0011 0000 Function set command
    __delay_ms(1);
    command(0x30);                          // 0011 0000 Function set command
    command(0x3C);                          // 0011 1100 Function set 
    command(0x08);                          // 0000 1000 Display OFF
    command(0x01);                          // 0000 0001 Clear Display
    command(0x06);                          // 0000 0110 Entry mode set
    command(0x0C);                          // 0000 1100 Display ON
}
void command(unsigned char a)
{
    PORTC &= ~0x02;                         // xxxx xx0x  RS=0 Setting up the LCD mode to command
    PORTB = a;                              // Assigning the argument to the portB
    PORTC |= 0x01;                          // xxxx xxx1 Setting up the enable bit
    __delay_ms(10);
    PORTC &= ~0x01;                         // xxxx xxx0 Setting down the enable bit
}

void data(unsigned char a)
{
    PORTC |= 0x02;                          // xxxx xx1x RS=1 Setting up the LCD mode to data 
    PORTB = a;                              // Assigning the argument to the portB
    PORTC |= 0x01;                          // xxxx xxx1 Setting up the enable bit
    __delay_ms(10);
    PORTC &= ~0x01;                         // xxxx xxx0 Setting down the enable bit
}
