# MPLAB IDE generated this makefile for use with GNU make.
# Project: timer.mcp
# Date: Tue Mar 18 12:48:56 2014

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

timer.cof : timer.o
	$(LD) /p18F452 /l"C:\MCC18\lib" "timer.o" /u_CRUNTIME /u_DEBUG /z__MPLAB_BUILD=1 /z__MPLAB_DEBUG=1 /o"timer.cof" /M"timer.map" /W

timer.o : timer.c C:/MCC18/h/delays.h C:/MCC18/h/xlcd.h C:/MCC18/h/timers.h C:/MCC18/h/stdlib.h timer.c C:/MCC18/h/p18f452.h C:/MCC18/h/p18cxxx.h C:/MCC18/h/pconfig.h
	$(CC) -p=18F452 "timer.c" -fo="timer.o" -D__DEBUG -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "timer.o" "timer.cof" "timer.hex"

