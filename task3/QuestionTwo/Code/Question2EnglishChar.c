/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
� Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Question 2 - task 3
Version : 
Date    : 12/28/2020
Author  :  Sepehr rezaei - 962023012
Company : 
Comments: 


Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/

#include <mega16.h>
#include <alcd.h>


int timerOverflowCounter;
int xLenght;
int yLenght;
int characterPosition;

char characters[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
      timerOverflowCounter++;
      if (characterPosition < 26 ) {
        if(timerOverflowCounter == 500 ){

          lcd_putchar(characters[characterPosition]);
          characterPosition += 1;
          //incress x position
          xLenght=xLenght+1;
          
          //check need to change line 
          if(characterPosition==20){
            xLenght=0;
            yLenght=1;
          }

          lcd_gotoxy(xLenght,yLenght);
          timerOverflowCounter=0;
       }
      }else{
        TCCR0=0x00;
        TIMSK=0x00;
      }
      
      TCNT0=0x00;
}


void main(void)
{

    DDRC=0x00;
    PORTC=0x00; 
    
    xLenght=0;
    yLenght=0;
    timerOverflowCounter=0;
    characterPosition=0;   
    
    TCCR0=0x01;
    TCNT0=0x00;
    OCR0=0x00;
    TIMSK=0x01; 
    
    lcd_init(20);
    #asm("sei")

    while (1)
    {
    }


}
