

#include <EEPROM.h>
#include "getgrams.h"
#include "lcdkeypad.h"
#include "lcd.h"
#include "numerickeypad.h"

#define PHOTODIODE_PIN A5
#define FREQUE_PIN 8
#define VIBRO_PIN 3
#define blen 100



//VARIABILI GLOBALI
int accensione=EEPROM.get(20,accensione);
int m=EEPROM.get(4,m);    //variabile dove viene salvato l'indice del materiale (indice inizio lettura memoria,variabile memorizzata)
int p=0;                  //variabile che memorizza % vibrazione 
int v=0;                  //variabile dove viene salvata la velocità del vibratore
int val=0;                //recasting variabile % in interi per la funzione vibro e flow

float fmap=0;
float mapgram=0;
int stato = 0;            //variabile urilizzata per navigare tra i menù
bool FIRST = true;        //variabile urilizzata per navigare tra i menù


float kp = EEPROM.get(40,kp);             //variablie proporzionale
float ki = EEPROM.get(80,ki);             //variabile integrativa
float f=0;                //variabile dove viene salvato il valore istantaneo del fotodiodo ricevitore
float e=0;                //errore
int buf[blen];        //array buffer per la funzione integrativa
float media=0;
float integrale=0;
float pro=0;
int out=0;

float Y=0.0;
float alpha=0.01;
float S=Y;

unsigned int Htime;
unsigned int Ltime;
float Ttime;
float freq;  
  
//DICHIARAZIONE ARRAY
String Materiale[] =  {
  "STEEL",
  "TITANIUM",
  "COPPER",
  "ALLUMINIUM",
  "INCONEL",
  "VANADIUM"
  };

void setup() {
 
 Serial.begin(9600);
 pinMode(PHOTODIODE_PIN, INPUT); 
 pinMode(VIBRO_PIN, OUTPUT); 
 setpinLcd();
 lcd.begin(16,2);
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("JOANNEUM"); 
 lcd.setCursor(8,1);
 lcd.print("RESEARCH");
 delay(3000);
 
}

void loop() {
   
  switch(stato){
    
    case 0:
      mainloop(); //main
    break;

    case 10:
      mainmenu1(); //vibro
    break;

    case 20:
      mainmenu2(); //material
    break;

    case 30:
      mainmenu3(); // flow
    break;

    case 40:
      mainmenu4(); //programm set point
    break;

    case 50:
      mainmenu5(); //PID funcion
    break;

    case 60:
      mainmenuexit(); //exit
    break;

    case 100: // sub vibro
      sub1();
    break;    

    case 200: // sub material
      sub2();
    break;  

    case 300: // sub flow
      sub3();
    break; 

    case 400: //programm sub set point
      sub4();
    break;  

    case 500: 
      sub5(); //PID sub funcion
    break;  
  }

}

//FUNZIONE CHE SETTA LO STATO
void setStato(int s){
  
  setpinLcd();
  stato = s;
  FIRST = true;
  lcd.clear();
  delay(300);
}

//FUNZIONE CHE SETTA LA SCHERMATA INIZIALE
void mainloop(){
  
  setpinLcd();
  if(FIRST){
    accensione++;
    EEPROM.put(20,accensione);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("FLOW RATE METER!");
    lcd.setCursor(0,1);
    lcd.print("P:menu  ON:");
    lcd.print(accensione);
    FIRST = false;
  }
  setpinTastiera();
  lettera = tastiera.getKey();
  switch(lettera){
    
    case 'P':
    setStato(10);
    break;

    case 'D': 
    digitalWrite(VIBRO_PIN, LOW);
  
    break; 
  }
}

//FUNZIONE CHE SETTA IL MENU 1 (VIBRAZIONE)
void mainmenu1(){
  
  setpinLcd();
   if(FIRST){
    lcd.print("VIBRATION   R:<");
    lcd.setCursor(0,1);
    lcd.print("A:Mater  B:Vibro");
    FIRST = false;
  }
  setpinTastiera();
  lettera = tastiera.getKey();
  switch(lettera){
    
    case 'A':
    setStato(20);
    break;

    case 'B':
    setStato(100);
    break;

    case 'R':
    setStato(0);
    break;

     case 'D': 
    digitalWrite(VIBRO_PIN, LOW);
      
    break; 
  }
}

