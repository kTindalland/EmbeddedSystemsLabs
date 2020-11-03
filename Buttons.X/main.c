/*
 * File:   main.c
 * Author: kaiti
 *
 * Created on 02 November 2020, 10:24
 */


#include <xc.h>
#include "buttons.h"

//begin config
#pragma config FOSC = HS // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = ON // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
//end config

void main(void) {
    
    TRISB = 0x00;
    PORTB = 0x00;
    
    for (;;) {
        
        int matrixResults[4][4];
        checkMatrixButtons(matrixResults);
        
        PORTB = matrixResults[0][0];
        
        /*if (matrixResults[0][0]) {
            
        }
        else {
            PORTB = 0x00;
        }*/
        
        
        
        
        
    }
    
    
    
    return;
}
