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

void LED_SWITCH_INIT(void);               // Function to initialize and set up the pins for LED and Switch
void SPI_MASTER_INIT(void);               // Function to Initialize and set up the controller to SPI mode
void SPI_WRITE(unsigned char);            // Function to write data to the Slave

void main(void) {
    
    LED_SWITCH_INIT();                    // Calling the function to initialize and setup the pins for LED and Switch
    SPI_MASTER_INIT();                    // Calling the function to initialize and set up the controller to SPI mode
    unsigned char data = 0;               // Declaring the variable to hold the data to be transferred
    
    while(1) {
    
        if (RB2==0) {                     // Checking if XX0X XXXX (Checking if Switch1 is pressed)
        
            data++;                       // If Switch1 is pressed increment the data variable by 1
            PORTD = data;                 // LEDs show up to check the input
            __delay_ms(200);
        }
        else if (RB1==0) {                // Checking if X0XX XXXX (Checking if Switch2 is pressed)
        
            data--;                       // If Switch1 is pressed decrement the data variable by 1
            PORTD = data;                 // LEDs show up to check the input
            __delay_ms(200);
        }
        else if (RB0==0) {                // Checking if 0XXX XXXX (Checking if Switch3 is pressed)
        
            SPI_WRITE(data);              // Send the data to the slave
            __delay_ms(200);
            // The below statement is because, the data is only sent if we press the switch3 twice
            SPI_WRITE(data);
        }
    }
}

void LED_SWITCH_INIT(void) {

    TRISD = 0x00;              // 0000 0000 Declaring all the PORTD pins to OUTPUT
    PORTD = 0x00;              // 0000 0000 Initializing the PORTD pins to zero
    TRISB = 0x07;              // 0000 0111 Declaring the RB0, RB1, RB2 pins to INPUT other all pins to OUTPUT 
    PORTB = 0x00;              // 0000 0000 Initializing the PORTB pins to zero
    OPTION_REG &= ~0x80;       // 0XXX XXXX Setting up the internal pull-up resistors in PORTB
    
}

void SPI_MASTER_INIT(void) {

    TRISC = 0x10;             // 1000 0000 Declaring the RC7 to INPUT Others all to OUTPUT
    PORTC = 0x00;             // 0000 0000 Initializing all the PORTC pins to zero
    
    // XXXX 0001 SPI MASTER MODE and Clock = Fosc/16
    // XX1X XXXX SSPEN=1 Enables serial port and configures SCK, SDO, SDI & ~SS as Serial port pins
    // XXX1 XXXX CKP=1 Clock polarity select bit (IDLE state for clock is HIGH)
    SSPCON &= ~0x0E;          // XXXX 000X
    SSPCON |= 0x31;           // XX11 XXX1
    
    // 0XXX XXXX SMP=0 Sample bit (In master mode input is sampled at middle of the data output time)
    // X1XX XXXX CKE=1 SPI CLock Select bit (Transmit occurs on transmission from Idle to active clock state)
    SSPSTAT &= 0x7F;          // 0XXX XXXX
    SSPSTAT |= 0x40;          // X1XX XXXX
    
}

void SPI_WRITE(unsigned char data) {

    // Writing the data to the Transmit buffer register which will push the data to the Slave
    SSPBUF = data;
    //while((SSPSTAT &= 0x01) == 0);
  
}