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

// EEPROM support functions

void EEPROM_Write(unsigned int, unsigned char);    // Function containing single byte write procedure for I2C
void EEPROM_Read(unsigned int);                    // Function containing single byte read procedure for I2C


