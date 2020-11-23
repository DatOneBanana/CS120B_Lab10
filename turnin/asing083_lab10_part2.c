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

unsigned char outputA = 0x00;
unsigned char temp = 0x00;

enum KeyInput_STATES{keyCases};

int tick(int state){
	unsigned char y;
	y = GetKeypadKey();
	switch(state){
		case keyCases:
		switch(y) {
				case '\0': break;
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
			break;
	}
	return state;
}

enum look_STATES{Start, pound, first, second, third, fourth, fifth, display7, failed};
unsigned char temp2 = 0x00;

int tick2(int state){
	temp = outputA;
	temp2 = ~PINB & 0x80;
	switch(state){
		case Start:
			state = pound;
			break;
		case pound:
			if(temp2){
				state = failed;
				break;
			}
			if(temp == 0x0F){
				state = first;
			}else{
				state = pound;
			}
			break;
		case first:
			if(temp == 0x01){
				state = second;
			}else{
				state = first;
			}
			break;
		case second:
			if(temp == 0x02){
				state = third;
			}else{
				state = second;
			}
			break;
		case third:
			if(temp == 0x03){
				state = fourth;
			}else{
				state = third;
			}
			break;
		case fourth:
			if(temp == 0x04){
				state = fifth;
			}else{
				state = fourth;
			}
			break;
		case fifth:
			if(temp == 0x05){
				state = display7;
			}else{
				state = fifth;
			}
			break;
		case display7:
			state = pound;
			break;
		case failed:
			state = pound;
			break;
		}
	switch(state){
		case pound:
			break;
		case first:
			break;
		case third:
			break;
		case fourth:
			break;
		case fifth:
			break;
		case display7:
			PORTB = 0x01;
			break;
		case failed:
			PORTB = 0x00;
			break;
		}
	return state;
}

int main() {
   	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x0F; PORTB = 0xF0;	
    	DDRC = 0xF0; PORTC = 0x0F;
	static task task1, task2;
	task *tasks[] = { &task1, &task2};
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	unsigned char GCD = 1; //temp value


	task1.state = 0;
	task1.period = 1;
	task1.elapsedTime = task1.period;
	task1.TickFct = &tick;

	task2.state = 0;
	task2.period = 1;
	task2.elapsedTime = task2.period;
	task2.TickFct = &tick2;

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
