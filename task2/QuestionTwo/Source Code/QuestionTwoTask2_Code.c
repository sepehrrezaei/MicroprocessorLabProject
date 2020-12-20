/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : Task2 - Question 2
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
int SevenSegmentNumbersArry[4] = {0,0,0,0}; // array for indecating which number is showing in 7 segments

int timerZeroOverFlow =0; // timer 0 over flow counter int   
int timerOneOverFlow =0; // timer 1 over flow counter int   
int portcTemp; // template for doing maths and ...
int i = 3; // for going from top to bottom in array SevenSegmentNumbersArry
int lastestSevenSegmentInited = 3;  // can be 0, 1, 2, 3

// Timer 0 overflow interrupt
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
    timerZeroOverFlow++;
    if(timerZeroOverFlow == 2){ 

           portcTemp = PORTC ^ 0b11111111;
           PORTC = portcTemp ^ 0b11111111;
           portcTemp = portcTemp >> 1;
           if(portcTemp == 0){
            portcTemp = 8;
           }
           portcTemp = portcTemp ^ 0b11111111;
           PORTC = portcTemp;
           
           PORTD = nums[SevenSegmentNumbersArry[lastestSevenSegmentInited]];
           lastestSevenSegmentInited--;
           if(lastestSevenSegmentInited == -1 ){
            lastestSevenSegmentInited = 3;
           }
           
           timerZeroOverFlow=0;
    }
    TCNT0=0x00;
}

// Timer1 overflow interrupt
interrupt [TIM1_OVF] void timer1_ovf_isr(void)
{
    timerOneOverFlow++;
    if(timerOneOverFlow == 100){
        SevenSegmentNumbersArry[3]++;  
        //check numbers to incress the counter (recorrect array of 7segs)
        while (i >= 0){
            if( SevenSegmentNumbersArry[i] ==10){
             SevenSegmentNumbersArry[i-1]++;
             SevenSegmentNumbersArry[i]=0;
            }
            i--;
        }
        i=3;
        timerOneOverFlow=0;
    }
    TCNT1H=0xFF;
    TCNT1L=0xF0;
}


void main(void)
{

DDRD=0b11111111;
PORTD=0b00000000;
DDRC=0b11111111;
PORTC=0b11101111;
 // 0b00001000 = 8 decimal


// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (1<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);


// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 8000.000 kHz
// Mode: Normal top=0xFF
// OC0 output: Disconnected
// Timer Period: 0.032 ms
TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (1<<CS02) | (0<<CS01) | (1<<CS00);
TCNT0=0x00;
OCR0=0x00;



// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: 8000.000 kHz
// Mode: Normal top=0xFFFF
// OC1A output: Disconnected
// OC1B output: Disconnected
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer Period: 8.192 ms
// Timer1 Overflow Interrupt: On
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=(0<<COM1A1) | (0<<COM1A0) | (0<<COM1B1) | (0<<COM1B0) | (0<<WGM11) | (0<<WGM10);
TCCR1B=(0<<ICNC1) | (0<<ICES1) | (0<<WGM13) | (0<<WGM12) | (1<<CS12) | (0<<CS11) | (1<<CS10);
TCNT1H=0xFF;
TCNT1L=0xF0;



// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
MCUCR=(0<<ISC11) | (0<<ISC10) | (0<<ISC01) | (0<<ISC00);
MCUCSR=(0<<ISC2);

#asm("sei")
while (1)
      {
      // Place your code here
      }
}