//FUNZIONE CHE SETTA IL MENU 2 (MATERIALE)
void mainmenu2(){
  
  setpinLcd();
   if(FIRST){
    lcd.print("MATERIAL     R:<");
    lcd.setCursor(0,1);
    lcd.print("A:Flow   B:Mater");
    FIRST = false;
  }
  setpinTastiera();
  lettera = tastiera.getKey();
  switch(lettera){
    
    case 'A':
    setStato(30);
    break;

    case 'B':
    setStato(200);
    break;

    case 'R':
    setStato(10);
    break;

    case 'D': 
    digitalWrite(VIBRO_PIN, LOW);
      
    break; 
  }
}

//FUNZIONE CHE SETTA IL MENU 3 (FLOW RATE)
void mainmenu3(){
  
  setpinLcd();
   if(FIRST){
    lcd.print("FLOW RATE    R:<");
    lcd.setCursor(0,1);
    lcd.print("A:Prog    B:Flow");
    FIRST = false;
  }
  setpinTastiera();
  lettera = tastiera.getKey();
  switch(lettera){
    
    case 'A':
    setStato(40);
    break;

    case 'B':
    setStato(300);
    break;

    case 'R':
    setStato(20);
    break;

    case 'D': 
    digitalWrite(VIBRO_PIN, LOW);
    
    break; 
  }
}

//FUNZIONE CHE SETTA IL MENU 4 (PROGRAMM)
void mainmenu4(){
  
  setpinLcd();
   if(FIRST){
    lcd.print("PROGRAMM    R:<");
    lcd.setCursor(0,1);
    lcd.print("A:PID     B:Prog");
    FIRST = false;
  }
  setpinTastiera();
  lettera = tastiera.getKey();
  switch(lettera){
    
    case 'A':
    setStato(50);
    break;

    case 'B':
    setStato(400);
    break;

    case 'R':
    setStato(30);
    break;

    case 'D': 
    digitalWrite(VIBRO_PIN, LOW);
    
    break; 
  }
}

//FUNZIONE CHE SETTA IL MENU 5 (PID funcion)
void mainmenu5(){
  
  setpinLcd();
   if(FIRST){
    lcd.print("PID          R:<");
    lcd.setCursor(0,1);
    lcd.print("A:Exit    B:PID");
    FIRST = false;
  }
  setpinTastiera();
  lettera = tastiera.getKey();
  switch(lettera){
    
    case 'A':
    setStato(60);
    break;

    case 'B':
    setStato(500);
    break;

    case 'R':
    setStato(40);
    break;

    case 'D': 
    digitalWrite(VIBRO_PIN, LOW);
    
    break; 
  }
}

//FUNZIONE CHE SETTA IL MENU EXIT
void mainmenuexit(){
  
  setpinLcd();
   if(FIRST){
    lcd.print("Exit menu?   R:<");
    lcd.setCursor(0,1);
    lcd.print("A:Vibro   B:Exit");
    FIRST = false;
  }
  setpinTastiera();
  lettera = tastiera.getKey();
  switch(lettera){
    
    case 'A':
    setStato(10);
    break;

    case 'B':
    setStato(0);
    break;

    case 'R':
    setStato(50);
    break;

    case 'D': 
    digitalWrite(VIBRO_PIN, LOW);
    break; 
  }
}

//FUNZIONE CHE SETTA IL SUB MENU 1 (VIBRAZIONE)

