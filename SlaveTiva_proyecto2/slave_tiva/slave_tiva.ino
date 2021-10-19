/*------------------------------------------------------------------------------  
Archivo: slave_tiva
Microcontrolador: TM4C123
Autor: Andy Bonilla
Compilador: Energia 1.8.11E23
Programa: proyecto 2
Hardware: Launchpad Tiva C
    
Creado: 19 de octubre de 2021    
Descripcion: tiva para el control del videojuego
------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 ----------------------------L I B R E R I A S---------------------------------
 -----------------------------------------------------------------------------*/
#include "pitches.h" 

/*-----------------------------------------------------------------------------
 -----------------V A R I A B L E S   A   I M P L E M T E N T A R--------------
 -----------------------------------------------------------------------------*/
unsigned char antirrebote1_j1, antirrebote2_j1, antirrebote3_j1, antirrebote4_j1;
unsigned char antirrebote1_j2, antirrebote2_j2, antirrebote3_j2, antirrebote4_j2;
int melody[]={NOTE_G2, NOTE_C2, NOTE_A2, NOTE_G2, NOTE_G2, 0, NOTE_C2, NOTE_E3};
int noteDurations[]={4, 8, 8, 4, 4, 4, 4, 4};

/*-----------------------------------------------------------------------------
 ------------------------ I N T E R R U P C I O N E S ------------------------
 -----------------------------------------------------------------------------*/
//-------interrupcion para izquierda jugador 1
void ISR_izj1(){
  antirrebote1_j1=1;
}

//-------interrupcion para derecha jugador 1
void ISR_derj1(){
  antirrebote2_j1=1;
}
//-------interrupcion para abajo jugador 1
void ISR_downj1(){
  antirrebote3_j1=1;
}
//-------interrupcion para arriba jugador 1
void ISR_upj1(){
  antirrebote4_j1=1;
}
//-------interrupcion para izquierda jugador 2
void ISR_izj2(){
  antirrebote1_j2=1;
}
//-------interrupcion para derecha jugador 2
void ISR_derj2(){
  antirrebote2_j2=1;
}
//-------interrupcion para abajo jugador 2
void ISR_downj2(){
  antirrebote3_j2=1;
}
//-------interrupcion para arriba jugador 2
void ISR_upj2(){
  antirrebote4_j2=1;
}

/*-----------------------------------------------------------------------------
 ------------ P R O T O T I P O S   D E   F U N C I O N E S -------------------
 -----------------------------------------------------------------------------*/
void musica(void);

/*-----------------------------------------------------------------------------
 ------------------------------ S E T   U P -----------------------------------
 -----------------------------------------------------------------------------*/
void setup() {
  //-------ENTRADAS Y SALIDA
  //jugador 1
  pinMode(PD_0, INPUT_PULLUP);    //boton izquierda j1
  pinMode(PD_1, INPUT_PULLUP);    //boton derecha j1
  pinMode(PD_2, INPUT_PULLUP);    //boton arriba j1
  pinMode(PD_3, INPUT_PULLUP);    //boton abajo j1
  //jugador 2
  pinMode(PA_2, INPUT_PULLUP);    //boton izquierda j2
  pinMode(PA_3, INPUT_PULLUP);    //boton derecha j2
  pinMode(PA_4, INPUT_PULLUP);    //boton arriba j2
  pinMode(PA_5, INPUT_PULLUP);    //boton abajo j2
  //salidas
  pinMode(PC_4,OUTPUT);     //salida 1
  pinMode(PC_5,OUTPUT);     //salida 2
  pinMode(PC_6,OUTPUT);     //salida 3
  pinMode(PC_7,OUTPUT);     //salida 4
  pinMode(PF_2, OUTPUT);    //salida para buzzer
  
  //-------CONFIGURACION INTERRUPCIONES
  //jugador 1
  attachInterrupt(digitalPinToInterrupt(PD_0), ISR_izj1, FALLING); 
  attachInterrupt(digitalPinToInterrupt(PD_1), ISR_derj1, FALLING); 
  attachInterrupt(digitalPinToInterrupt(PD_2), ISR_downj1, FALLING); 
  attachInterrupt(digitalPinToInterrupt(PD_3), ISR_upj1, FALLING); 
  //jugador 2
  attachInterrupt(digitalPinToInterrupt(PA_2), ISR_izj2, FALLING); 
  attachInterrupt(digitalPinToInterrupt(PA_3), ISR_derj2, FALLING);
  attachInterrupt(digitalPinToInterrupt(PA_4), ISR_downj2, FALLING);
  attachInterrupt(digitalPinToInterrupt(PA_5), ISR_upj2, FALLING);

  //-------CONFIGURACION DE COMUNICACION UART
  Serial.begin(9600);
}

