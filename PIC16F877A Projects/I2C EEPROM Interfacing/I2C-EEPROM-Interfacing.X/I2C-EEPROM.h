// I2C support functions

void I2C_Init(unsigned long);
void I2C_Start(void);
void I2C_Repeatedstart(void);
void I2C_Stop(void);
void I2C_Wait(void);
void I2C_Ack(void);
void I2C_Nack(void);
unsigned char I2C_Write(unsigned char);
unsigned char I2C_Read(void);

// EEPROM support functions

void EEPROM_Write(unsigned int, unsigned char);
void EEPROM_Read(unsigned int);