void sub1(){
  
  setpinLcd();
  if(FIRST){
    //val=(((float)v/255)*100);
    lcd.setCursor(0,0);
    lcd.print("Vibro v=");
    lcd.setCursor(8,0);
    lcd.print(v);
    //lcd.print('%');
    lcd.setCursor(13,0);
    lcd.print("R:<");
    lcd.setCursor(0,1);
    lcd.print("AB:~  C:on D:off");
    FIRST = false;
  }
  
  setpinTastiera();
  lettera = tastiera.getKey();
  switch(lettera){
    
    case 'R':
    setStato(10);
    break;
    
    case 'A':
    
    do{
    setpinTastiera();
    lettera = tastiera.getKey();
    if(v<255){v=v+1;}
    else{break;}
    p = v;
    //val=(((float)v/255)*100);
    setpinLcd();
    lcd.setCursor(8,0);
    lcd.print("     ");
    lcd.setCursor(8,0);
    lcd.print(v);
    //lcd.print('%');
    analogWrite(VIBRO_PIN,v);
    delay(120);
    }while(lettera != 'A');
    
    break;
     
    case 'B':
    
    do{ 
    setpinTastiera();
    lettera = tastiera.getKey();
    if(v>0){v=v-1;}
    else{break;}
    p = v;
    //val=(((float)v/255)*100);
    setpinLcd();
    lcd.setCursor(8,0);
    lcd.print("     ");
    lcd.setCursor(8,0);
    lcd.print(v);
    //lcd.print('%');
    analogWrite(VIBRO_PIN,v);
    delay(120);
    }while(lettera != 'B');
    
    break;

    case 'C':
    setpinLcd(); 
    analogWrite(VIBRO_PIN, p);
    v=p;
    //val=(((float)v/255)*100);
    lcd.setCursor(8,0);
    lcd.print("     ");
    lcd.setCursor(8,0);
    lcd.print(v);
    //lcd.print('%');
    delay(100);   
    break;
    
    case 'D': 
    setpinLcd();
    digitalWrite(VIBRO_PIN, LOW);
    v=0;
    //val=(((float)v/255)*100);
    lcd.setCursor(8,0);
    lcd.print("     ");  
    lcd.setCursor(8,0);
    lcd.print(v);
    //lcd.print('%');
    delay(100);   
    break; 
  }
}

//FUNZIONE CHE SETTA IL SUB MENU 2 (MATERIALE)


void sub2(){
  
  setpinLcd();
  if(FIRST){
    lcd.setCursor(0,0);
    lcd.print("AB:~        R:<");
    lcd.setCursor(0,1);
    lcd.print("MAT:");
    lcd.setCursor(5,1);
    lcd.print(Materiale[m]);
    FIRST = false;
  }
  setpinTastiera();
  lettera = tastiera.getKey();
  switch(lettera){
    
    case 'R':
    setStato(20);
    break;
    
    case 'A':
    setpinLcd();
    if(m<5){m++;}
    EEPROM.put(4,m); //salva il valore corrente del materiale sulla EEPROM (indice inizio scrittura memoria,variabile da memorizzare)
    lcd.setCursor(5,1);
    lcd.print("            ");
    lcd.setCursor(5,1);
    lcd.print(Materiale[m]);
    delay(100);
    break;
    
    case 'B': 
    setpinLcd();
    if(m>0){m--;}
    EEPROM.put(4,m); //salva il valore corrente del materiale sulla EEPROM (indice inizio scrittura memoria,variabile da memorizzare)
    lcd.setCursor(5,1);
    lcd.print("            ");
    lcd.setCursor(5,1);
    lcd.print(Materiale[m]);
    delay(100);   
    break;  

    case 'D': 
    digitalWrite(VIBRO_PIN, LOW);
    
    break; 
  } 
}

//FUNZIONE CHE SETTA IL SUB MENU 3 (FLOW RATE)

