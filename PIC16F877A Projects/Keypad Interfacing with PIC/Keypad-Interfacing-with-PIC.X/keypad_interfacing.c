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


#define _XTAL_FREQ 6000000       // Setting the Fosc to be 6MHz

unsigned char cnt;               // Initializing the variable cnt

void keypad_init(void);          // Declaring the keypad_init function
void LCD_init(void);             // Declaring the LCD_init function

void check_LCD(void);            // Declaring the check_LCD function

char keypad_scan(void);          // Declaring the keypad_scan function

void command(unsigned char) ;   // Initializing the command function
void data(unsigned char);       // Initializing the data function

void main() {

    keypad_init();              // Calling the keypad_init function
    LCD_init();                 // Calling the LCD_init function
    char pressed = 'x';         // This acts as the default state when no key is pressed
    while(1) {
        pressed = keypad_scan(); // Updating the pressed variable to the output of the function keypad_scan
        if (pressed != 'x') {    // Checks if any key is pressed
            check_LCD();         // Calling the check_LCD function
            data(pressed);       // pushing the pressed data to the LCD
        }
    }
}

void keypad_init() {

    TRISB = 0x07;                 // 0000 0111 Setting the Last three LSBs to be input others all to output
    OPTION_REG &= 0x7F;           // 1XXX XXXX Setting up the pull-up resistor in PORTB
    PORTB = 0x00;                 // 0000 0000 Initializing the PORTB pins to 0
}

void LCD_init(){

    TRISD = 0x00 ;               // Setting all the pins in PORTB to output 
    TRISC = 0x00 ;               // Setting all the pins in PORTC to output
    PORTC = 0x00 ;               // 0000 0000 Initializing the PORTC pins to 0
    PORTD = 0x00 ;               // 0000 0000 Initializing the PORTD pins to 0
    
    command(0x38)  ;             // Setting the function to 2 lines and 5x7 dots
    __delay_ms(10);
    command(0x08)  ;             // Switching OFF the Display
    __delay_ms(10);
    command(0x01)  ;             // Clearing the Display
    __delay_ms(10);
    command(0x0C)  ;             // Hiding the blink and cursor options
    __delay_ms(10);
    command(0x80);               // The command to start from 1x1 matrix
    __delay_ms(10);
    command(0x06);               // The command to move the cursor rightwards
    __delay_ms(10);

}

void check_LCD(void) {

    cnt++;                       // Increase the cnt variable by 1

    if (cnt==17) {
        command(0xC0);           // The command to start from 2x1 matrix
    }
    else if (cnt==33) {
    
        command(0x01);           // Clearing the Display
        command(0x80);           // The command to start from 1x1 matrix
        cnt=0;                   // Updating the cnt variable to 0
    }
    
}

