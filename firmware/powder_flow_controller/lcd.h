
#include <LiquidCrystal.h>

#ifndef lcd_h
#define lcd_h

#define RS 4
#define E  5
#define C3 6
#define C2 7
#define C1 8
#define C0 9

LiquidCrystal lcd(RS, E, C3, C2, C1, C0);

void setpinLcd(){
  pinMode(C0, OUTPUT); // LINEA DATI LCD      
  pinMode(C1, OUTPUT); // LINEA DATI LCD  
  pinMode(C2, OUTPUT); // LINEA DATI LCD 
  pinMode(C3, OUTPUT); // LINEA DATI LCD 
} 

#endif
