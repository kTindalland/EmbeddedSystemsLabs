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
#include <stdlib.h>


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
        char bytes[9];
        
        therm_init();
        
        skip_ROM();
        write_byte(0xBE);
        
        
        
        for (int i = 0; i < 9; i++) {
            bytes[i] = read_byte();
        }
        
        // Check if it's 40 for now
        
        int result = bytes[1];
        result <<= 8;
        result |= bytes[0];
        
        TRISB = 0x00;
        PORTB = bytes[0];
        
        init();
        lcd_soft_init();
        
        double converted_result = therm_convert_number(result);
        int* status;
        
        char* snum = ftoa(converted_result, status);
            
        
            
            
        writestr(snum);
        
        
        
        
        delayBy(1000);
        
    }
}
