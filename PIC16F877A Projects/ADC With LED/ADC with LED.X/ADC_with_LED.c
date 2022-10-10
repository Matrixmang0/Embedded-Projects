
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

void init(void);                    // Declaring the init functon, which sets the TRIS ports
void data(unsigned char);           // Declaring the function to send printing datas to the LCD
void command(unsigned char);        // Declaring the function to send command datas to the LCD
void display_init(void);            // Declaring the function to set up the LCD
void ADC_init(void);                // Declaring the function to set the ADCON0 and ADCON1 registers 
void LCD_print(unsigned long);      // Declaring the function to calibrate the generated data to print in the LCD
void LED_glow(unsigned long);       // Declaring the function to glow the LEDs at appropriate combination for respective analog values 
unsigned char arr[2];               // Declaring the global run-time array
unsigned long displayVal;           // Declaring the global variable which should be displayed in the LCD
// *The above variable should be only of unsigned long type to correctly glow the LEDs* 

void main() {

    init();                                                       // Calling the init function, which sets the TRIS ports
    ADC_init();                                                   // Calling the function to set the ADCON0 and ADCON1 registers
    display_init();                                               // Calling the function to set up the LCD
    
    while(1) {
        
        ADCON0 = 0x95;                                            // Switching ON the A/D converter bit (ADON) and A/D conversion status bit (GO/DONE)
        while (ADCON0&0x04);                                      // This step completes only when the conversion step completes (i.e) GO/DONE=0
        unsigned int two_MSB = ADRESH;                            // Storing ADRESH register in unsigned int variable
        unsigned int eight_LSB = ADRESL;                          // Storing ADRESL register in unsigned int variable
        unsigned long AnalogVal = (two_MSB << 8) | eight_LSB;     // Combining the data in both the variables and storing it in a single variable
        // *The above variable should be only of unsigned long type to correctly display the value to the LCD* 
        displayVal = ((AnalogVal*100)/1023);                      // Converting the analog value to percentage
        LCD_print(displayVal);                                    // Calling function to print the percentage values to LCD
        LED_glow(displayVal);                                     // Calling function to correctly glow the LEDs
    }
}

void LCD_print(unsigned long value) {
    
    arr[0] = value/100;                                           // Storing the 100s place digit to the 0th index of the array
    arr[1] = ((value%100) - (value%10))/10;                       // Storing the 10s place digit to the 1st index of the array
    arr[2] = value%10;                                            // Storing the 1s place digit to the 2nd index of the array

    command(0x86);                                                // LCD command to start printing from the position 0x86
    for(unsigned char i=0;i<=2;i++) {
        data(arr[i]+48);                                          // Sending the calibrated data to the LCD
        __delay_ms(50);                                           // Delay the process by 50 ms
    }
    data(0);                                                      // printing the null character
    data(37);                                                     // printing the % character
    __delay_ms(50);                                               // Delay the process by 50 ms
}

void LED_glow(unsigned long val) {

    if (val<=25 && val>=0) {
        PORTB|=0x01;                                              // 1xxx xxxx Switching ON the LED at RB0
        PORTB&=~0x02;                                             // x0xx xxxxSwitching OFF the LED at RB1
    }
    else if (val<=50 && val>25) {
        PORTB|=0x02;                                              // x1xx xxxx Switching ON the LED at RB1
        PORTB&=~0x01;                                             // 0xxx xxxx Switching OFF the LED at RB0
    }
    else if (val<=75 && val>50) {
        PORTB|=0x03;                                              // 11xx xxxx Switching ON the LEDs at RB0 and RB1
    }
    else if (val<=100 && val>75) {
        PORTB&=~0x03;                                             // 00xx xxxx Switching OFF the LEDs at RB0 and RB1
    }
}

void init(void) {

    TRISA = 0x04;                                                 // 0000 0100 Setting the RA2/AN2 port to input other all ports to output
    TRISB = ~0xC3;                                                // 0011 1100 Setting the RB0, RB1, RB6, RB7 to output other all ports to input
    TRISD = 0x00;                                                 // 0000 0000 Setting all the port to output in the D register
} 

void display_init(void) {
    
    command(0x30);                                                // 0011 0000 Function set command
    __delay_ms(5);
    command(0x30);                                                // 0011 0000 Function set command
    __delay_ms(1);
    command(0x30);                                                // 0011 0000 Function set command
    command(0x3C);                                                // 0011 1100 Function set command 2-lines and 5x10 dots
    command(0x08);                                                // 0000 1000 Display OFF command
    command(0x01);                                                // 0000 0001 Display clear command
    command(0x06);                                                // 0000 0110 Entry mode set increments the DD RAM address
    command(0x0C);                                                // 0000 1100 Display ON setting cursor blink to OFF
    __delay_ms(50);
}

void ADC_init(void) {

    ADCON0 = 0x90;                                                // 1001 0000 setting Fosc/32, AN2, AD-OFF, AD conversion process-OFF 
    ADCON1 = 0x82;                                                // 10 bit right justified, AN2 is analog along with AN0, AN1, AN3, AN4
}

void data(unsigned char dat) {
    
    PORTB |= 0x40;                                                // x1xx xxxx Setting the register select to 1, setting it to read data mode
    PORTD = dat;                                                  // Sending the actual data to LCD
    PORTB |= 0x80;                                                // 1xxx xxxx Setting the enable bit
    __delay_ms(10);
    // *The data won't be printed without this delay*
    PORTB &= ~0x80;                                               // 0xxx xxxx Clearing the enable bit
    
}

void command(unsigned char com) {
    
    PORTB &= ~0x40;                                               // x0xx xxxx Setting the register select to 0, setting it to read command mode
    PORTD = com;                                                  // Sending the actual data to LCD
    PORTB |= 0x80;                                                // 1xxx xxxx Setting the enable bit
    __delay_ms(10); 
    // *The data won't be printed without this delay*
    PORTB &= ~0x80;                                               // 0xxx xxxx Clearing the enable bit
    
}