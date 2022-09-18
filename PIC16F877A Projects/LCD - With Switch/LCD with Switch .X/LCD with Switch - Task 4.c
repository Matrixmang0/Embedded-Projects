
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

#define _XTAL_FREQ 6000000 // Setting the frequency


void command(unsigned char);      // The function for setting LCD commands
void data(unsigned char);         // The function to send data to the LCD display
void __init__();                  // The function for initializing the display
void calibrate(unsigned int);     // The function for printing the values in desired format to the LCD
void printb(unsigned int);        // The function to display the status w.r.t the value provided

unsigned char Battery[20] = {"BATTERY =      V"};
unsigned char Low[20] = {"Battery Low"};
unsigned char Normal[20] = {"Battery Normal"};
unsigned char High[20] = {"Battery High"};

unsigned int x1, x2, x3;

void main() 
{

__init__();
unsigned int k = 155 ;

while(1)
{
     
unsigned char val = PORTB ;

switch((val)&0xF0)
{
        
case 0xE0 :
{   
    command(0x80);     // Setting cursor position to 1x1 position 
    __delay_ms(100);
    command(0x06);     // Setting the cursor movement to right
    __delay_ms(100);
    for (int i=0;i<16;i++) { data(Battery[i]); }
       
    k = 155;
    calibrate(k);
    printb(k);
    break;
}

case 0xD0 :
{       
    k=k+1;        // Incrementing the value
    if (k>255)
    {k = 255 ;}
    calibrate(k);
    printb(k);
    break;
}

case 0xB0 :
{
    k=k-1;         // Decrementing the value
    if (k<155)
    {k = 155 ;}
    calibrate(k);
    printb(k);
    break;
}

case 0x70 :
{
    k = 155;        // Resetting the value to the original position
    calibrate(k);
    printb(k);
    break;
}      
}        
}
}


void __init__()
{
    TRISC = 0x00;                // Setting all the PORTC pins to output
    TRISB = 0xF0;                // Setting the PORTB pins to both output and input
    
    OPTION_REG &= ~0x80;         // Setting the inbuilt pull-up resistor
    
    command(0x38)  ;             // Setting the function to 2 lines and 5x7 dots
    __delay_ms(100);
    command(0x08)  ;             // Switching OFF the Display
    __delay_ms(100);
    command(0x01)  ;             // Clearing the Display
    __delay_ms(100);
    command(0x0C)  ;             // Hiding the blink and cursor options
    __delay_ms(100);
}
void command(unsigned char i)
{
    PORTB &= ~0x04;              // Setting the RS register to command
    PORTC = i;
    PORTB |= 0x08;               // Setting the enable register to 1
    PORTB &= ~0x08;              // Setting the enable register to 0
    __delay_ms(100);
}

void data(unsigned char i)
{
    PORTB |= 0x04;               // Setting the RS register to data
    PORTC = i;
    PORTB |= 0x08;               // Setting the enable register to 1
    PORTB &= ~0x08;              // Setting the enable register to 0
    __delay_ms(100);
}

void calibrate(unsigned int x)
{
    command(0x8A);               // Placing the cursor at the desired position
    __delay_ms(100);
    command(0x06);               // Setting the cursor movement to right
    __delay_ms(100);
    
    
    x1 = (unsigned char) (x/100) ;             // Digit in the 10s place
    x2 = (unsigned char) ( (x%100)/10 );       // Digit in the 1s place
    x3 = (unsigned char) (x%10);               // Digit in the decimal place
    
    data(0x30+(x1));                           // Sending the value in the ASCII format
    data(0x30+(x2));                           // Sending the value in the ASCII format
    data('.');
    data(0x30+(x3));                           // Sending the value in the ASCII format
} 

void printb(unsigned int m) 
{
    command (0xC1);                           // Placing the cursor at the 2x2 position
    __delay_ms(100);
    command(0x06);                            // Setting the cursor movement to right
    __delay_ms(100);
    
    for (int y=0; y<15; y++)
    {
        if( (m >= 155) && (m <= 174) )
        { data(Low[y]); }
        else if( (m >= 175) && (m <= 204) )
        { data(Normal[y]); }
        else
        { data(High[y]); }
    
    }

}