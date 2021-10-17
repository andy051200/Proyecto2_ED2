/*------------------------------------------------------------------------------
Archivo: mainsproject.s
Microcontrolador: PIC16F887
Autor: Andy Bonilla
Compilador: pic-as (v2.30), MPLABX v5.40
    
Programa: pic para motores de proyecto 1 de PCB
Hardware: PIC16F887
    
Creado: 10 de septiembre de 2021    
Descripcion: 
------------------------------------------------------------------------------*/

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT   //configuracion de oscilador interno
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

/*-----------------------------------------------------------------------------
 ----------------------------LIBRERIAS-----------------------------------------
 -----------------------------------------------------------------------------*/
#include <stdint.h>             //se incluye libreria
#include <pic16f887.h>          //se incluye libreria del pic
#include "Osc_config.h"
#include "UART_CONFIG.h"
#include <xc.h>
/*-----------------------------------------------------------------------------
 ----------------------- VARIABLES A IMPLEMTENTAR------------------------------
 -----------------------------------------------------------------------------*/
//-------DIRECTIVAS DEL COMPILADOR
#define _XTAL_FREQ 4000000
//-------VARIABLES DE PROGRAMA
unsigned char antirrebote0,antirrebote1;  //para botones
unsigned char antirrebote2,antirrebote3;  //para botones
unsigned char antirrebote4,antirrebote5;  //para botones
unsigned char antirrebote6,antirrebote7;  //para botones
unsigned char horJ1, verJ1;   //variables de jugador 1
unsigned char horJ2, verJ2;   //variables de jugador 2
unsigned char cuenta_uart;
int wenas;
/*-----------------------------------------------------------------------------
 ------------------------ PROTOTIPOS DE FUNCIONES ------------------------------
 -----------------------------------------------------------------------------*/
void setup(void);
void botonazos(void);
void mandar_datos(void);
/*-----------------------------------------------------------------------------
 --------------------------- INTERRUPCIONES -----------------------------------
 -----------------------------------------------------------------------------*/
void __interrupt() isr(void) //funcion de interrupciones
{   
    //-------INTERRUPCION POR BOTONAZO
    if (INTCONbits.RBIF)
    {
        switch(PORTB)
        {
            case(0b11111110):
                antirrebote0=1;
                break;
            case(0b11111101):
                antirrebote1=1;
                break;
            case(0b11111011):
                antirrebote2=1;
                break;
            case(0b11110111):
                antirrebote3=1;
                break;
            case(0b11101111):
                antirrebote4=1;
                break;
            case(0b11011111):
                antirrebote5=1;
                break;
            case(0b10111111):
                antirrebote6=1;
                break;
            case(0b01111111):
                antirrebote7=1;
                break;
            /*default:
                antirrebote0=0;
                antirrebote1=0;
                antirrebote2=0;
                antirrebote3=0;
                antirrebote4=0;
                antirrebote5=0;
                antirrebote6=0;
                antirrebote7=0;
                break;*/
        }
        INTCONbits.RBIF=0;
    }
    //-------INTERRUPCION POR UART
    if (PIR1bits.TXIF)
    {
        cuenta_uart++;      //se suma variable guia
        mandar_datos();     //invoco funcion para mandar uart
        PIR1bits.TXIF=0;    //apago interrupcion
    }
}
/*-----------------------------------------------------------------------------
 ----------------------------- MAIN LOOP --------------------------------------
 -----------------------------------------------------------------------------*/
void main(void) {
    setup();
    while(1)
    {
        botonazos();    //se llama funcion de botonazos
        //mandar_datos();     //invoco funcion para mandar uart
    }
    return;
}
/*-----------------------------------------------------------------------------
 ---------------------------------- SET UP -----------------------------------
 -----------------------------------------------------------------------------*/
