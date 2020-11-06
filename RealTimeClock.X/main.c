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
    
    uch hoursByte = convertHours(11, 0);
    
    writeByte(RTC_HOURS, hoursByte);
    
    for (;;) {
        
        uch hoursFromClock = readByte(RTC_HOURS);
        
        int hours = convertReadHours(hoursFromClock);
        
        if (hours == 2) {
            PORTC = 0xFF;
        }
        else if (seconds == 8) {
            PORTC = 0xFF;
        }
        else {
            PORTC = 0x00;
        }
        
        for (int i = 0; i < 200; i++);
        
    }
    
    return;
}
