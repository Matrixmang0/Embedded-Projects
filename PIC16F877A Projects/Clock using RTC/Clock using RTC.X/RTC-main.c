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

#define _XTAL_FREQ 6000000                        // Setting up the Fosc frequency to 6MHz

void LCD_init(void);                              // functions to initialize the 16x2 LCD
void command(unsigned char);                      // functions to command the LCD
void data(unsigned char);                         // function to write data onto LCD display

// I2C support functions

void I2C_Init(unsigned long);                      //  Initializing the I2C
void I2C_Start(void);                              //  Sending out the Start bit
void I2C_Repeatedstart(void);                      //  Sending out the Repeated Start bit   
void I2C_Stop(void);                               //  Sending out the Stop bit
void I2C_Wait(void);                               //  Wait till all the process completes
void I2C_Ack(void);                                //  Sending out the acknowledgement bit
void I2C_Nack(void);                               //  Sending out the Not acknowledgement bit
unsigned char I2C_Write(unsigned char);            //  I2C Write operation
unsigned char I2C_Read(void);                      //  I2C Read operation

void RTC_Write(unsigned char);                     // Function to set time onto the DS3232 RTC
void RTC_Read(unsigned char);                      // Function to read time onto the DS3232 RTC

unsigned char Hexa_to_BCD(unsigned char);          // Function to convert the data format from Hexadecimal to BCD

void set_sec(unsigned char);                       // Function to set up seconds onto the array wr_time 
void set_min(unsigned char);                       // Function to set up minute onto the array wr_time 
void set_hour(unsigned char, unsigned char);       // Function to set up hour onto the array wr_time 
void set_day(unsigned char);                       // Function to set up day onto the array wr_time 
void set_date(unsigned char);                      // Function to set up date onto the array wr_time 
void set_mon(unsigned char);                       // Function to set up month onto the array wr_time 
void set_year(unsigned char);                      // Function to set up year onto the array wr_time 


void set_time(unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);  // Function to setup the entire time onto the DS3232 RTC

void LCD_display(void);                            // Function which aggregates all the functions to fetch the time from rd_time array to LCD display
void display_min(unsigned char);                   // Function to display the minute onto LCD from array rd_time
void display_sec(unsigned char);                   // Function to display the seconds onto LCD from array rd_time
void display_date(unsigned char);                  // Function to display the date onto LCD from array rd_time
void display_hr(unsigned char);                    // Function to display the hour onto LCD from array rd_time
void display_mon(unsigned char);                   // Function to display the month onto LCD from array rd_time
void display_year(unsigned char);                  // Function to display the year onto LCD from array rd_time
void display_day(unsigned char);                   // Function to display the day onto LCD from array rd_time

unsigned char MSB(unsigned char);                  // Function to split the 4-bit MSB nibble of a 8-bit char to a whole new 8-bit char datatype
unsigned char LSB(unsigned char);                  // Function to split the 4-bit MSB nibble of a 8-bit char to a whole new 8-bit char datatype

unsigned char rd_time[];                           // Array to hold all the time units to display the time onto LCD display fetched from RTC DS3232
unsigned char wr_time[];                           // Array to hold all the time units to set up the time onto the RTC DS3232

void main(void) {
    
    
    LCD_init();                                    // Calling the function to set-up the LCD modes
    set_time(34, 59, 12, 0, 6, 21, 12, 24);        // Calling the function to place all the units of time onto an array wr_time
    
    I2C_Init(100000);                              // Calling the function to initialize the I2C transmission process
    RTC_Write(0x00);                               // Function to write all the units from the array wr_time to the RTC DS3232
    
    while(1){
        RTC_Read(0x00);                            // Function to read the time units from the DS3232 RTC onto an array rd_time
        LCD_display();                             // Function to display all the units from the array to the LCD display
    }
}

void set_time(unsigned char sec, unsigned char min, unsigned char hour, unsigned char state, unsigned char day, unsigned char date, unsigned char mon, unsigned char year) {

    set_sec(sec);                                  // Function the assign the BCD converted seconds data to the wr_time array
    set_min(min);                                  // Function the assign the BCD converted minutes data to the wr_time array
    set_hour(hour, state);                         // Function the assign the BCD converted hour data to the wr_time array
    set_day(day);                                  // Function the assign the BCD converted day data to the wr_time array
    set_date(date);                                // Function the assign the BCD converted date data to the wr_time array
    set_mon(mon);                                  // Function the assign the BCD converted months data to the wr_time array
    set_year(year);                                // Function the assign the BCD converted years data to the wr_time array
}

