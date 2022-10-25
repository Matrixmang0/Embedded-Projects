
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

void init(void);                            //Initializing the init function
unsigned char calibrate(unsigned char);     //Initializing the calibrate function
void left(unsigned char);                   //Initializing the left function
void right(unsigned char);                  //Initializing the right function

unsigned char counter;                      //Initializing the counter variable

void main() {

    init();                                 //Calling the init function
    counter = 0;
    calibrate(counter);                     //Calling the calibrate function with counter variable
    while(1){
        unsigned char var = PORTB;          //Declaring the var variable and assigning it to PORTB
        switch (var) {
            
            case(0xFE):                     // 1111 1111 
                counter++;                  // Incrementing the counter variable
                break;
            case(0xFD):                     // 1111 1101
                counter--;                  // Decrementing the counter variable
                break;
        }
        counter = calibrate(counter);       // Update the counter variable to the return value from calibrate function with counter argument 
    }
}

void init() {

    TRISB = 0xFF;                          // 1111 1111 Declaring all the PORTB pins to input
    PORTB = 0x00;                          // 0000 0000 Initializing all the PORTB pins to zero
    TRISC = 0x00;                          // 0000 0000 Declaring all the PORTC pins to output
    PORTC = 0x00;                          // 0000 0000 Initializing all the PORTC pins to zero
    TRISD = 0x00;                          // 0000 0000 Declaring all the PORTD pins to output
    PORTD = 0x00;                          // 0000 0000 Initializing all the PORTD pins to zero
    OPTION_REG &= ~0x80;                   // 0111 1111 Setting the internal pull up register in PORTB
}

unsigned char calibrate(unsigned char counter) {

    if (counter < 0) {
        counter = 0;
    }
    else if (counter > 99){
        counter = 99;
    }
    
    unsigned char rdig = (counter%10);          // Separating the 1's digit
    unsigned char ldig = ((counter-rdig)/10);   // Separating the 10's digit
    
    left(ldig);                                 // Calling the left function with ldig argument
    right(rdig);                                // Calling the right function with rdig argument
    
    return counter;                             // Returning the counter variable
}

void left(unsigned char l) {

    unsigned char arr[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x98};  // Assigning the byte value at the respective indices
    PORTC = arr[l];                                                               // Assigning the the specific called index value to PORTC
}

void right(unsigned char r) {

    unsigned char arr[10] = {0x3F,0x30,0x6D,0x79,0x72,0x5B,0x5F,0x31,0x7F,0x73};  // Assigning the byte value at the respective indices
    PORTD = arr[r];                                                               // Assigning the the specific called index value to PORTC
}