void setup(void)
{
    //-------CONFIGURACION ENTRADAS ANALOGICAS
    
    ANSEL=0;
    ANSELH=0;
    //-------CONFIGURACION DE PUERTOS
    TRISA=0;        //salida para los pines de los motores
    TRISBbits.TRISB0=1;        //entrada para los botones de modos
    TRISBbits.TRISB1=1;        //entrada para los botones de modos
    TRISBbits.TRISB2=1;        //entrada para los botones de modos
    TRISBbits.TRISB3=1;        //entrada para los botones de modos
    TRISBbits.TRISB4=1;        //entrada para los botones de modos
    TRISBbits.TRISB5=1;        //entrada para los botones de modos
    TRISBbits.TRISB6=1;        //entrada para los botones de modos
    TRISBbits.TRISB7=1;        //entrada para los botones de modos
    TRISD=0;        //entrada para los botones de modos
    //-------LIMPIEZA DE PUERTOS
    PORTA=0;                    //se limpia puerto A
    PORTB=0;                    //se limpia puerto B
    PORTD=0;                    //se limpia puerto B
    //-------CONFIGURACION DE RELOJ
    osc_config(4);                      //reloj a 4MHz
    //-------CONFIGURACION DE UART
    uart_config();
    //-------CONFIGURACION DE WPUB
    OPTION_REGbits.nRBPU=0;             //se activan WPUB
    WPUBbits.WPUB0=1;                   //RB0, boton encendido
    WPUBbits.WPUB1=1;                   //RB1, boton apagado
    WPUBbits.WPUB2=1;                   //RB2, boton retorno
    WPUBbits.WPUB3=1;                   //RB3, boton retorno
    WPUBbits.WPUB4=1;                   //RB4, boton retorno
    WPUBbits.WPUB5=1;                   //RB5, boton retorno
    WPUBbits.WPUB6=1;                   //RB6, boton retorno
    WPUBbits.WPUB7=1;                   //RB7, boton retorno
    //-------CONFIGURACION DE INTERRUPCIONES
    INTCONbits.GIE=1;                   //se habilita interrupciones globales
    INTCONbits.PEIE = 1;                //habilitan interrupciones por perifericos
    INTCONbits.RBIE=1;                  //se  habilita IntOnChange B
    INTCONbits.RBIF=0;                  //se  apaga bandera IntOnChange B
    IOCBbits.IOCB0=1;                   //habilita IOCB RB0
    IOCBbits.IOCB1=1;                   //habilita IOCB RB1
    IOCBbits.IOCB2=1;                   //habilita IOCB RB2
    IOCBbits.IOCB3=1;                   //habilita IOCB RB3
    IOCBbits.IOCB4=1;                   //habilita IOCB RB4
    IOCBbits.IOCB5=1;                   //habilita IOCB RB5
    IOCBbits.IOCB6=1;                   //habilita IOCB RB6
    IOCBbits.IOCB7=1;                   //habilita IOCB RB7
    PIE1bits.TXIE=1;            //enable interrupcion de tx uart
    PIR1bits.TXIF=0;            //apago bandera interrupcion tx uart
}
/*-----------------------------------------------------------------------------
 --------------------------------- FUNCIONES ----------------------------------
 -----------------------------------------------------------------------------*/
//-------FUNCION PARA LOS BOTONAZOS DE LOS CONTROLES
void botonazos(void)
{
    //JUGADOR 1
    //-------antirrebote 0, izquierda j1
    if(antirrebote0==1 && PORTBbits.RB0==0) 
    {
        antirrebote0=0;
        horJ1=0;
    }
    //-------antirrebote 1, derecha j1
    if(antirrebote1==1 && PORTBbits.RB1==0)
    {
        antirrebote1=0;
        horJ1=1;
    }
    
    //-------antirrebote 2, arriba j1
    if(antirrebote2==1 && PORTBbits.RB2==0)
    {
        antirrebote2=0;
        verJ1=0;
    }
    //-------antirrebote 3, abajo j1
    if(antirrebote3==1 && PORTBbits.RB3==0)
    {
        antirrebote3=0;
        verJ1=1;
    }
    //JUGADOR 2
    //-------antirrebote 4, izquierda j2
    if(antirrebote4==1 && PORTBbits.RB4==0)
    {
        antirrebote4=0;
        horJ2=0;
    }
    //-------antirrebote 5, derecha j2
    if(antirrebote5==1 && PORTBbits.RB5==0)
    {
        antirrebote5=0;
        horJ2=1;
    }
    //-------antirrebote 6, arriba j2
    if(antirrebote6==1 && PORTBbits.RB6==0)
    {
        antirrebote6=0;
        verJ2=0;
    }
    //-------antirrebote 7, abajo j2
    if(antirrebote7==1 && PORTBbits.RB7==0)
    {
        antirrebote7=0;
        verJ2=1;
    }
}
//-------FUNCION PARA MANDAR LOS DATOS UART A LA TIVA
void mandar_datos(void)
{
    switch(cuenta_uart)
    {
        case(0):
            //TXREG=0x02;
            break;
        case(1):
            TXREG=(verJ1+48);
            //TXREG='w';
            break;
        case(2):
            TXREG=44;
            //TXREG='e';
            break;
        case(3):
            TXREG=horJ1+48;
            //TXREG='n';
            break;
        case(4):
            TXREG=44;
            //TXREG='a';
            break;
        case(5):
            TXREG=horJ2+48;
            //TXREG='s';
            break;
        case(6):
            TXREG=44;
            //TXREG=0x03;
            break;
        case(7):
            TXREG=verJ2+48;
            break;
        
        case(8):
            TXREG=10;               //cambio de linea
            break;
        case(9):
            TXREG=13;               //retorno de carro
            break;
        case(15):
            cuenta_uart=0;          //un tipo de delay para reiniciar cuenta
            break;
    }
    
}