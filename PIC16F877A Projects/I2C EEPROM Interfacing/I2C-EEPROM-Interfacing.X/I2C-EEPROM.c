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

#define _XTAL_FREQ 6000000

// Function definition for I2C support functions

void I2C_Init(unsigned long freq) {

    TRISC = 0x18;
    PORTC &= ~0xE7;
    TRISD = 0x00;
    PORTD = 0x00;
    SSPSTAT = 0x00;
    SSPCON2 = 0x00;
    SSPCON = 0x28;
    SSPADD = (_XTAL_FREQ/(4*freq))-1;
    
}

void I2C_Wait(void) {

    while((SSPSTAT&(0x04))||(SSPCON2&(0x1F)));
}

void I2C_Start(void) {

    I2C_Wait();
    SSPCON2 |= 0x01;
}

void I2C_Repeatedstart(void) {

    I2C_Wait();
    SSPCON2 |= 0x02;
}

void I2C_Stop(void) {

    I2C_Wait();
    SSPCON2 |= 0x04;
}

void I2C_Ack(void) {

    SSPCON2 &= ~0x20;
    I2C_Wait();
    SSPCON2 |= 0x10;
}

void I2C_Nack(void) {

    SSPCON2 |= 0x20;
    I2C_Wait();
    SSPCON2 |= 0x10;
}

unsigned char I2C_Write(unsigned char data) {

    I2C_Wait();
    SSPBUF = data;
    while(!(PIR1|0x08));
    PIR1 &= ~0x08;
    return ACKSTAT;
}

unsigned char I2C_Read(void) {

    I2C_Wait();
    SSPCON2 |= 0x08;
    while(!(PIR1|0x08));
    PIR1 &= ~0x08;
    I2C_Wait();
    return SSPBUF;
}


// EEPROM Support functions

void EEPROM_Write(unsigned int address, unsigned char data) {

    I2C_Start();
    I2C_Write(0xA0);
    I2C_Write(address>>8);
    I2C_Write((unsigned char)address);
    I2C_Write(data);
    I2C_Stop();
    __delay_ms(1000);
}

void EEPROM_Read(unsigned int address) {

    I2C_Start();
    I2C_Write(0xA0);
    I2C_Write(address>>8);
    I2C_Write((unsigned char)address);
    I2C_Repeatedstart();
    I2C_Write(0xA1);
    unsigned char data = I2C_Read();
    I2C_Nack();
    I2C_Stop();
    PORTD = data;
    __delay_ms(1000);   
}