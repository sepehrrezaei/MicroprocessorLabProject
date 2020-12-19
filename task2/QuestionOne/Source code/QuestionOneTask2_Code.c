/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
� Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Task2 - Question1
Version : 1
Date    : 12/19/2020
Author  : sepehr rezaei
Company : -
Comments: -


Chip type               : ATmega16
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*******************************************************/


#include <mega16.h>
#include <delay.h>
int nums[10] = {0b00111111 , 0b00000110 , 0b01011011 , 0b01001111 , 0b01100110 , 0b01101101 , 0b01111101 , 0b00000111 ,0b01111111 ,0b01101111};
int timerCounterForOverflow = 0;
int counter =0;

interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{
    ++timerCounterForOverflow;
    if(timerCounterForOverflow == 100){
        if(counter < 10){
           PORTD =  nums[counter];
        }else{
           counter = 0 ;
           PORTD = nums[counter];

        }
        counter++;
    }

    TCNT1H=0xFF;
    TCNT1L=0xF0;
}
void main(void)
{
// Declare your local variables here

// Port D initialization
DDRD=0b11111111;
PORTD=0b00000000;
// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 125.000 kHz
// Mode: Normal top=0xFFFF
// OC1A output: Disconnected
// OC1B output: Disconnected
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer Period: 0.52429 s
// Timer1 Overflow Interrupt: On
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x01;
TCNT1H=0xFF;
TCNT1L=0xF0;


// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
MCUCSR=(0<<ISC2);


// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (1<<TOIE1) | (0<<OCIE0) | (0<<TOIE0);

#asm("sei")
while (1)
      {
      // Place your code here
      }
}