void sub3(){
  
  
  setpinLcd();
  if(FIRST){
    val=(((float)v/255)*100);
    lcd.setCursor(0,0);
    lcd.print("Vibro v=");
    lcd.setCursor(8,0);
    lcd.print(val);
    lcd.print('%');
    lcd.setCursor(13,0);
    lcd.print("R:<");
    lcd.setCursor(0,1);
    lcd.print("Flow  f=");
    lcd.setCursor(8,1);
    lcd.print(f);
    lcd.setCursor(12,1);
    lcd.print("AB:~");
    FIRST = false;
  }
  
  do{
    setpinTastiera();
    lettera = tastiera.getKey();
    //f = analogRead(PHOTODIODE_PIN);
    //Y = (float)f;
    //S = (alpha*Y)+((1-alpha)*S);
    
    Htime = pulseIn(FREQUE_PIN, HIGH);
    Ltime = pulseIn(FREQUE_PIN, LOW);

    Ttime  = Htime + Ltime;
    freq = 1000/Ttime;

    Y = freq;
    S = (alpha*Y)+((1-alpha)*S);
    
    setpinLcd();
    lcd.setCursor(8,1);
    lcd.print(S);
    
    Serial.print(Y);
    Serial.print(",");
    Serial.println(S);

    //Serial.println(freq);
    
    //delay(10);
    }while(lettera != 'R' &&
           lettera != 'A' && 
           lettera != 'B' && 
           lettera != 'C' &&
           lettera != 'D' );
    
  switch(lettera){
    
    case 'R':
    setStato(30);
    break;
    
    case 'A':
    
    do{
    setpinTastiera();
    lettera = tastiera.getKey();
    if(v<255){v=v+5;}
    else{break;}
    p = v;
    val=(((float)v/255)*100);
    setpinLcd();
    lcd.setCursor(8,0);
    lcd.print("     ");
    lcd.setCursor(8,0);
    lcd.print(val);
    lcd.print('%');
    analogWrite(VIBRO_PIN,v);
    delay(120);
    }while(lettera != 'A');
    
    break;
     
    case 'B':
    
    do{ 
    setpinTastiera();
    lettera = tastiera.getKey();
    if(v>0){v=v-5;}
    else{break;}
    p = v;
    val=(((float)v/255)*100);
    setpinLcd();
    lcd.setCursor(8,0);
    lcd.print("     ");
    lcd.setCursor(8,0);
    lcd.print(val);
    lcd.print('%');
    analogWrite(VIBRO_PIN,v);
    delay(120);
    }while(lettera != 'B');
    
    break;

    case 'C':
    setpinLcd(); 
    analogWrite(VIBRO_PIN, p);
    v=p;
    val=(((float)v/255)*100);
    lcd.setCursor(8,0);
    lcd.print("     ");
    lcd.setCursor(8,0);
    lcd.print(val);
    lcd.print('%');
    delay(100);   
    break;
    
    case 'D': 
    setpinLcd();
    digitalWrite(VIBRO_PIN, LOW);
    v=0;
    val=(((float)v/255)*100);
    lcd.setCursor(8,0);
    lcd.print("     ");  
    lcd.setCursor(8,0);
    lcd.print(val);
    lcd.print('%');
    delay(100);   
    break; 
  }
}

//FUNZIONE CHE SETTA IL SUB MENU 4 (PROGRAMM)

