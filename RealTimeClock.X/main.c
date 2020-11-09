/*
 * File:   main.c
 * Author: kaiti
 *
 * Created on 06 November 2020, 10:52
 */


#include <xc.h>
#include "rtc.h"

void main(void) {
    
    rtcTime time;
    
    uch hoursByte = convertHours(11, 0);
    
    writeByte(RTC_HOURS, hoursByte);
    
    for (;;) {
        
        uch hoursFromClock = readByte(RTC_HOURS);
        
        int hours = convertReadHours(hoursFromClock, &time.AMPM);
        
        if (hours == 11) {
            PORTC = 0xFF;
        }
        else {
            PORTC = 0xff;
        }
        
        for (int i = 0; i < 200; i++);
        
    }
    
    return;
}
