

#ifndef numerickeypad_h
#define numerickeypad_h

char lettera;             //variabile che contiene il carattere catturato dalla tastiera
int n=0;                  //variabile utilizzata per la memorizzazione dei valori numerici acquisiti da tastiera


// FUNZIONE IMPOSTAZIONE NUMERI DA TASTIERA 
int tastoPremuto(){
  n=-1;
  setpinTastiera();
  lettera = tastiera.getKey();
  switch(lettera){

   case '0':
   n = 0;
   return n;
   break; 
    
   case '1':
   n = 1;
   return n;
   break;

   case '2':
   n = 2;
   return n;
   break;

   case '3':
   n = 3;
   return n;
   break;

   case '4':
   n = 4;
   return n;
   break;

   case '5':
   n = 5;
   return n;
   break;

   case '6':
   n = 6;
   return n;
   break;

   case '7':
   n = 7;
   return n; 
   break;

   case '8':
   n = 8;
   return n;
   break;

   case '9':
   n = 9;
   return n; 
   break;  
  }
 }

#endif
