#include <p18f452.h>
#include <delays.h>
#pragma config OSC = XT, PWRT = ON, WDT = OFF, LVP = OFF, DEBUG = OFF
#pragma config CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF, CPB = OFF, CPD = OFF
#pragma config WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF, WRTB = OFF,WRTC = OFF, WRTD = OFF
#pragma config EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF, EBTRB = OFF
#define buzzer PORTEbits.RE1
const int cikis1[8]={0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF};
const int cikis2[8]={0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF};
const int cikis3[15]={0x01, 0x02, 0x03, 0x04, 0x07, 0x08, 0x0F, 0x10, 0x1F, 0x20, 0x3F, 0x40, 0x7F, 0x80, 0xFF};
void main()
{
int i=0,j=0,k=0,l=0,tutucu=1; 
TRISC=0xFF;
TRISD=0x00;
TRISEbits.TRISE1=0;
PORTD=0x00;
PORTEbits.RE1=0;
buzzer=0;
for(;;)
{
   while(!PORTCbits.RC0)
   {
      while(!PORTCbits.RC0);
      Delay1KTCYx(30); 
      i++; 
      if(i==3)
      { PORTD=0x01; i=0;}
			}
   while(!PORTCbits.RC1)
    {
      PORTD=0x00; 
      while(!PORTCbits.RC1);
      Delay1KTCYx(250);
      for(j=0;j<8;j++)
      { PORTD=cikis1[j];Delay1KTCYx(1000);}
    }    
     while(!PORTCbits.RC2)
    {
      PORTD=0x00; 
      while(!PORTCbits.RC2);
      Delay1KTCYx(250);
      for(j=0;j<8;j++)
      { PORTD=cikis2[j];Delay1KTCYx(1000);}
    } 
    while(!PORTCbits.RC3)
    {
      PORTD=0x00; 
      while(!PORTCbits.RC3);
      Delay1KTCYx(250);
      for(j=0;j<15;j++)
      { PORTD=cikis3[j];Delay10KTCYx(30);}
    }
    while(!PORTCbits.RC4)
    {
      PORTD=0x00; 
      while(!PORTCbits.RC4);
      PORTD=0x55;
    }
    while(!PORTCbits.RC5)
    {
      PORTD=0x00; 
      while(!PORTCbits.RC5);
      PORTD=0xAA;
    }
     while(!PORTCbits.RC6)
   {
      while(!PORTCbits.RC6);
      Delay1KTCYx(30); 
      k++; 
      if(k<8){
      PORTD=tutucu;
      tutucu=tutucu<<1;
	   }
      if(k>=8)
      { 
       if(k==8)tutucu=0x80; 
       PORTD=tutucu;
       tutucu=tutucu>>1; 
        if(k==14)k=0;
        }
      	}
     while(!PORTCbits.RC7)
    {
      PORTD=0x00; 
      while(!PORTCbits.RC7);
      PORTEbits.RE1=1;
      Delay10KTCYx(100);
      PORTEbits.RE1=0;
    }
}
}