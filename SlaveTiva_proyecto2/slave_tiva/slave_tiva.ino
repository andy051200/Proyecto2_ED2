//***************************************************************************************************************************************
/* Librería para el uso de la pantalla ILI9341 en modo 8 bits
 * Basado en el código de martinayotte - https://www.stm32duino.com/viewtopic.php?t=637
 * Adaptación, migración y creación de nuevas funciones: Pablo Mazariegos y José Morales
 * Con ayuda de: José Guerra
 * Modificaciones y adaptación: Diego Morales
 * IE3027: Electrónica Digital 2 - 2021
 * adaptacion para uso de proyecto 2 de Andy Bonilla y Pablo Herrarte
 */
//***************************************************************************************************************************************

/*-----------------------------------------------------------------------------
 ----------------------------L I B R E R I A S---------------------------------
 -----------------------------------------------------------------------------*/
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978



/*-----------------------------------------------------------------------------
 ------------ P R O T O T I P O S   D E   F U N C I O N E S -------------------
 -----------------------------------------------------------------------------*/
void beep(int note, int duration);
void musica(void);
void serial(void);
unsigned int S=0;
unsigned int SS=0;
unsigned int C=54;
unsigned int CC=49;
unsigned int x=0;
/*-----------------------------------------------------------------------------
 ------------------------------ S E T   U P -----------------------------------
 -----------------------------------------------------------------------------*/

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);
  pinMode(PA_2, INPUT_PULLUP);
  pinMode(PA_3, INPUT_PULLUP);
  pinMode(PA_4, INPUT_PULLUP);
  pinMode(PA_5, INPUT_PULLUP);
  pinMode(PD_2, INPUT_PULLUP);
  pinMode(PD_3, INPUT_PULLUP);
  pinMode(PD_1, INPUT_PULLUP);
  pinMode(PD_0, INPUT_PULLUP);
  pinMode(PF_2,OUTPUT);
}

void loop() {
  if (Serial3.available()){
    x=Serial3.read();
    if (x==1){
      Serial3.write(C);
      Serial3.write(CC);
      Serial3.write(10);
     
    }
    
  }
  //else if(x==0){
    //musica();
 // }
  serial();
  //musica();
  
}
/*-----------------------------------------------------------------------------
 ------------------------------ F U N C I O N E S -----------------------------------
 -----------------------------------------------------------------------------*/

//-------FUNCION PARA FUNCIONAMIENTO DE COMUNICACION SERIAL 
void serial(void){
  if ((digitalRead(PA_5)==HIGH && digitalRead(PA_3)==HIGH && digitalRead(PA_2)==HIGH && digitalRead(PA_4)==LOW&&(S!=2))){
    S=2;
    C=54;
    Serial3.write(C);
    Serial3.write(CC);
    Serial3.write(10);
  }
  else if (digitalRead(PA_5)==LOW && digitalRead(PA_4)==HIGH && digitalRead(PA_3)==HIGH && digitalRead(PA_2)==HIGH && (S!=1)){
    S=1;
    C=53;
    Serial3.write(C);
    Serial3.write(CC);
    Serial3.write(10);
  }
  else if (digitalRead(PA_3)==LOW && digitalRead(PA_2)==HIGH && digitalRead(PA_4)==HIGH && digitalRead(PA_5)==HIGH && (S!=3)){
    S=3;
    C=55;
    Serial3.write(C);
    Serial3.write(CC);
    Serial3.write(10);
  }
  else if (digitalRead(PA_3)==HIGH && digitalRead(PA_4)==HIGH && digitalRead(PA_5)==HIGH && digitalRead(PA_2)==LOW && (S!=4)){
    S=4;
    C=56;
    Serial3.write(C);
    Serial3.write(CC);
    Serial3.write(10);
  }
  if (digitalRead(PD_2)==HIGH && digitalRead(PD_3)==HIGH && digitalRead(PD_1)==HIGH && digitalRead(PD_0)==LOW&&(SS!=1)){
    SS=1;
    CC=49;
    Serial3.write(C);
    Serial3.write(CC);
    Serial3.write(10);
  }
  else if (digitalRead(PD_2)==HIGH && digitalRead(PD_3)==HIGH && digitalRead(PD_0)==HIGH && digitalRead(PD_1)==LOW && (SS!=2)){
    SS=2;
    CC=50;
    Serial3.write(C);
    Serial3.write(CC);
    Serial3.write(10);
  }
  else if (digitalRead(PD_0)==HIGH && digitalRead(PD_3)==HIGH && digitalRead(PD_1)==HIGH && digitalRead(PD_2)==LOW && (SS!=3)){
    SS=3;
    CC=51;
    Serial3.write(C);
    Serial3.write(CC);
    Serial3.write(10);
  }
  else if (digitalRead(PD_2)==HIGH && digitalRead(PD_0)==HIGH && digitalRead(PD_1)==HIGH && digitalRead(PD_3)==LOW && (SS!=4)){
    SS=4;
    CC=52;
    Serial3.write(C);
    Serial3.write(CC);
    Serial3.write(10);
  }
}

//-------FUNCION PARAN NOTAS MUSICALES
void beep(int note, int duration){
  tone(PF_2, note, duration / 2);
  delay(duration / 2);
  noTone(PF_2);
  delay(duration / 2 + 20);
}
//-------FUNCION QUE REPRODUCE LAS CANCIONES
void musica(void){
  beep(NOTE_G2,200);
  beep(NOTE_C2,400);
  beep(NOTE_A2,400);
  beep(NOTE_G2,200);
  beep(NOTE_G2,200);
  beep(0,200);
  beep(NOTE_C2,200);
  beep(NOTE_E3,200);
  
  //NOTE_G2, NOTE_C2, NOTE_A2, NOTE_G2, NOTE_G2, 0, NOTE_C2, NOTE_E3
  //4, 8, 8, 4, 4, 4, 4, 4
}
