#include <p18f452.h>
#include <delays.h>
#include <xlcd.h>
#include <timers.h>
#pragma config OSC = XT, PWRT = ON, WDT = OFF, LVP = OFF, DEBUG = OFF
#pragma config CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF, CPB = OFF, CPD = OFF
#pragma config WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF, WRTB = OFF,WRTC = OFF, WRTD = OFF
#pragma config EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF, EBTRB = OFF
int i = 0;
int j=0,k=0,kontrol=1,l=0;
char data1[]="Urun adedi ";                    //data1 deðiþkenine veri string olarak tanýmlandý
char data2[]="Bekleme ";
char data3[]="Urun adedi 0";
void LCD_zamanlayici(int b)
{
  WriteCmdXLCD(0x01);                             //Ekraný temizle ve kursörü baþa getir komutu gönderiliyor
  putsXLCD(data2);
  while(BusyXLCD());
  putcXLCD(b/10+48);
  while(BusyXLCD());
  putcXLCD(b%10+48);
  b++;
   return;
}

void int_handler(void);
#pragma code high_vector=0x08
void high_interrupts (void) {
_asm GOTO int_handler _endasm
}
#pragma code low_vector=0x18
void low_interrupts (void) {
_asm GOTO int_handler _endasm
}
#pragma code
#pragma interrupt int_handler
void int_handler(void) {
if(PIR1bits.TMR2IF == 1) {
while(kontrol==0)
   { 
        PORTCbits.RC1=0;
        LCD_zamanlayici(k);
        Delay10KTCYx(100);
        k++;  if(k==21)
         {
             k=0;kontrol=1;l++;            
			}
   }
  WriteTimer0(0);
  PIR1bits.TMR2IF = 0;
  PIE1bits.TMR2IE = 0;
}
}

void DelayFor18TCY( void )                      //xlcd kütüphanesinin ihtiyaç duyduðu bekleme fonksiyonlarý
{
Nop();Nop();Nop();Nop();Nop();
Nop();Nop();Nop();Nop();Nop();Nop();            //18 komut süresi bekleme fonksiyonu oluþturuldu
Nop();Nop();Nop();Nop();Nop();Nop();Nop();
} 
void DelayPORXLCD (void)
{
Delay1KTCYx(60);                                // 60 ms bekleme fonksiyonu oluþturuldu
return;
}
void DelayXLCD (void)  
{
Delay1KTCYx(20);                                // 20 ms bekleme fonksiyonu oluþturuldu
return;
}

void LCD_sayici(int a)
{ 
  WriteCmdXLCD(0x01);                             //Ekraný temizle ve kursörü baþa getir komutu gönderiliyor
  putsXLCD(data1);
  while(BusyXLCD());
  putcXLCD(a/10+48);
  while(BusyXLCD());
  putcXLCD(a%10+48);
  Delay10KTCYx(5);
  a++;  
} 

void main(void) {
TRISC = 0;
PORTC = 0;
OpenXLCD(FOUR_BIT&LINES_5X7);
CloseTimer1();
WriteCmdXLCD(BLINK_OFF&CURSOR_OFF);             //kursörü kapatýyoruz
OpenTimer2(TIMER_INT_ON & T2_PS_1_16 & T2_POST_1_16);
PR2 = 250;
RCONbits.IPEN = 1;
while(1)
{
 
   while(kontrol==1)
  {
   
    PORTCbits.RC1=1;
    
       i=ReadTimer0();
       Delay10KTCYx(5);
       LCD_sayici(i);
   
    if(i==10)
    {  kontrol=0;
       CloseTimer0();
       CloseTimer1();
       INTCONbits.GIE = 1;
       PIE1bits.TMR2IE = 1;
       i=0;
    } 
  }
}
}
