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

void init(void);                          // Declaring the function init
void data(unsigned char);                 // Declaring the data function
void command(unsigned char);              // Declaring the command function
void delay(unsigned int);                 // Declaring the delay function
void conv(unsigned int, unsigned int);    // Declaring the conv function
void sendData(unsigned int);              // Declaring the sendData function

void main(void) {
    init();                      // Calling the init function
    unsigned int dig1 = 987;     // Setting up the input digit 1
    unsigned int dig2 = 683;     // Setting up the input digit 2
    conv(dig1,dig2);             // Calling the conv function 
    while(1);
}

void init(void){
    TRISC = 0x00;                // Setting the PORTC pins to output
    TRISD = 0x00;                // Setting the PORTD pins to output
    command(0x30);               // Function set command
    command(0x30);               // Function set command
    command(0x30);               // Function set command
    command(0x3C);               // Function set command
    command(0x08);               // Display OFF command
    command(0x01);               // Clear display command
    command(0x06);               // Entry mode set
    command(0x0C);               // Display ON command
}

void conv (unsigned int a, unsigned int b) {
    
    unsigned int ans;
    unsigned char sign;
    if (a>=b){
        ans = a-b;               // Answer obtained after subtraction
        sign = '+';
    }
    else {
        ans = b-a;               // Answer obtained after subtraction
        sign = '-';
    }
    command(0x82);               // Setting the cursor position at 0x82
    sendData(a);                 // Printing the dig1 on display
    data('-');
    sendData(b);                 // Printing the dig2 on display
    data('=');
    data(sign);                  // Printing the appropriate sign on display
    sendData(ans);               // Printing the ans on display

}

void sendData(unsigned int i){
    
    unsigned char x=1,y,k[3];
    while (i>0){
        y = i - ((i/10)*10);    // Splitting up the digits
        k[x] = y;               // Storing the digits in the array
        i /= 10;
        x++;                    // incrementing the index
    }
    
    x--;                        // decrementing the index
    
    while (x!=0) {
        data(48+k[x]);          // printing the data using the ASCII value
        x--;                    // decrementing the index
    }
}

void delay(unsigned int k)
{
    while(--k);
}

void data(unsigned char i)
{
    PORTC |= 0x40;              //  x1xx xxxx setting up the RC6 pin 
    PORTD = i;               
    PORTC |= 0x80;              // 1xxx xxxx setting up the RC7 pin
    PORTC &= ~0x80;             // 0xxx xxxx setting low the RC7 pin
    delay(1000);
}

void command(unsigned char i)
{
    PORTC &= ~0x40;              // x0xx xxxx setting low the RC6 pin 
    PORTD = i;
    PORTC |= 0x80;               // 1xxx xxxx setting up the RC7 pin
    PORTC &= ~0x80;              // 0xxx xxxx setting low the RC7 pin
    delay(1000);
}