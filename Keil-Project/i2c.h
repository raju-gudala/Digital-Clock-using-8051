#ifndef I2C_H
#define I2C_H

void i2c_Clock(void);
void i2c_Start(void);
void i2c_Stop(void);
void i2c_Write(unsigned char dat);
unsigned char i2c_Read(void);
void i2c_Ack(void);
void i2c_NoAck(void);

#endif