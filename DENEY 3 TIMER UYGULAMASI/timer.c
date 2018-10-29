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
void  timer0 (void)
{int i=0;
if(INTCONbits.TMR0IF && INTCONbits.TMR0IE)	 
{
i++;
}
}
#pragma interrupt timer2
void timer2(void)
{  int sayac=0;
char zaman []={""};
int s,k,j;
if(PIR1bits.TMR2IF==1)
{	char bekle[]=" Bekleme";
while( BusyXLCD() );
putsXLCD(bekle);
itoa(sayac,zaman);
WriteCmdXLCD(0xC0);
putsXLCD(zaman);
for(j=0;j<20;j++){
for(s=0;s<1;s++){
sayac++;
for(k=0;k<540;k++){
itoa(sayac,zaman);
WriteCmdXLCD(0xC0);
putsXLCD(zaman);
}
}
}
}
}
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
void toplamurun(void)
{
int sonuc;
char sayi []={""};
char urun []=" Toplam Urun";
while( BusyXLCD() );
WriteCmdXLCD(0x01);
putsXLCD(urun);
WriteCmdXLCD(0xC0);
sonuc=ReadTimer0();
itoa(sonuc,sayi);
putsXLCD(sayi);
}

void main(void)
{

	int sonuc;
	char sayi []={"  "};
char urun []=" Toplam Urun";
	TRISB=0; // B portu output ayarlandý
	TRISC=0; // C portu output olarak ayarlandý
	TRISAbits.TRISA4=1;
	PORTB=0; // PORTB baþlangýç deðerleri sýfýrlandý
	PORTC=0; // PORTC baþlangýç deðerleri sýfýrlandý
OpenTimer0( TIMER_INT_ON &T0_16BIT & T0_SOURCE_EXT & T0_PS_1_1);
OpenTimer2( TIMER_INT_ON & T2_PS_1_1 & T2_POST_1_1);
INTCONbits.GIE = 1; //enable interrupts
INTCONbits.TMR0IE=1;
PIE1bits.TMR2IE=1;
OpenXLCD(FOUR_BIT & LINES_5X7); //lcd 4bit modda ve 5x7 çözünürlükte çalýþtýrýldý
while( BusyXLCD() );
WriteCmdXLCD( CURSOR_OFF & BLINK_OFF);// imleci ve cursorü kapat
while( BusyXLCD() );
WriteCmdXLCD(0x01);
putsXLCD(urun);
WriteCmdXLCD(0xC0);
sonuc=ReadTimer0();
itoa(sonuc,sayi);
putsXLCD(sayi);

while(1) 
{ 
sonuc=ReadTimer0();
itoa(sonuc,sayi);
if(sonuc>0 & sonuc<10)
{
PORTCbits.RC1=1;
while( BusyXLCD() );
WriteCmdXLCD(0xC0);
putsXLCD(sayi);
}
else if(sonuc==10){
WriteCmdXLCD(0xC0);
putsXLCD(sayi);
PORTCbits.RC1=0;
WriteTimer0(0);          //timer0 kesmesini sýfýrla
WriteCmdXLCD(0x01);
timer2();
while( BusyXLCD() );
WriteCmdXLCD(0x01);
putsXLCD(urun);
WriteCmdXLCD(0xC0);
sonuc=ReadTimer0();
itoa(sonuc,sayi);
putsXLCD(sayi);
}
}
}