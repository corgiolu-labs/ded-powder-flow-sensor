
#include <Key.h>
#include <Keypad.h>

#ifndef lcdkeypad_h
#define lcdkeypad_h

#define C3 6   
#define C2 7
#define C1 8
#define C0 9
#define R3 10
#define R2 11
#define R1 12
#define R0 13

#define RIGHE 4
#define COLONNE 4

 char tasti[RIGHE][COLONNE] =
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'P','0','R','D'}
};

  byte pinRighe[RIGHE] = {R0,R1,R2,R3};
  byte pinColonne[COLONNE] = {C0,C1,C2,C3};
  Keypad tastiera = Keypad(makeKeymap(tasti),pinRighe, pinColonne,RIGHE,COLONNE);
    
  void setpinTastiera(){
  pinMode(C0, INPUT_PULLUP);       
  pinMode(C1, INPUT_PULLUP); 
  pinMode(C2, INPUT_PULLUP);
  pinMode(C3, INPUT_PULLUP);
  pinMode(R0, OUTPUT);
  pinMode(R1, OUTPUT); 
  pinMode(R2, OUTPUT); 
  pinMode(R3, OUTPUT);
}
  
#endif
