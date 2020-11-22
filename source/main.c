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
    /* Insert DDR and PORT initializations */

    /* Insert your solution below */
    while (1) {

    }
    return 1;
}