void LCD_display(void) {

    display_hr(rd_time[2]);                        // Function to display the hours data from the rd_time array to the LCD display
    display_min(rd_time[1]);                       // Function to display the minutes data from the rd_time array to the LCD display
    display_sec(rd_time[0]);                       // Function to display the seconds data from the rd_time array to the LCD display     
    display_date(rd_time[4]);                      // Function to display the dates data from the rd_time array to the LCD display
    display_mon(rd_time[5]);                       // Function to display the months data from the rd_time array to the LCD display
    display_year(rd_time[6]);                      // Function to display the years data from the rd_time array to the LCD display
    display_day(rd_time[3]);                       // Function to display the days data from the rd_time array to the LCD display
}

void display_year(unsigned char year) {

    data('2');
    data('0');
    data(MSB(year)+0x30);                          // Taking the MSB data from the year variable on BCD format and printing out on LCD
    data(LSB(year)+0x30);                          // Taking the LSB data from the year variable on BCD format and printing out on LCD
    data(' ');
}

void display_day(unsigned char day) {

    switch(day) {
    
        case(1): 
            data('S');data('U');data('N');break;   // Printing out 'SUN' data onto the LCD
        case(2):
            data('M');data('O');data('N');break;   // Printing out 'MON' data onto the LCD
        case(3): 
            data('T');data('U');data('E');break;   // Printing out 'TUE' data onto the LCD
        case(4): 
            data('W');data('E');data('D');break;   // Printing out 'WED' data onto the LCD
        case(5): 
            data('T');data('H');data('U');break;   // Printing out 'THU' data onto the LCD
        case(6): 
            data('F');data('R');data('I');break;   // Printing out 'FRI' data onto the LCD
        case(7): 
            data('S');data('A');data('T');break;   // Printing out 'SAT' data onto the LCD
 
    }
    
}

void display_mon(unsigned char mon) {

    mon &= ~0x80;                                  // 0XXX XXXX zeroing out the 8th bit to clear any information on century
    mon = (10*(MSB(mon))) + LSB(mon);              // Converting the BCD formatted data into original Hexadecimal format
    switch(mon) {
    
        case(1): 
            data('J');data('A');data('N');break;   // Printing out 'JAN' data onto the LCD
        case(2):
            data('F');data('E');data('B');break;   // Printing out 'FEB' data onto the LCD
        case(3): 
            data('M');data('A');data('R');break;   // Printing out 'MAR' data onto the LCD
        case(4): 
            data('A');data('P');data('R');break;   // Printing out 'APR' data onto the LCD
        case(5): 
            data('M');data('A');data('Y');break;   // Printing out 'MAY' data onto the LCD
        case(6): 
            data('J');data('U');data('N');break;   // Printing out 'JUN' data onto the LCD
        case(7): 
            data('J');data('U');data('L');break;   // Printing out 'JUL' data onto the LCD
        case(8): 
            data('A');data('U');data('G');break;   // Printing out 'AUG' data onto the LCD
        case(9): 
            data('S');data('E');data('P');break;   // Printing out 'SEP' data onto the LCD
        case(10): 
            data('O');data('C');data('T');break;   // Printing out 'OCT' data onto the LCD
        case(11): 
            data('N');data('O');data('V');break;   // Printing out 'NOV' data onto the LCD
        case(12): 
            data('D');data('E');data('C');break;   // Printing out 'DEC' data onto the LCD
    }
    
    data(' ');                                     // Printing out empty space onto the LCD
}

void display_date(unsigned char date) {

    command(0xC0);                                 // Setting the start position at 2x1 position of the LCD
    data(MSB(date)+0x30);                          // Printing the MSB part of the date to the LCD
    data(LSB(date)+0x30);                          // Printing the LSB part of the date to the LCD
    data(' ');
}

void display_min(unsigned char min){

    data(MSB(min)+0x30);                           // Printing the MSB part of the minutes to the LCD
    data(LSB(min)+0x30);                           // Printing the MSB part of the minutes to the LCD
    data(':');
}

void display_sec(unsigned char sec){

    data(MSB(sec)+0x30);                           // Printing the MSB part of the seconds to the LCD                      
    data(LSB(sec)+0x30);                           // Printing the LSB part of the seconds to the LCD
    data(' ');
}

