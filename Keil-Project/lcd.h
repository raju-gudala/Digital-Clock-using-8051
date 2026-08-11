#ifndef LCD_H
#define LCD_H

void LCD_Init(void);
void LCD_Command(unsigned char cmd);
void LCD_Data(unsigned char dat);
void LCD_String(char *str);
void LCD_SetCursor(unsigned char row, unsigned char col);
void LCD_Clear(void);

#endif