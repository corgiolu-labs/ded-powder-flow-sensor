

#ifndef getgrams_h
#include "lcdkeypad.h"
#include "lcd.h"
#include "numerickeypad.h"
#define getgrams_h

int b=0;                  //variabile dove viene salvato il numero totale digitato
bool CONTEGGIO = false;   //controlla la finestra temporale che viene aperta per introdurre i numeri da tastiera
bool CONTINUA = true;     //variabile di appoggio per mettere in loop continuo il ciclo while
long t=0;                 //variabile usata per salvare i tempi
float grammo=0;           //variabile grammo visualizzato sul lcd


// FUNZIONE IMPOSTAZIONE SEQUENZA DI NUMERI DA TASTIERA 

int sequenzaNumeri(){
    n=0;
    while(CONTINUA){      
 if((n >= 0) && !CONTEGGIO) {
    CONTEGGIO = true;
    t = millis();
    b=n;
    }
      
    tastoPremuto();   
 if (CONTEGGIO && (millis()-t >= 1500)) {
    CONTEGGIO = false;
    return b;        
    }

 if (n >= 0 && CONTEGGIO){
    t = millis();  
     
    b = b*10 + n; //calcola le cifre successive

    if(b<=25.00) {grammo=b;}; //limite di scrittura grammi
    
    setpinLcd();
    lcd.setCursor(7,1);
    lcd.print("         "); 
    lcd.setCursor(7,1);
    lcd.print(grammo);
    lcd.print('g');
    }
    }
}
#endif