void display_hr(unsigned char hour) {

    command(0x80);                                 // Setting the start position at 1x1 position of the LCD
    unsigned char time[] = {"TIME:"};
    for (char i=0;i<5;i++){
    
        data(time[i]);
    }
    
    if ((hour&0x40)==0x00) {                       // X0XX XXXX Checks if the hour data in 24-hr format
    
       data(MSB(hour)+0x30);                       // Printing the MSB part of the hours to the LCD
       data(LSB(hour)+0x30);                       // Printing the LSB part of the hours to the LCD
    }
    else {
    
        hour &= ~0x40;                             // X0XX XXXX As this block is for 12-hrs format setting down the bit for 12-hr format
        command(0x8E);                             // Setting the start position at 1x14 position of the LCD
        if ((hour&0x20)==0x00) {                   // XX0X XXXX Checks if the 12-hours data is in PM
        
            data('A');
            data('M');
        }
        else {
        
            hour &= ~0x20;                         // XX0X XXXX As this block is for AM format setting down the bit for AM indication
            data('P');
            data('M');
        }
        command(0x85);                             // Setting the start position at 1x6 position of the LCD
        data(MSB(hour)+0x30);                      // Printing the MSB part of the hours to the LCD
        data(LSB(hour)+0x30);                      // Printing the LSB part of the hours to the LCD
    }
    
    data(':');
}

void set_hour(unsigned char hour, unsigned char state) {
    unsigned char hr_data = Hexa_to_BCD(hour);    // Converting the hour from hexa format to BCD so that it can be loaded to the RTC
    if (hour>12){ 
        // No changes needed if the time is in 24-hr format
        hr_data &= ~0x40;                         // Setting down the bit for 12-hr format (Only checking, can also be neglected)
    }
    else {
        
        hr_data |= 0x40;                          // X1XX XXXX Setting up the bit to indicate the hour is in 12-hr format
        if(state==0){                             // For AM
            hr_data &= ~0x20;                     // XX0X XXXX Setting down the bit to indicate that the time is in AM
        } 
        else{                                     // For PM
            hr_data |= 0x20;                      // XX1X XXXX Setting up the bit to indicate that the time is in PM
        }
    }
    wr_time[2] = hr_data;                         // Placing the hour data on the wr_time array to write it on DS3232 RTC 
}


void set_sec(unsigned char sec){

    unsigned char sec_data = Hexa_to_BCD(sec);    // Converting the second data from Hexa to BCD to load it to DS3232 RTC
    wr_time[0] = sec_data;                        // Placing the second data on the wr_time array to write it on DS3232 RTC 
}

void set_min(unsigned char min){

    unsigned char min_data = Hexa_to_BCD(min);    // Converting the minute data from Hexa to BCD to load it to DS3232 RTC
    wr_time[1] = min_data;                        // Placing the minute data on the wr_time array to write it on DS3232 RTC 
}

void set_date(unsigned char date){

    unsigned char date_data = Hexa_to_BCD(date);  // Converting the date data from Hexa to BCD to load it to DS3232 RTC
    wr_time[4] = date_data;                       // Placing the date data on the wr_time array to write it on DS3232 RTC 
}

void set_mon(unsigned char mon){

    unsigned char mon_data = Hexa_to_BCD(mon);    // Converting the month data from Hexa to BCD to load it to DS3232 RTC
    wr_time[5] = mon_data;                        // Placing the month data on the wr_time array to write it on DS3232 RTC 
}

void set_year(unsigned char year){

    unsigned char year_data = Hexa_to_BCD(year);  // Converting the year data from Hexa to BCD to load it to DS3232 RTC
    wr_time[6] = year_data;                       // Placing the year data on the wr_time array to write it on DS3232 RTC 
}

void set_day(unsigned char day) {
    
    wr_time[3] = day;                             // Placing the day data on the wr_time array to write it on DS3232 RTC                      
 
}


unsigned char Hexa_to_BCD(unsigned char data){
    
    unsigned char ones = data%10;            // Separating the ones part of the number
    unsigned char tens = (data - ones)/10;   // Separating the tens part of the number

    unsigned char MSB = (tens<<4);           // Shifting the tens part to the MSB 
    unsigned char LSB = ones;                // Taking the ones part as it is
    
    return (MSB|LSB);                        // Combining the MSB and LSB to form a new 8-bit data
}

unsigned char MSB(unsigned char data) {

    unsigned char tens = (data>>4);         // Right-shifting the MSB nibble by 4 units
    
    return tens;
}

