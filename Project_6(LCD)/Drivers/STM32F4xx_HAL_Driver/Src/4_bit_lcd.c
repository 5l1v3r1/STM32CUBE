#include "stm32f4xx.h"

#include "4_bit_lcd.h"

void delay(int ticks) //us seviyesinde beklme suresi

{

while(ticks--);

}

void lcd_init() //lcd ayarlai set ediliyor

{

CMD_PORT &= ~(LCD_E); //LCD_E = 0; //Enable 0 la

CMD_PORT &= ~(LCD_RS); //LCD_RS = 0; //yazmaya hazirlan

DelayMS(30); //BASLAMADAN ÖNCE STABILIZASYON AYARI

LCD_NYB(0x30,0); //BASLAMA SATIRI

DelayMS(5);

LCD_NYB(0x30,0); //BASLAMA SATIRI

DelayMS(1);

LCD_DATA(0x02,0); //4 BIT GÖNDERILECEK HAZIRLAN, 1 lin


LCD_DATA(0x28,0); //4 BIT GÖNDERILECEK HAZIRLAN, 2 line and 5*10 font

LCD_DATA(0x0c,0); //4 BIT GÖNDERILECEK HAZIRLAN, 2 line and 5*7 font

LCD_DATA(0x01,0); //EKRANI TEMIZLE

LCD_DATA(0x06,0); //move cursor right after write

}

//——————————————————————————–//

void LCD_DATA(unsigned char data,unsigned char type){

WaitLCDBusy(); //MESGUL OLABILIR BIRAZ GECIKME KOYDU

K

if(type == CMD){

CMD_PORT &= ~(LCD_RS); //KOMUT MOD

} else {

CMD_PORT |= LCD_RS; //KARAKTER/DATA MOD

}

LCD_NYB(data>>4,type); //WRITE THE UPPER NIBBLE

LCD_NYB(data,type); //WRITE THE LOWER NIBBLE

}

//————————————————————————

——–//

void WaitLCDBusy(void){

DelayMS(2); //DELAY 1 MILISANIYE

}

//————————————————————————-

——-//

void LCD_NYB(unsigned char nyb,unsigned char type){

DATA_PORT &= DATA_CLR; //LCD_PORT &= 0xF0; //CLEAR LOWER PORT NIBBLE

DATA_PORT |= (nyb<<DATA); //LCD_PORT |= (nyb & 0x0F); //SAT

IR BILGISI GÖDNER

if(type == CMD){

CMD_PORT &= ~(LCD_RS); //KOMUT MOD

} else {

CMD_PORT |= LCD_RS; //KARAKTER/DATA MOD

}

CMD_PORT |= LCD_E; //LCD_E = 1; //AKTIF LCD DATA LINE

delay(100);

CMD_PORT &= ~(LCD_E); //LCD_E = 0; //DEAKTIF LCD DATA LINE

}

//————————————————————————-

——-//

void LCD_STR(const char *text){ // lcd 1. satir yazmak icin

while(*text){

LCD_DATA(*text++,1);

}

}

void LCD_STR2(unsigned char *text){ //lcd 2. satir için yaz

while(*text)

{

LCD_DATA(*text++,1);

}

}

//————————————————————————

——–//

void LCD_LINE(char line){ //lcd goto yerine line olarak belirledik

switch(line){

case 0:

case 1:

LCD_DATA(LINE1,0);

break;

case 2:

LCD_DATA(LINE2,0);

break;

}

}

//——————————————————————————–//

//————————————————————————

——–//

void DelayMS(unsigned int ms){

unsigned int x;

for(x=0;x<ms;x++)

delay(600);

}