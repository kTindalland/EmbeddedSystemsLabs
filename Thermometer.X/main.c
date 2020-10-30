/*
 * File:   main.c
 * Author: 578004
 *
 * Created on 26 October 2020, 14:06
 */

#include <xc.h>
#include "thermometer.h"
#include "delay.h"
#include "lcd.h"
#include <stdio.h>


//begin config
#pragma config FOSC = HS // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = ON // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
//end config

void init() {
    ADCON1 = 0x07; // Set port a to ordinary IO
    TRISA = 0x00;
    TRISD = 0x00;
}

void main(void) {
    
    
    for (;;) {
        
        
        therm_init();
        skip_ROM();
        
        write_byte(0xBE);
        
        char bytes[9];
        
        for (int i = 0; i < 9; i++) {
            bytes[i] = read_byte();
        }
        
        // Check if it's 40 for now
        
        int result = 0;
        result |= bytes[1] << 8;
        result |= bytes[0];
        
        
        init();
        lcd_soft_init();
        
        if (result & 0x280) {
            char snum[10];
            
            sprintf(snum, "%lf", therm_convert_number(result));
            
            writestr(snum);
        }
        else {
            char snum[5];
            
            sprintf(snum, "%lf", therm_convert_number(result));
            
            writestr(snum);
        }
        
        
        
        
        delayBy(1000);
        
    }
}
