#include<p18f242.h>
#include <xlcd.h>
#include<adc.h> 
#include<stdlib.h> 
#include <delays.h>
#pragma config OSC = XT, PWRT = ON, WDT = OFF, LVP = OFF, DEBUG = OFF
#pragma config CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF, CPB = OFF, CPD = OFF
#pragma config WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF, WRTB = OFF,WRTC = OFF, WRTD = OFF
#pragma config EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF, EBTRB = OFF

void DelayFor18TCY( void )
{
Nop(); Nop(); Nop();
Nop(); Nop(); Nop();
Nop(); Nop(); Nop();
Nop(); Nop(); Nop();
}
void DelayPORXLCD (void)
{
Delay1KTCYx(60); // Delay of 15ms
// Cycles = (TimeDelay * Fosc) / 4
// Cycles = (15ms * 16MHz) / 4
// Cycles = 60,000
return;
}
void DelayXLCD (void)
{
Delay1KTCYx(20); // Delay of 5ms
// Cycles = (TimeDelay * Fosc) / 4
// Cycles = (5ms * 16MHz) / 4
// Cycles = 20,000
return;
}
void main (void)
{ while(1){
char sicaklik[]={""};
char isim[]={"BARIS GOZDE"};
OpenXLCD( FOUR_BIT & LINES_5X7 );
OpenADC( ADC_FOSC_32 & ADC_RIGHT_JUST & ADC_8ANA_0REF, ADC_CH0 & ADC_INT_OFF );
TRISA=1;
TRISB=0; 
TRISD=0; 
PORTB=0; 
PORTD=0; 
WriteCmdXLCD(CURSOR_OFF & BLINK_OFF);
Delay10TCYx(5); 
while( BusyXLCD() );
WriteCmdXLCD(0x01);  
while(BusyXLCD() ); 
putsXLCD(isim);    
while(1){  
Delay100TCYx(25);
ConvertADC ();
while(BusyADC());
itoa(ReadADC()*0.48828125,sicaklik);
Delay100TCYx(25);
WriteCmdXLCD(0xC0);
while(BusyXLCD() );
putsXLCD(sicaklik);
if(ReadADC()*0.48828125>=30 || ReadADC()*0.48828125<=0)
PORTD=0;
if(ReadADC()*0.48828125<10 && ReadADC()*0.48828125>=0)
{PORTD=0;
PORTDbits.RD0=1;
}
if(ReadADC()*0.48828125>=10 && ReadADC()*0.48828125<20)
{
PORTD=0;
PORTDbits.RD1=1;
}
if(ReadADC()*0.48828125>=20 && ReadADC()*0.48828125<30 )
{PORTD=0;
PORTDbits.RD2=1;
}
}
CloseADC();
}
}