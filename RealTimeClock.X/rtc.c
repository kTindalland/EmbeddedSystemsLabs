#include "rtc.h"
#include <xc.h>

uch readCH() {
    uch secsByte = readByte(RTC_SEC);
    
    return (secsByte & 0x80) >> 7;
}

uch readByte(uch addr) {
    uch readAddr = addr | RTC_READ;
    uch result = 0;
    
    SCLK = 0;
    RST = 0;
    
    // Start transaction 
    RST = 1;
    uch value;
    // Send addr
    TRISB = TRISB & 0xEF; // Set TRISB4 to output
    for (int i = 0; i < 8; i++) {
        value = (readAddr & 0x80) >> 7;
        RTC_IO = value;
               
        SCLK = 1;
        
        SCLK = 0;
        
        readAddr <<= 1;
    }
    
    TRISB = TRISB | 0x10; // Set TRISB4 to input
    // Read result 
    for (int i = 0; i < 8; i++) {
        // Read
        value = RTC_IO;
        
        result >>= 1;
        
        if (value) result |= 0x80;
        
        // Put up
        SCLK = 1;
        
        // Put down
        SCLK = 0;
    }
    
    RST = 0;
    
    return result;    
}


void writeByte(uch addr, uch data) {
    uch writeAddr = addr | RTC_WRITE;
    
    SCLK = 0;
    RST = 0;
    
    RST = 1;
    uch value;
    // Send addr
    TRISB = TRISB & 0xEF; // Set TRISB4 to output
    for (int i = 0; i < 8; i++) {
        value = (writeAddr & 0x80) >> 7;
        
        RTC_IO = value;
        
        SCLK = 1;
        
        SCLK = 0;
        
        writeAddr <<= 1;
    }
    
    // Send data
    for (int i = 0; i < 8; i++) {
        value = (data & 0x80) >> 7;
        
        RTC_IO = value;
        
        SCLK = 1;
        
        SCLK = 0;
        
        data <<= 1;
    }
    
    RST = 0;
}

void clearWP() {
    
    writeByte(RTC_CTRL, 0x00);
    
}