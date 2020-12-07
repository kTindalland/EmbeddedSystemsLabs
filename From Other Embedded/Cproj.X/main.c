/*
 * File:   main.c
 * Author: kaiti
 *
 * Created on 08 October 2020, 17:29
 */


#include <xc.h>
#include "main.h"
#include "delay.h"

#define DELAY_ITER 0xff

void seg();

void main(void) {
    init();
    
    
    while(1) {
        PORTC++;
        delay();
    }
    
    
    return;
}

void seg() {
    while(1) {
        init();
        PORTD=0xc0;
        PORTA=0x3a;
        delay();
    }
}

void init() {
    ADCON1=0x07;
    TRISA=0x00;
    TRISB=0x00;
    TRISC=0x00;
    TRISD=0x00;
    
    PORTA=0x00;
    PORTB=0x00;
    PORTC=0x00;
    PORTD=0x00;
}