void sub4(){
  
  setpinLcd();
  if(FIRST){
    
    lcd.setCursor(0,0);
    lcd.print("P:SET POINT");
    lcd.setCursor(13,0);
    lcd.print("R:<");
    lcd.setCursor(0,1);
    lcd.print("Gr/min=");
    lcd.setCursor(7,1);
    lcd.print(grammo);
    lcd.print('g');  
    FIRST = false;
  }
  setpinTastiera();
  lettera = tastiera.getKey();
    
  switch(lettera){
    
    case 'R':
    setStato(40);
    break;

    
// ROUTINE IMPOSTAZIONE GRAMMI DA TASTIERA 
       
    case 'P': 
    
    sequenzaNumeri();
    break;
  
 //INCREMENTA I GRAMMI
    case 'A':
    
    do{
    setpinTastiera();
    lettera = tastiera.getKey();
    if(grammo<=25){grammo=grammo+0.01;}
    else{break;}
    EEPROM.put(0, grammo); //salva il valore corrente del grammo sulla EEPROM (indice inizio scrittura memoria,variabile da memorizzare)
    setpinLcd();
    lcd.setCursor(7,1);
    lcd.print("         "); 
    lcd.setCursor(7,1);
    lcd.print(grammo);
    lcd.print('g');
    delay(120);
    }while(lettera != 'A');
    break;

//DECREMENTA I GRAMMI
    case 'B':
    
    do{
    setpinTastiera();
    lettera = tastiera.getKey();
    if(grammo>0){grammo=grammo-0.01;}
    else{break;}
    EEPROM.put(0, grammo);  //salva il valore corrente del grammo sulla EEPROM (indice inizio scrittura memoria,variabile da memorizzare)
    setpinLcd();
    lcd.setCursor(7,1);
    lcd.print("         "); 
    lcd.setCursor(7,1);
    lcd.print(grammo);
    lcd.print('g');
    delay(120);
    }while(lettera != 'B');
    break; 
    }
}

//FUNZIONE CHE SETTA IL SUB MENU 2 (PID funcion)