unsigned char LSB(unsigned char data) {

    unsigned char ones = (data&0x0F);        // Clearing the MSB nibble from the data
    
    return ones;
}


void LCD_init(void){

    TRISD = 0x00 ;               // Setting all the pins in PORTB to output 
    TRISC = 0x18 ;               // Setting all the pins in PORTC to output
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

void command(unsigned char m)
{
   PORTC = 0x00 ;                // Setting the RS pin to 0 (i.e) to command mode 
   PORTD = m ;
   PORTC = 0x80 ;                // Switching the enable pin to 1
   PORTC = 0x00 ;                // Switching the enable pin to 0
   __delay_ms(2);

}

void data(unsigned char n)
{
   PORTC = 0x40 ;                 // Setting the RS pin to 1 (i.e) to data mode
   PORTD = n ;
   PORTC = 0xC0 ;                 // Switching the enable pin to 1
   PORTC = 0x40 ;                 // Switching the enable pin to 0
   __delay_ms(2);

}

void I2C_Init(unsigned long freq) {

    SSPSTAT = 0x00;                      // 0000 0000 Initializing the SSPTAT register to 0
    SSPCON2 = 0x00;                      // 0000 0000 Initializing the SSPCON2 register to 0
    SSPCON = 0x28;                       // 0010 1000 Enabling SDA and SCL as serial port pins, setting up the processor in Master mode
    SSPADD = (_XTAL_FREQ/(4*freq))-1;    //  Holds the Slave address
    
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

void RTC_Write(unsigned char address) {

    I2C_Start();                        // Calling the I2C_Start function
    I2C_Write(0xD0);                    // Calling the I2C_Write function with the address slave 0xD0 to read
    // Note here the address is in 8-bit, so we are only passing it once
    I2C_Write(address);                 // Calling the I2C_Write function with the LSB register address on the DS3232RTC
    I2C_Write(wr_time[0]);              // Calling the I2C_Write function with the data to be written on the next address
    I2C_Write(wr_time[1]);              // Calling the I2C_Write function with the data to be written on the next address
    I2C_Write(wr_time[2]);              // Calling the I2C_Write function with the data to be written on the next address
    I2C_Write(wr_time[3]);              // Calling the I2C_Write function with the data to be written on the next address
    I2C_Write(wr_time[4]);              // Calling the I2C_Write function with the data to be written on the next address
    I2C_Write(wr_time[5]);              // Calling the I2C_Write function with the data to be written on the next address
    I2C_Write(wr_time[6]);              // Calling the I2C_Write function with the data to be written on the next address
    I2C_Stop();                         // Calling the I2C_stop function
}

void RTC_Read(unsigned char address) {

    I2C_Start();                          // Calling the I2C_Start function
    I2C_Write(0xD0);                      // Calling the I2C_Write function with the address slave 0xD0 to read
    // Note here the address is in 8-bit, so we are only passing it once
    I2C_Write(address);                   // Calling the I2C_Write function address on DS3232 RTC
    I2C_Repeatedstart();                  // Calling the I2C_Repeatedstart function
    I2C_Write(0xD1);                      // Calling the I2C_Write function with the address slave 0xD1 to write
    rd_time[0] = I2C_Read();              // Placing the read data from current address to the variable 'rd_time'
    I2C_Ack();                            // Calling the I2C_Nack function
    rd_time[1] = I2C_Read();              // Placing the read data from next address to the variable 'rd_time'
    I2C_Ack();                            // Calling the I2C_Nack function
    rd_time[2] = I2C_Read();              // Placing the read data from next address to the variable 'rd_time'
    I2C_Ack();                            // Calling the I2C_Nack function
    rd_time[3] = I2C_Read();              // Placing the read data from next address to the variable 'rd_time'
    I2C_Ack();                            // Calling the I2C_Nack function
    rd_time[4] = I2C_Read();              // Placing the read data from next address to the variable 'rd_time'
    I2C_Ack();                            // Calling the I2C_Nack function
    rd_time[5] = I2C_Read();              // Placing the read data from next address to the variable 'rd_time'
    I2C_Ack();                            // Calling the I2C_Nack function
    rd_time[6] = I2C_Read();              // Placing the read data from next address to the variable 'rd_time'
    I2C_Nack();                           // Calling the I2C_Nack function
    I2C_Stop();                           // Calling the I2C_stop function  
}