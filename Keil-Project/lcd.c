#include <reg51.h>
#include "lcd.h"

sbit LCD_RS = P3^4;
sbit LCD_EN = P3^5;


/* Simple delay */
void LCD_DelayMs(unsigned int ms)
{
    unsigned int i, j;

    for(i = 0; i < ms; i++)
    {
        for(j = 0; j < 120; j++);
    }
}


/* Send only the upper nibble of P1.
   P1.0-P1.3 are preserved because they are used by I2C. */
void LCD_WriteNibble(unsigned char nibble)
{
    P1 = (P1 & 0x0F) | (nibble & 0xF0);

    LCD_EN = 1;
    LCD_DelayMs(1);
    LCD_EN = 0;
    LCD_DelayMs(1);
}


/* Send 8-bit command in 4-bit mode */
void LCD_Command(unsigned char cmd)
{
    LCD_RS = 0;

    LCD_WriteNibble(cmd);
    LCD_WriteNibble(cmd << 4);

    LCD_DelayMs(2);
}


/* Send data character */
void LCD_Data(unsigned char dat)
{
    LCD_RS = 1;

    LCD_WriteNibble(dat);
    LCD_WriteNibble(dat << 4);

    LCD_DelayMs(1);
}


/* LCD initialization */
void LCD_Init(void)
{
    LCD_RS = 0;
    LCD_EN = 0;

    /* Allow LCD power to stabilize */
    LCD_DelayMs(20);

    /* Force LCD into 8-bit initialization state */
    LCD_WriteNibble(0x30);
    LCD_DelayMs(5);

    LCD_WriteNibble(0x30);
    LCD_DelayMs(2);

    LCD_WriteNibble(0x30);
    LCD_DelayMs(2);

    /* Switch to 4-bit mode */
    LCD_WriteNibble(0x20);
    LCD_DelayMs(2);

    /* 4-bit, 2 lines, 5x8 font */
    LCD_Command(0x28);

    /* Display ON, cursor OFF, blink OFF */
    LCD_Command(0x0C);

    /* Entry mode */
    LCD_Command(0x06);

    /* Clear display */
    LCD_Command(0x01);

    LCD_DelayMs(5);
}


/* Clear LCD */
void LCD_Clear(void)
{
    LCD_Command(0x01);
    LCD_DelayMs(3);
}


/* Set cursor */
void LCD_SetCursor(unsigned char row, unsigned char col)
{
    if(row == 0)
        LCD_Command(0x80 + col);
    else
        LCD_Command(0xC0 + col);
}


/* Display string */
void LCD_String(char *str)
{
    while(*str)
    {
        LCD_Data(*str);
        str++;
    }
}