void sub5(){
  
  setpinLcd();
  if(FIRST){
    lcd.setCursor(0,0);
    lcd.print("KP:     KI:");
    lcd.setCursor(3,0);
    lcd.print(kp);
    lcd.setCursor(11,0);
    lcd.print(ki);
    lcd.setCursor(0,1);
    lcd.print("Set:       W:");
    lcd.setCursor(4,1);
    lcd.print(grammo);
    lcd.print('g');
    lcd.setCursor(13,1);
    lcd.print(out);
    kp=1;
    ki=1;
    FIRST = false;
  }

//CONTROLLORE   

 do{ 
    
    
    //f = analogRead(PHOTODIODE_PIN);     //lettura dal fotodiodo ricevitore
    //Y = (float)f;
    //S = (alpha*Y)+((1-alpha)*S);
    
    Htime = pulseIn(FREQUE_PIN, HIGH);
    Ltime = pulseIn(FREQUE_PIN, LOW);

    Ttime  = Htime + Ltime;
    freq = 1000/Ttime;

    Y = freq;
    S = (alpha*Y)+((1-alpha)*S);
    
    fmap = map(S, 85, 100, 0, 255);    //mappatura del segnale dato dal fotodiodo ricevitore
    fmap = constrain(fmap, 0, 255);

    mapgram = map(grammo, 0, 10, 150, 255); //rimappatura dell'uscita pwm vibro a seconda della quantità di polvere
    mapgram = constrain(mapgram, 0, 255);
    
    e =(mapgram-fmap) ;                 //calcolo errore
    out=prop(e) + intgr(e);             //calcolo output da applicare
    
    Serial.println(out);
    
    out = map(out, 0, 512, 0, 255);     //mappatura del segnale da dare al vibratore
    out = constrain(out, 0, 255);       //il segnale di output viene costretto a stare tra 0 e 255 valori
    analogWrite(VIBRO_PIN,out);         //scrittura del segnale di controllo sull'attuatore "vibro"
    //delay(10);                        //velocità di aggiornamento

    setpinLcd();
    lcd.setCursor(13,1);
    lcd.print("   ");
    lcd.setCursor(13,1);
    lcd.print(out);
    delay(100);
    setpinTastiera();
    lettera = tastiera.getKey(); 
    }while(lettera != 'R' &&
           lettera != 'P' && 
           lettera != 'A' && 
           lettera != 'B' &&
           lettera != 'C' && 
           lettera != 'D' && 
           lettera != '1' && 
           lettera != '4' && 
           lettera != '2' &&
           lettera != '5' ); 
  

  switch(lettera){
    
    case 'R':
    setStato(50);
    break;
    
    case 'P': 
    digitalWrite(VIBRO_PIN, LOW);
    break; 
  
 //INCREMENTA I GRAMMI
    case 'A':
    
    do{
    if(grammo<=25){grammo=grammo+0.01;}
    else{break;}
    EEPROM.put(0, grammo); //salva il valore corrente del grammo sulla EEPROM (indice inizio scrittura memoria,variabile da memorizzare)
    setpinLcd();
    lcd.setCursor(4,1);
    lcd.print("      ");
    lcd.setCursor(4,1);
    lcd.print(grammo);
    lcd.print('g');
    delay(120);
    setpinTastiera();
    lettera = tastiera.getKey();
    }while(lettera != 'A');
    break;

//DECREMENTA I GRAMMI
    case 'B':
    
    do{
    if(grammo>0){grammo=grammo-0.01;}
    else{break;}
    EEPROM.put(0, grammo);  //salva il valore corrente del grammo sulla EEPROM (indice inizio scrittura memoria,variabile da memorizzare)
    setpinLcd();
    lcd.setCursor(4,1);
    lcd.print("      ");
    lcd.setCursor(4,1);
    lcd.print(grammo);
    lcd.print('g');
    delay(120);
    setpinTastiera();
    lettera = tastiera.getKey();
    }while(lettera != 'B');
    break; 
    
//INCREMENTA KP
    case '1': 
    
    do{
    if(kp<9){kp=kp+0.05;}
    else{break;}
    EEPROM.put(40,kp);          //salva il valore corrente del grammo sulla EEPROM (indice inizio scrittura memoria,variabile da memorizzare)
    setpinLcd();
    lcd.setCursor(3,0);
    lcd.print("     ");
    lcd.setCursor(3,0);
    lcd.print(kp);
    delay(120);
    setpinTastiera();
    lettera = tastiera.getKey();
    }while(lettera != '1');
    break; 
    
//DECREMENTA KP  
    case '4': 
    
    do{
    
    if(kp>=1){kp=kp-0.05;}
    else{break;}
    EEPROM.put(40,kp);  //salva il valore corrente del grammo sulla EEPROM (indice inizio scrittura memoria,variabile da memorizzare)
    setpinLcd();
    lcd.setCursor(3,0);
    lcd.print("     ");
    lcd.setCursor(3,0);
    lcd.print(kp);
    delay(120);
    setpinTastiera();
    lettera = tastiera.getKey();
    }while(lettera != '4');
    break; 
    
//INCREMENTA KI
    case '2': 

    do{
    if(ki<9){ki=ki+0.05;}
    else{break;}
    EEPROM.put(80,ki);    //salva il valore corrente del grammo sulla EEPROM (indice inizio scrittura memoria,variabile da memorizzare)
    setpinLcd();
    lcd.setCursor(11,0);
    lcd.print("     ");
    lcd.setCursor(11,0);
    lcd.print(ki);
    delay(120);
    setpinTastiera();
    lettera = tastiera.getKey();
    }while(lettera != '2');
    break; 

//DECREMENTA KI  
    case '5': //decrementa ki
    
    do{
    if(ki>=1){ki=ki-0.05;}
    else{break;}
    EEPROM.put(80,ki);  //salva il valore corrente del grammo sulla EEPROM (indice inizio scrittura memoria,variabile da memorizzare)
    setpinLcd();
    lcd.setCursor(11,0);
    lcd.print("     ");
    lcd.setCursor(11,0);
    lcd.print(ki);
    delay(120);
    setpinTastiera();
    lettera = tastiera.getKey();
    }while(lettera != '5');
    break; 
    }
}


//FUNZIONE CHE CALCOLA IL VALORE PROPORZIONALE DELL'ERRORE

float prop(float e) {                 
  pro = e*kp;
  return pro;
}

//FUNZIONE CHE CALCOLA IL VALORE INTEGRATIVO DELL'ERRORE

float intgr(float e){
  buf[0] = e;
  for(int j = blen-1; j > 0; j--){
    buf[j] = buf[j-1];
  }

  for(int j = 0; j < blen; j++){
    media += buf[j];
  }
  media = media / (float)blen;
  integrale = media*ki;
  return integrale;
} 
