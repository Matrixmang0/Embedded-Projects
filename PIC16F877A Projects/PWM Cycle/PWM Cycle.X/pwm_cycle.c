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

void init(void);      // Initializing the function init
void pwmCycle(void);  // Initializing the function pwmCycle
unsigned char R1L20, CON20, R1L60, CON60, R1L90, CON90;  // Initializing the variables to store the values for the corresponding duty cycle to the corresponding CCPR1l or CCP1CON reg

void main() {
    init();
    while(1) {
        pwmCycle();   // This function will be executing in loop
    }
}

void init() {
    
    TRISC = ~0x04;     // 1111 1011  setting RC2 pin as output as that is the PWM pin 
    CCPR1L = 0x00;     // 0000 0000 Just initializing a dummy value to the CCPR1L reg
    CCP1CON = 0x0F;    // --00 11xx Setting dummy values to CCP1X and CCP1Y, setting the PWM mode
    T2CON = 0x06;      // -000 011x Setting the Timer2 to ON, prescalar to 16 and postscale 1:1
    PR2 = 0x2F;        // 0010 1111 Setting the period value to 47
    
    R1L20 = 0x09;      // 0000 1001 Split first 6 MSB of 38
    CON20 = 0x2F;      // --10 11xx Setting up PWM mode, 2 LSB 10
    
    R1L60 = 0x1C;      // 0001 1100 Split first 6 MSB of 113
    CON60 = 0x1F;      // --01 11xx Setting up PWM mode, 2 LSB 01
    
    R1L90 = 0x2A;      // 0010 1010 Split first 6 MSB of 169
    CON90 = 0x1F;      // --01 11xx Setting up PWM mode, 2 LSB 01
    
}

void pwmCycle() {

    CCPR1L = R1L20;   // Setting the value for 20% duty cycle to CCPR1L reg
    CCP1CON = CON20;  // Setting the value for 20% duty cycle to CCPCON reg, also setting PWM mode
    __delay_ms(3000); // Holding up the output for 3 seconds
    
    CCPR1L = R1L60;   // Setting the value for 60% duty cycle to CCPR1L reg
    CCP1CON = CON60;  // Setting the value for 60% duty cycle to CCPCON reg, also setting PWM mode
    __delay_ms(3000); // Holding up the output for 3 seconds
    
    CCPR1L = R1L90;   // Setting the value for 90% duty cycle to CCPR1L reg
    CCP1CON = CON90;  // Setting the value for 90% duty cycle to CCPCON reg, also setting PWM mode
    __delay_ms(3000); // Holding up the output for 3 seconds
}