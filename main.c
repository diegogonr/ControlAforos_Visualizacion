/*
 * ****************************ETAPA CONTROL-ACTUADOR************************ 
 * Descripción: Se tiene un torniquete el cual estará ubicado en cada salón, este
 * dispositivo es representado por un motor paso a paso. Tenemos 2 botonos el cuál 
 * uno de ellos representa la entrada de personas cada vez que es presionado y el otro
 * representa la salida de personas. Además, se tiene un tercer botón que será 
 * usado en caso de emergencia habilitando el torniquete para la salida de personas 
 * 
 * RC0 = Entrada de personas
 * RC1 = Salida de personas
 */

  

#include "Conf.h"
#include "MiLCD.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"


#define Total_Personas 5
 
char cod1;                                 //codigo de referencia de cada tarjeta 
char texto [10];                           //10 registros x 8 bits
char cont [10];
int i;


void InitPort(void){
    ADCON1bits.PCFG = 0x0F;                   //Pines en digital
    TRISC =0xff;                              //Entrada
}

  
void main(void) {
    cod1 = 158;
    LCD_Init();
    InitPort();
   
    LCD_gotoXY(0,0);                   
    LCD_Cadena("RFID LECTURA TAG");
    __delay_ms(1000);
    
     while(1){
         
               if((PORTCbits.RC0 == 1) && (i<Total_Personas))    //se ejecuta cuando detecta el button 1
                   {                              
                        __delay_ms (200);                        //efecto rebote
                        while(PORTCbits.RC0 == 1);               // el bit sigue siendo 1 seguirá en este bucle
                        sprintf  (texto,"Entro: %d  ",cod1);     // cod1 convierte en una cadena
                        LCD_gotoXY(1,0);
                        LCD_Cadena(texto);
                        i++;                                     //aumento en 1
                        sprintf(cont, "# %d ", i);               //conversión de binario a decimal     
                        LCD_gotoXY(1,12); 
                        LCD_Cadena(cont);
                        __delay_ms(200);                         

                   }
                      
               else if ((PORTCbits.RC1 == 1) && (i>0) )          //se ejecuta cuando detecta el button 2
                    {
                        __delay_ms (200);                        //efecto rebote
                        while(PORTCbits.RC1 == 1);               // el bit sigue siendo 1 seguirá en este bucle
                        sprintf  (texto,"Salio: %d  ",cod1);     // cod1 convierte en una cadena
                        LCD_gotoXY(1,0);                     
                        LCD_Cadena(texto);
                        i--;                                     //disminución en 1
                        sprintf(cont, "# %d ", i);               //conversión de binario a decimal     
                        LCD_gotoXY(1,12); 
                        LCD_Cadena(cont);
                        __delay_ms(200);                         
                    }

                if (i==Total_Personas) 
                    {
                        __delay_ms (200);
                        LCD_gotoXY(1,0);
                        LCD_Cadena("***AULA LLENA***");

                    }
               
            }
 }

   
    
