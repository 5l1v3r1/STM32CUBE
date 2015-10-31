/*

* 4_bit_lcd.h

*

* Created on: Feb 28, 2013

* Author: Kaan

*/

#define DATA_PORT GPIOC->ODR

#define CMD_PORT GPIOA->ODR

#define DATA 6

#define DATA_CLR 0xFFFFFC3F

#define LCD_E 0x100 //PA8

#define LCD_RS 0x200 //PA9

#define CMD 0

#define TXT 1

#define LINE1 0x80 // ILK SATIR LCD_GOTO(1,X) IÇIN

#define LINE2 0xC0 // 2. SATIR YÖNLENDIRME LCD_GOTO(2,X) IÇIN

void WaitLCDBusy(void);

void LCD_Init(void);

void LCD_DATA(unsigned char data,unsigned char type);

void LCD_NYB(unsigned char nyb,unsigned char type);

void LCD_STR(const char *text);

void LCD_LINE(char line);

void DelayMS(unsigned int ms);

//void initDiscovery(void);