#include <reg51.h>

#include "lcd.h"
#include "ds1307.h"


unsigned char hour;
unsigned char minute;
unsigned char second;

unsigned char date;
unsigned char month;
unsigned char year;


/* Print two digits */
void LCD_Print2(unsigned char value)
{
    LCD_Data((value / 10) + '0');
    LCD_Data((value % 10) + '0');
}


void main(void)
{
    /* Initialize LCD */
    LCD_Init();

    /* Initialize RTC */
    RTC_Init();

    /* Header */
    LCD_SetCursor(0, 0);
    LCD_String("TIME ");

    LCD_SetCursor(1, 0);
    LCD_String("DATE ");

    while(1)
    {
        /* Read time */
        RTC_GetTime(&hour, &minute, &second);

        /* Display time */
        LCD_SetCursor(0, 5);

        LCD_Print2(hour);
        LCD_Data(':');

        LCD_Print2(minute);
        LCD_Data(':');

        LCD_Print2(second);


        /* Read date */
        RTC_GetDate(&date, &month, &year);

        /* Display date */
        LCD_SetCursor(1, 5);

        LCD_Print2(date);
        LCD_Data('/');

        LCD_Print2(month);
        LCD_Data('/');

        LCD_Print2(year);

        /* Small delay */
        {
            unsigned int i;
            for(i = 0; i < 200; i++);
        }
    }
}