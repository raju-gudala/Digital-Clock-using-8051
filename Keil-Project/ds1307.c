#include <reg51.h>

#include "ds1307.h"
#include "i2c.h"


/* DS1307 I2C address */

#define DS1307_WRITE  0xD0
#define DS1307_READ   0xD1


/* Convert binary to BCD */
unsigned char BIN2BCD(unsigned char value)
{
    return ((value / 10) << 4) | (value % 10);
}


/* Convert BCD to binary */
unsigned char BCD2BIN(unsigned char value)
{
    return ((value >> 4) * 10) + (value & 0x0F);
}


/*
 * Initialize DS1307.
 *
 * If the CH bit in the seconds register is set,
 * the oscillator is stopped. Clear it.
 */
void RTC_Init(void)
{
    unsigned char sec;

    /* Read seconds register */

    i2c_Start();

    i2c_Write(DS1307_WRITE);
    i2c_Write(0x00);

    i2c_Start();

    i2c_Write(DS1307_READ);

    sec = i2c_Read();

    i2c_NoAck();

    i2c_Stop();


    /* Clear CH bit if oscillator is stopped */

    if(sec & 0x80)
    {
        sec &= 0x7F;

        i2c_Start();

        i2c_Write(DS1307_WRITE);
        i2c_Write(0x00);
        i2c_Write(sec);

        i2c_Stop();
    }
}


/*
 * Set RTC time
 *
 * hour   : 0-23
 * minute : 0-59
 * second : 0-59
 */
void RTC_SetTime(
    unsigned char hour,
    unsigned char minute,
    unsigned char second
)
{
    i2c_Start();

    i2c_Write(DS1307_WRITE);

    /* Start at seconds register */
    i2c_Write(0x00);

    i2c_Write(BIN2BCD(second));
    i2c_Write(BIN2BCD(minute));
    i2c_Write(BIN2BCD(hour));

    i2c_Stop();
}


/*
 * Set date
 *
 * date  : 1-31
 * month : 1-12
 * year  : 0-99
 */
void RTC_SetDate(
    unsigned char date,
    unsigned char month,
    unsigned char year
)
{
    i2c_Start();

    i2c_Write(DS1307_WRITE);

    /* Date register */
    i2c_Write(0x04);

    i2c_Write(BIN2BCD(date));
    i2c_Write(BIN2BCD(month));

    /*
     * Register 0x06 = Year
     *
     * Register 0x05 = Month
     * Register 0x04 = Date
     */
    i2c_Write(BIN2BCD(year));

    i2c_Stop();
}


/*
 * Read time from DS1307
 */
void RTC_GetTime(
    unsigned char *hour,
    unsigned char *minute,
    unsigned char *second
)
{
    unsigned char sec;
    unsigned char min;
    unsigned char hr;


    /*
     * Set register pointer to 0x00
     */

    i2c_Start();

    i2c_Write(DS1307_WRITE);
    i2c_Write(0x00);


    /*
     * Read from DS1307
     */

    i2c_Start();

    i2c_Write(DS1307_READ);


    sec = i2c_Read();
    i2c_Ack();

    min = i2c_Read();
    i2c_Ack();

    hr = i2c_Read();
    i2c_NoAck();

    i2c_Stop();


    /*
     * Convert BCD to binary
     */

    *second = BCD2BIN(sec & 0x7F);
    *minute = BCD2BIN(min & 0x7F);

    /*
     * 24-hour mode
     */
    *hour = BCD2BIN(hr & 0x3F);
}


/*
 * Read date from DS1307
 */
void RTC_GetDate(
    unsigned char *date,
    unsigned char *month,
    unsigned char *year
)
{
    unsigned char d;
    unsigned char m;
    unsigned char dow;
    unsigned char y;


    /*
     * Set register pointer to date register
     */

    i2c_Start();

    i2c_Write(DS1307_WRITE);
    i2c_Write(0x04);


    /*
     * Read date registers
     */

    i2c_Start();

    i2c_Write(DS1307_READ);


    d = i2c_Read();
    i2c_Ack();

    m = i2c_Read();
    i2c_Ack();

    /*
     * Day of week
     */
    dow = i2c_Read();
    i2c_Ack();

    y = i2c_Read();
    i2c_NoAck();

    i2c_Stop();


    /*
     * Convert BCD to binary
     */

    *date = BCD2BIN(d & 0x3F);
    *month = BCD2BIN(m & 0x1F);
    *year = BCD2BIN(y);
}