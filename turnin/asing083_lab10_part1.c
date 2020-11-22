/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <timer.h>
#include <bit.h>
#include <keypad.h>
#include <scheduler.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

/*
unsigned char GetKeypadKey(){
	PORTC = 0xEF;
	asm("nop");
	if(GetBit(PINC, 0) == 0) {return('1'); }
        if(GetBit(PINC, 1) == 0) {return('4'); }
        if(GetBit(PINC, 2) == 0) {return('7'); }
        if(GetBit(PINC, 3) == 0) {return('*'); }

        PORTC = 0xDF;
        asm("nop");
        if(GetBit(PINC, 0) == 0) {return('2'); }
        if(GetBit(PINC, 1) == 0) {return('5'); }
        if(GetBit(PINC, 2) == 0) {return('8'); }
        if(GetBit(PINC, 3) == 0) {return('0'); }

        PORTC = 0xBF;
        asm("nop");
        if(GetBit(PINC, 0) == 0) {return('3'); }
        if(GetBit(PINC, 1) == 0) {return('6'); }
        if(GetBit(PINC, 2) == 0) {return('9'); }
        if(GetBit(PINC, 3) == 0) {return('#'); }

	return('\0');
}
int main(void){
	unsigned char x;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xF0; PORTC = 0x0F;
	while(1){
		x = GetKeypadKey();
		switch(x){
			case '\0': PORTB = 0x1F; break;
			case '1': PORTB = 0x01; break;

			default: PORTB = 0x1B; break;

		}
	}
}

*/



int outputA = 0x00;


enum STATES{keyCases}state;

int tick(int state){
	unsigned char y;
	y = GetKeypadKey();
	switch(state){
		case keyCases:
		switch(y) {
				case '\0': outputA = 0x1F; break;
				case '1': outputA = 0x01; break;
				case '2': outputA = 0x02; break;
				case '3': outputA = 0x03; break;
                        	case '4': outputA = 0x04; break;
                        	case '5': outputA = 0x05; break;
                        	case '6': outputA = 0x06; break;
                        	case '7': outputA = 0x07; break;
                        	case '8': outputA = 0x08; break;
                        	case '9': outputA = 0x09; break;
                        	case 'A': outputA = 0x0A; break;
                        	case 'B': outputA = 0x0B; break;
                        	case 'C': outputA = 0x0C; break;
                        	case 'D': outputA = 0x0D; break;
                        	case '*': outputA = 0x0E; break;
                        	case '0': outputA = 0x00; break;
                        	case '#': outputA = 0x0F; break;
                        	default: outputA = 0x1B; break;
				}	
			state = keyCases;
			PORTB = outputA;
			break;
	}
	return state;
}



int main(void) {
    
	DDRB = 0xFF; PORTB = 0x00;	
    	DDRC = 0xF0; PORTC = 0x0F;
	static task task1;
	task *tasks[] = { &task1 };
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	unsigned char GCD = 10; //temp value


	task1.state = 0;
	task1.period = 100;
	task1.elapsedTime = task1.period;
	task1.TickFct = &tick;

	TimerSet(GCD);
	TimerOn();

	unsigned short i;
    	while (1) {
		for(i = 0; i < numTasks; i++){
			if(tasks[i]->elapsedTime == tasks[i]->period){
				tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
				tasks[i]->elapsedTime = 0;
			}
			tasks[i]->elapsedTime += GCD;
		}
		while(!TimerFlag);
		TimerFlag = 0;
    	}
    return 0;
}
