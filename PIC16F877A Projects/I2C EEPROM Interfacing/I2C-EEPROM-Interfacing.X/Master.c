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

void main(void) {

    I2C_Init(100000);
    
    EEPROM_Write(0x0023, 'A'); // Writing data 'A' onto the address 0x0023 on the EEPROM
    EEPROM_Write(0x0028, 'B'); // Writing data 'B' onto the address 0x0028 on the EEPROM
    EEPROM_Write(0x0036, 'C'); // Writing data 'C' onto the address 0x0036 on the EEPROM
    
    EEPROM_Read(0x0023);       // Reading data from the address 0x0023 on the EEPROM
    EEPROM_Read(0x0028);       // Writing data from the address 0x0028 on the EEPROM
    EEPROM_Read(0x0036);       // Writing data from the address 0x0036 on the EEPROM
    
    while(1);                  // Holding the flow here 
}
