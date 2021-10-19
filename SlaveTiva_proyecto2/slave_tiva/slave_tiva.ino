
#include "pitches.h" 

unsigned char antirrebote1_j1, antirrebote2_j1, antirrebote3_j1, antirrebote4_j1;
unsigned char antirrebote1_j2, antirrebote2_j2, antirrebote3_j2, antirrebote4_j2;
int melody[]={NOTE_G2, NOTE_C2, NOTE_A2, NOTE_G2, NOTE_G2, 0, NOTE_C2, NOTE_E3};
int noteDurations[]={4, 8, 8, 4, 4, 4, 4, 4};

//interrupcion para izquierda jugador 1
void ISR_izj1(){
  antirrebote1_j1=1;
}

//interrupcion para derecha jugador 1
void ISR_derj1(){
  antirrebote2_j1=1;
}
//interrupcion para abajo jugador 1
void ISR_downj1(){
  antirrebote3_j1=1;
}
//interrupcion para arriba jugador 1
void ISR_upj1(){
  antirrebote4_j1=1;
}
//interrupcion para izquierda jugador 2
void ISR_izj2(){
  antirrebote1_j2=1;
}
//interrupcion para derecha jugador 2
void ISR_derj2(){
  antirrebote2_j2=1;
}
//interrupcion para abajo jugador 2
void ISR_downj2(){
  antirrebote3_j2=1;
}
//interrupcion para arriba jugador 2
void ISR_upj2(){
  antirrebote4_j2=1;
}


void musica(void);


//
void setup() {
  pinMode(PD_0, INPUT_PULLUP);    //boton izquierda j1
  pinMode(PD_1, INPUT_PULLUP);    //boton derecha j1
  pinMode(PD_2, INPUT_PULLUP);    //boton arriba j1
  pinMode(PD_3, INPUT_PULLUP);    //boton abajo j1
  attachInterrupt(digitalPinToInterrupt(PD_0), ISR_izj1, FALLING); 
  attachInterrupt(digitalPinToInterrupt(PD_1), ISR_derj1, FALLING); 
  attachInterrupt(digitalPinToInterrupt(PD_2), ISR_downj1, FALLING); 
  attachInterrupt(digitalPinToInterrupt(PD_3), ISR_upj1, FALLING); 
  
  pinMode(PA_2, INPUT_PULLUP);    //boton izquierda j2
  pinMode(PA_3, INPUT_PULLUP);    //boton derecha j2
  pinMode(PA_4, INPUT_PULLUP);    //boton arriba j2
  pinMode(PA_5, INPUT_PULLUP);    //boton abajo j2
  attachInterrupt(digitalPinToInterrupt(PA_2), ISR_izj2, FALLING); 
  attachInterrupt(digitalPinToInterrupt(PA_3), ISR_derj2, FALLING);
  attachInterrupt(digitalPinToInterrupt(PA_4), ISR_downj2, FALLING);
  attachInterrupt(digitalPinToInterrupt(PA_5), ISR_upj2, FALLING);

  pinMode(PC_4,OUTPUT);     //salida 1
  pinMode(PC_5,OUTPUT);     //salida 2
  pinMode(PC_6,OUTPUT);     //salida 3
  pinMode(PC_7,OUTPUT);     //salida 4
  pinMode(PF_2, OUTPUT);    //salida para buzzer
  Serial.begin(9600);
}
void loop() {
  //antirrebote para izquierda j1
  if (digitalRead(PD_0)==0 && antirrebote1_j1==1){
    antirrebote1_j1=0;
    Serial.println("Boton para la derecha J1");
    digitalWrite(PC_4, HIGH);   //salida mera mera
    digitalWrite(PC_5, LOW);    //defensiva
  }
  //antirrebote para derecha j1
  if (digitalRead(PD_1)==0 && antirrebote2_j1==1){
    antirrebote2_j1=0;
    Serial.println("Boton para la izquierda J1");
    digitalWrite(PC_4, LOW);    //salida mera mera
    digitalWrite(PC_5, LOW);    //defensiva
  }
  
  //antirrebote para arriba j1
  if (digitalRead(PD_2)==0 && antirrebote3_j1==1){
    antirrebote3_j1=0;
    Serial.println("Boton para la arriba J1");
    digitalWrite(PC_4, LOW);    //defensiva
    digitalWrite(PC_5, HIGH);   //salida mera mera
  }
  //antirrebote para abajo j1
  if (digitalRead(PD_3)==0 && antirrebote4_j1==1){
    antirrebote4_j1=0;
    Serial.println("Boton para la abajo J1");
    digitalWrite(PC_4, LOW);    //defensiva
    digitalWrite(PC_5, LOW);    //salida mera mera
  }
  
  //antirrebote para izquierda j2
  if (digitalRead(PA_2)==0 && antirrebote1_j2==1){
    antirrebote1_j2=0;
    Serial.println("Boton para la derecha J2");
    digitalWrite(PC_6, HIGH);   //salida mera mera
    digitalWrite(PC_7, LOW);    //defensiva
  }
  //antirrebote para derecha j2
  if (digitalRead(PA_3)==0 && antirrebote2_j2==1){
    antirrebote1_j2=0;
    Serial.println("Boton para la izquierda J2");
    digitalWrite(PC_6, LOW);    //salida mera mera
    digitalWrite(PC_7, LOW);    //defensiva
  }
  //antirrebote para arriba j2
  if (digitalRead(PA_4)==0 && antirrebote3_j2==1){
    antirrebote3_j2=0;
    Serial.println("Boton para la arriba J2");
    digitalWrite(PC_6, LOW);    //defensiva
    digitalWrite(PC_7, HIGH);   //salida mera mera
  }
  //antirrebote para abajo j2
  if (digitalRead(PA_5)==0 && antirrebote4_j2==1){
    antirrebote4_j2=0;
    Serial.println("Boton para la abajo J2");
    digitalWrite(PC_6, LOW);    //defensiva
    digitalWrite(PC_7, LOW);    //salida mera mera
  }
  //musica();
}

void musica(void){
  for (int thisNote=0; thisNote <8; thisNote++){
    int noteDuration = 1000 / noteDurations [thisNote];
    tone(PF_2, melody [thisNote], noteDuration);
    
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(8);
  }
}




/*#include "pitches.h"  //add note library
//VARIABLES
#define LED_J1 RED_LED      //directiva para led rojo, J1
//unsigned char recibido;
unsigned char horJ1, verJ1;   //variables de jugador 1
unsigned char horJ2, verJ2;   //variables de jugador 2
unsigned char recibido[16];
int melody[]={NOTE_G2, NOTE_C2, NOTE_A2, NOTE_G2, NOTE_G2, 0, NOTE_C2, NOTE_E3};
int noteDurations[]={4, 8, 8, 4, 4, 4, 4, 4};

//SETUP
void setup() {
  Serial.begin(9600);
  Serial.print("wenas");
  Serial3.begin(9600);       //UART para menu
  pinMode(PF_2, OUTPUT);
}
//LOOP
void loop() {
  
  for (int thisNote=0; thisNote <8; thisNote++){
    if (Serial3.available()){
    unsigned char recibido = Serial3.read();
    Serial.println(recibido);
    }
    else{
      Serial.println("algo no esta jalando :,c");  
    }
    //to calculate the note duration, take one second. Divided by the note type
    int noteDuration = 1000 / noteDurations [thisNote];
    tone(PF_2, melody [thisNote], noteDuration);

    //to distinguish the notes, set a minimum time between them
    //the note's duration +30% seems to work well
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    //stop the tone playing
    noTone(8);
    delay(10);
   }
  
}
*/