/*-----------------------------------------------------------------------------
 -------------------------- M A I N   L O O P ---------------------------------
 -----------------------------------------------------------------------------*/
void loop() {
  //-------antirrebote para izquierda j1
  if (digitalRead(PD_0)==0 && antirrebote1_j1==1){
    antirrebote1_j1=0;
    Serial.println("Boton para la derecha J1");
    digitalWrite(PC_4, HIGH);                         //salida mera mera
    digitalWrite(PC_5, LOW);                          //defensiva
  }
  //-------antirrebote para derecha j1
  if (digitalRead(PD_1)==0 && antirrebote2_j1==1){
    antirrebote2_j1=0;
    Serial.println("Boton para la izquierda J1");
    digitalWrite(PC_4, LOW);                         //salida mera mera
    digitalWrite(PC_5, LOW);                         //defensiva
  }
  
  //-------antirrebote para arriba j1
  if (digitalRead(PD_2)==0 && antirrebote3_j1==1){
    antirrebote3_j1=0;
    Serial.println("Boton para la arriba J1");
    digitalWrite(PC_4, LOW);                        //defensiva
    digitalWrite(PC_5, HIGH);                       //salida mera mera
  }
  //-------antirrebote para abajo j1
  if (digitalRead(PD_3)==0 && antirrebote4_j1==1){
    antirrebote4_j1=0;
    Serial.println("Boton para la abajo J1");
    digitalWrite(PC_4, LOW);                        //defensiva
    digitalWrite(PC_5, LOW);                        //salida mera mera
  }
  
  //-------antirrebote para izquierda j2
  if (digitalRead(PA_2)==0 && antirrebote1_j2==1){
    antirrebote1_j2=0;
    Serial.println("Boton para la derecha J2");
    digitalWrite(PC_6, HIGH);                     //salida mera mera
    digitalWrite(PC_7, LOW);                      //defensiva
  }
  //-------antirrebote para derecha j2
  if (digitalRead(PA_3)==0 && antirrebote2_j2==1){
    antirrebote1_j2=0;
    Serial.println("Boton para la izquierda J2");
    digitalWrite(PC_6, LOW);                      //salida mera mera
    digitalWrite(PC_7, LOW);                      //defensiva
  }
  //-------antirrebote para arriba j2
  if (digitalRead(PA_4)==0 && antirrebote3_j2==1){
    antirrebote3_j2=0;
    Serial.println("Boton para la arriba J2");
    digitalWrite(PC_6, LOW);                      //defensiva
    digitalWrite(PC_7, HIGH);                     //salida mera mera
  }
  //-------antirrebote para abajo j2
  if (digitalRead(PA_5)==0 && antirrebote4_j2==1){
    antirrebote4_j2=0;
    Serial.println("Boton para la abajo J2");
    digitalWrite(PC_6, LOW);                      //defensiva
    digitalWrite(PC_7, LOW);                      //salida mera mera
  }
  //musica();
}

/*-----------------------------------------------------------------------------
 ------------------------- F U N C I O N E S ----------------------------------
 -----------------------------------------------------------------------------*/
void musica(void){
  for (int thisNote=0; thisNote <8; thisNote++){
    int noteDuration = 1000 / noteDurations [thisNote];
    tone(PF_2, melody [thisNote], noteDuration);
    
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(8);
  }
}
