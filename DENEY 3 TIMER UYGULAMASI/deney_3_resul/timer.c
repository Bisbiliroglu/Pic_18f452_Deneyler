#include <p18f452.h>
#include<delays.h>
#include<xlcd.h>
#include<timers.h>
#include<stdlib.h>
#pragma config OSC=XT, PWRT = ON, WDT = OFF, LVP = OFF, DEBUG = OFF
#pragma config CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF, CPB = OFF, CPD = OFF
#pragma config WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF, WRTB = OFF,WRTC = OFF, WRTD = OFF
#pragma config EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF, EBTRB = OFF
#pragma interrupt timer0
#pragma interrupt timer2
void DelayFor18TCY(void)
{
Nop(); Nop(); Nop();
Nop(); Nop(); Nop();
Nop(); Nop(); Nop(); 
Nop(); Nop(); Nop();
}
void DelayPORXLCD(void)
{
Delay1KTCYx(60);// Delay of 60ms
// Cycles = (TimeDelay * Fosc) / 4
// Cycles = (60ms * 4MHz) / 4
// Cycles = 60,000
return;
}

void DelayXLCD (void)
{
Delay1KTCYx(100); // Delay of 100ms
// Cycles = (TimeDelay * Fosc) / 4
// Cycles = (100ms * 4MHz) / 4
// Cycles = 100,000
return;
}
void timer2(void)
{ int a=0,k ,j;
char zaman []={""};
char bekleme[]=" Bekleme";
if(PIR1bits.TMR2IF==1)
{
while( BusyXLCD() );
putsXLCD(bekleme);
itoa(a,zaman);
WriteCmdXLCD(0xC0);
putsXLCD(zaman);
for(j=0;j<20;j++){
a++;
Delay10KTCYx(100);
itoa(a,zaman);
WriteCmdXLCD(0xC0);
putsXLCD(zaman);
}
}
}
void main(void)
{

	char sayi []={""};
	char toplam []=" Toplam Urun";
	TRISB=0; 
	TRISC=0;
	TRISAbits.TRISA4=1;
	PORTB=0; 
	PORTC=0;
OpenTimer0( TIMER_INT_ON &T0_16BIT & T0_SOURCE_EXT & T0_PS_1_1);
OpenTimer2( TIMER_INT_ON & T2_PS_1_1 & T2_POST_1_1);
INTCONbits.GIE = 1; 
INTCONbits.TMR0IE=1;
PIE1bits.TMR2IE=1;
OpenXLCD(FOUR_BIT & LINES_5X7); 
while( BusyXLCD() );
WriteCmdXLCD( CURSOR_OFF & BLINK_OFF);
while( BusyXLCD() );
WriteCmdXLCD(0x01);
putsXLCD(toplam);
WriteCmdXLCD(0xC0);
itoa(ReadTimer0(),sayi);
putsXLCD(sayi);

for(;;)
{ 
itoa(ReadTimer0(),sayi);
if(ReadTimer0()>0 & ReadTimer0()<10)
{
PORTCbits.RC1=1;
while( BusyXLCD() );
WriteCmdXLCD(0xC0);
putsXLCD(sayi);
}
else if(ReadTimer0()==10){
WriteCmdXLCD(0xC0);
putsXLCD(sayi);
PORTCbits.RC1=0;
WriteTimer0(0);
WriteCmdXLCD(0x01);
timer2();
while( BusyXLCD() );
WriteCmdXLCD(0x01);
putsXLCD(toplam);
WriteCmdXLCD(0xC0);
INTCONbits.TMR0IF==1;
INTCONbits.TMR0IE==1;
itoa(ReadTimer0(),sayi);
putsXLCD(sayi);
}
}
}
