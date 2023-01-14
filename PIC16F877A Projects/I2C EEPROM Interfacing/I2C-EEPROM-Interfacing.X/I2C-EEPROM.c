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

#include "I2C-EEPROM.h"

#define _XTAL_FREQ 6000000            // Setting up the Fosc to be 6MHz

// Function definition for I2C support functions

void I2C_Init(unsigned long freq) {

    TRISC = 0x18;                 // 0001 1000 Setting RC3 and RC4 to be input others all as output
    PORTC &= ~0xE7;               // 000X X000 Initializing the PORTC pins
    TRISD = 0x00;                 // 0000 0000 Setting up all the PORTD pins to output
    PORTD = 0x00;                 // 0000 0000 Initializing the PORTD pins to 0
    SSPSTAT = 0x00;               // 0000 0000 Initializing the SSPTAT register to 0
    SSPCON2 = 0x00;               // 0000 0000 Initializing the SSPCON2 register to 0
    SSPCON = 0x28;                // 0010 1000 Enabling SDA and SCL as serial port pins, setting up the processor in Master mode
    SSPADD = (_XTAL_FREQ/(4*freq))-1;   //  Holds the Slave address
    
}

void I2C_Wait(void) {

    while((SSPSTAT&(0x04))||(SSPCON2&(0x1F)));   // Holds the flow until transmit completes, Acknowlwdgement received, Acknowlwedgement sequence completes, Receive bit completes, stop condition idle, repeated start condition idle and start condition idle
}

void I2C_Start(void) {

    I2C_Wait();
    SSPCON2 |= 0x01;                 // Sending out Start bit
}

void I2C_Repeatedstart(void) {

    I2C_Wait();
    SSPCON2 |= 0x02;                // Sending out repeated start bit
}

void I2C_Stop(void) {

    I2C_Wait();
    SSPCON2 |= 0x04;                // Sending out the stop bit
}

void I2C_Ack(void) {

    SSPCON2 &= ~0x20;               // 0 Acknowlwedgement bit
    I2C_Wait();
    SSPCON2 |= 0x10;                // Sends the previously loaded bit 
}

void I2C_Nack(void) {

    SSPCON2 |= 0x20;               // 1 Not Acknowledgement bit
    I2C_Wait();
    SSPCON2 |= 0x10;               // Sends the previously loaded bit 
}

unsigned char I2C_Write(unsigned char data) {

    I2C_Wait();
    SSPBUF = data;                // Placing the data over the SSPBUF register
    while(!(PIR1|0x08));          // SSPIF bit is set up if the Stop condition reached
    PIR1 &= ~0x08;                // Clearing the SSPIF bit
    return ACKSTAT;
}

unsigned char I2C_Read(void) {

    I2C_Wait();
    SSPCON2 |= 0x08;              // Sending the repeated start condition bit
    while(!(PIR1|0x08));          // SSPIF bit is set up if the Stop condition reached
    PIR1 &= ~0x08;                // Clearing the SSPIF bit
    I2C_Wait();
    return SSPBUF;
}


// EEPROM Support functions

void EEPROM_Write(unsigned int address, unsigned char data) {

    I2C_Start();                        // Calling the I2C_Start function
    I2C_Write(0xA0);                    // Calling the I2C_Write function with the address slave 0xA0
    I2C_Write(address>>8);              // Calling the I2C_Write function with the MSB register address on the EEPROM
    I2C_Write((unsigned char)address);  // Calling the I2C_Write function with the LSB register address on the EEPROM
    I2C_Write(data);                    // Calling the I2C_Write function with the data to be written on the address
    I2C_Stop();                         // Calling the I2C_stop function
    __delay_ms(1000);
}

void EEPROM_Read(unsigned int address) {

    I2C_Start();                          // Calling the I2C_Start function
    I2C_Write(0xA0);                      // Calling the I2C_Write function with the address slave 0xA0
    I2C_Write(address>>8);                // Calling the I2C_Write function with the MSB register address on the EEPROM
    I2C_Write((unsigned char)address);    // Calling the I2C_Write function with the LSB register address on the EEPROM
    I2C_Repeatedstart();                  // Calling the I2C_Repeatedstart function
    I2C_Write(0xA1);
    unsigned char data = I2C_Read();      // Placing the read data to the variable 'data'
    I2C_Nack();                           // Calling the I2C_Nack function
    I2C_Stop();                           // Calling the I2C_stop function
    PORTD = data;                         // Placing the data to the PORTB
    __delay_ms(1000);   
}