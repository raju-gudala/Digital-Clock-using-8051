#include <reg51.h>
#include "delay.h"
#include "i2c.h"

/*
 * DS1307 I2C connections
 *
 * P1.0 -> SCL
 * P1.1 -> SDA
 */

sbit SCL = P1^0;
sbit SDA = P1^1;


/* Generate one I2C clock pulse */
void i2c_Clock(void)
{
    SCL = 0;
    delay_us(50);

    SCL = 1;
    delay_us(50);

    SCL = 0;
    delay_us(50);
}


/* I2C START condition */
void i2c_Start(void)
{
    SDA = 1;
    SCL = 1;
    delay_us(50);

    SDA = 0;
    delay_us(50);

    SCL = 0;
    delay_us(50);
}


/* I2C STOP condition */
void i2c_Stop(void)
{
    SDA = 0;
    SCL = 0;
    delay_us(50);

    SCL = 1;
    delay_us(50);

    SDA = 1;
    delay_us(50);
}


/* Write one byte */
void i2c_Write(unsigned char dat)
{
    unsigned char i;

    for(i = 0; i < 8; i++)
    {
        if(dat & 0x80)
            SDA = 1;
        else
            SDA = 0;

        SCL = 1;
        delay_us(50);

        SCL = 0;
        delay_us(50);

        dat <<= 1;
    }

    /*
     * Release SDA so slave can generate ACK.
     */
    SDA = 1;

    SCL = 1;
    delay_us(50);

    SCL = 0;
    delay_us(50);
}


/* Read one byte */
unsigned char i2c_Read(void)
{
    unsigned char i;
    unsigned char dat = 0;

    /*
     * Release SDA so slave can drive it.
     */
    SDA = 1;

    for(i = 0; i < 8; i++)
    {
        dat <<= 1;

        SCL = 1;
        delay_us(50);

        if(SDA)
            dat |= 1;

        SCL = 0;
        delay_us(50);
    }

    return dat;
}


/* Send ACK */
void i2c_Ack(void)
{
    SDA = 0;

    SCL = 1;
    delay_us(50);

    SCL = 0;
    delay_us(50);

    SDA = 1;
}


/* Send NACK */
void i2c_NoAck(void)
{
    SDA = 1;

    SCL = 1;
    delay_us(50);

    SCL = 0;
    delay_us(50);
}