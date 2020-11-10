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
    clearWP();    
    
    rtcTime time;
    time.AMPM = AM;
    
    uch hoursByte = convertHours(21, AM);
    
    if (hoursByte == RTC_ERROR) exit(1);
    
    writeByte(RTC_HOURS, hoursByte);
    
    for (;;) {
        
        uch hoursFromClock = readByte(RTC_HOURS);
        
        int hours = convertReadHours(hoursFromClock, &time.AMPM);
        
        if (hours == 21 && time.AMPM == NULL) {
            PORTC = 0xFF;
        }
        else {
            PORTC = hours;
        }
        
        for (int i = 0; i < 200; i++);
        
    }
    
    return;
}
