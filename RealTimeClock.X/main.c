/*
 * File:   main.c
 * Author: kaiti
 *
 * Created on 06 November 2020, 10:52
 */


#include <xc.h>
#include "rtc.h"

void main(void) {
    TRISC = 0x00;
    TRISB = 0x00;
    PORTB = 0xFF;
    
    clearWP();
    
    uch secsByte = convertSecs(0);
    
    writeByte(RTC_SEC, secsByte);
    
    for (;;) {
        
        uch secsFromClock = readByte(RTC_SEC);
        
        int seconds = convertReadSecs(secsFromClock);
        
        if (seconds == 2) {
            PORTC = 0xFF;
        }
        else if (seconds == 8) {
            PORTC = 0xFF;
        }
        else {
            PORTC = 0x00;
        }
        
        for (int i = 0; i < 500; i++);
        
    }
    
    return;
}