char keypad_scan() {

    PORTB |= 0x70;                       // X111 XXXX Setting HIGH the 2nd, 3rd and 4th row
    PORTB &= ~0x08;                      // XXXX 0XXX Setting LOW the first row
    if ((PORTB&0x04)==0x00){
        __delay_ms(100);
        if (~(PORTB&0x04)){              // Checks if the key 1 is still pressed
            while((PORTB&0x04)==0x00);   // Holds till the key 1 is pressed
            return '1';                  // Return the character '1'
        }    
    }
    else if ((PORTB&0x02)==0x00){
        __delay_ms(100);
        if (~(PORTB&0x02)){              // Checks if the key 2 is still pressed
            while((PORTB&0x02)==0x00);   // Holds till the key 2 is pressed
            return '2';                  // Return the character '2'
        }         
    }
    else if ((PORTB&0x01)==0x00){
        __delay_ms(100);
        if (~(PORTB&0x01)){              // Checks if the key 3 is still pressed
            while((PORTB&0x01)==0x00);   // Holds till the key 3 is pressed
            return '3';                  // Return the character '3'
        }        
    }
    
    
    PORTB |= 0x68;                       // X11X 1XXX Setting HIGH the 1st, 3rd and 4th row
    PORTB &= ~0x10;                      // XXX0 XXXX Setting LOW the 2nd row
    if ((PORTB&0x04)==0x00){
        __delay_ms(100);
        if (~(PORTB&0x04)){              // Checks if the key 4 is still pressed
            while((PORTB&0x04)==0x00);   // Holds till the key 4 is pressed
            return '4';                  // Return the character '4'
        }        
    }
    else if ((PORTB&0x02)==0x00){
        __delay_ms(100);
        if (~(PORTB&0x02)){              // Checks if the key 5 is still pressed
            while((PORTB&0x02)==0x00);   // Holds till the key 5 is pressed
            return '5';                  // Return the character '5'
        }         
    }
    else if ((PORTB&0x01)==0x00){
        __delay_ms(100);
        if (~(PORTB&0x01)){              // Checks if the key 6 is still pressed
            while((PORTB&0x01)==0x00);   // Holds till the key 6 is pressed
            return '6';                  // Return the character '6'
        }        
    }
    
    PORTB |= 0x58;                       // X1X1 1XXX Setting HIGH the 1st, 2nd and 4th row
    PORTB &= ~0x20;                      // XX0X XXXX Setting LOW the 3rd row
    if ((PORTB&0x04)==0x00){
        __delay_ms(100);
        if (~(PORTB&0x04)){               // Checks if the key 7 is still pressed
            while((PORTB&0x04)==0x00);    // Holds till the key 7 is pressed
            return '7';                   // Return the character '7'
        }         
    }
    else if ((PORTB&0x02)==0x00){
        __delay_ms(100);
        if (~(PORTB&0x02)){               // Checks if the key 8 is still pressed
            while((PORTB&0x02)==0x00);    // Holds till the key 8 is pressed
            return '8';                   // Return the character '8'
        }         
    }
    else if ((PORTB&0x01)==0x00){
        __delay_ms(100);
        if (~(PORTB&0x01)){               // Checks if the key 9 is still pressed
            while((PORTB&0x01)==0x00);    // Holds till the key 9 is pressed
            return '9';                   // Return the character '9'
        }         
    }
    
    PORTB |= 0x38;                        // XX11 1XXX Setting HIGH the 1st, 2nd and 3rd row
    PORTB &= ~0x40;                       // X0XX XXXX Setting LOW the 4th row
    if ((PORTB&0x04)==0x00){
        __delay_ms(100);
        if (~(PORTB&0x04)){                // Checks if the key * is still pressed
            while((PORTB&0x04)==0x00);     // Holds till the key * is pressed
            return '*';                    // Return the character '*'
        }        
    }
    else if ((PORTB&0x02)==0x00){
        __delay_ms(100);
        if (~(PORTB&0x02)){                // Checks if the key 0 is still pressed
            while((PORTB&0x02)==0x00);     // Holds till the key 0 is pressed
            return '0';                    // Return the character '0'
        }         
    }
    else if ((PORTB&0x01)==0x00){
        __delay_ms(100);
        if (~(PORTB&0x01)){                 // Checks if the key 1 is still pressed
            while((PORTB&0x01)==0x00);      // Holds till the key 1 is pressed
            return '#';                     // Return the character '1'
        }        
    }   
    
    return 'x';
}

void command(unsigned char m)
{
   PORTC = 0x00 ;                // Setting the RS pin to 0 (i.e) to command mode 
   PORTD = m ;
   PORTC = 0x80 ;                // Switching the enable pin to 1
   PORTC = 0x00 ;                // Switching the enable pin to 0
   __delay_ms(100);

}

void data(unsigned char n)
{
   PORTC = 0x20 ;                 // Setting the RS pin to 1 (i.e) to data mode
   PORTD = n ;
   PORTC = 0xA0 ;                 // Switching the enable pin to 1
   PORTC = 0x20 ;                 // Switching the enable pin to 0
   __delay_ms(100);

}