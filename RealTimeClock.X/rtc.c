#include "rtc.h"
#include <xc.h>

void rtcInit(){
    TRISB = 0x00;
    PORTB = 0xFF;
}

void clearWP() {
    
    writeByte(RTC_CTRL, 0x00);
    
}

uch readCH() {
    uch secsByte = readByte(RTC_SEC);
    
    return (secsByte & 0x80) >> 7;
}

void startClock() {
    uch currentSeconds = readByte(RTC_SEC);
    
    uch newSeconds = currentSeconds & 0x7F;
    
    writeByte(RTC_SEC, newSeconds);
}

void stopClock() {
    uch currentSeconds = readByte(RTC_SEC);
    
    uch newSeconds = currentSeconds | 0x80;
    
    writeByte(RTC_SEC, newSeconds);
}

uch readByte(uch addr) {
    rtcInit();
    
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
    
    // Flip the result
    result = reverseBits(result);
    
    
    return result;    
}

void writeByte(uch addr, uch data) {
    rtcInit();
    
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

void setDate(rtcDate date) {
    
    uch dateByte = convertDate(date.date, date.month, date.year);
    writeByte(RTC_DATE, dateByte);
    
    uch monthByte = convertMonth(date.month);
    writeByte(RTC_MONTH, monthByte);
    
    uch yearByte = convertYear(date.year);
    writeByte(RTC_YEAR, yearByte);
    
    uch dayByte = convertDay(date.day);
    writeByte(RTC_DAY, dayByte);
    
}

void setTime(rtcTime time) {
    
    uch secByte = convertSecs(time.secs);
    writeByte(RTC_SEC, secByte);
    
    uch minsByte = convertMins(time.mins);
    writeByte(RTC_MINS, minsByte);
    
    uch hoursByte = convertHours(time.hours, time.AMPM);
    writeByte(RTC_SEC, hoursByte);
    
}

void setDateTime(rtcDateTime datetime) {
    setDate(datetime.date);
    setTime(datetime.time);
}

void getDate(rtcDate* date) {
    uch dateByte = readByte(RTC_DATE);
    date->date = convertReadDate(dateByte);
    
    uch monthByte = readByte(RTC_MONTH);
    date->month = convertReadMonth(monthByte);
    
    uch yearByte = readByte(RTC_YEAR);
    date->year = convertReadYear(yearByte);
    
    uch dayByte = readByte(RTC_DAY);
    date->day = convertReadDay(dayByte);
}

void getTime(rtcTime* time) {
    uch secsByte = readByte(RTC_SEC);
    time->secs = convertReadSecs(secsByte);
    
    uch minsByte = readByte(RTC_MINS);
    time->mins = convertReadMins(minsByte);
    
    uch hoursByte = readByte(RTC_HOURS);
    time->hours = convertReadHours(hoursByte, &time->AMPM);
}

void getTime24(rtcTime* time) {
    
    getTime(time);
    
    if (time->AMPM != NULL) {
        convertHourFormat(time);
    }
    
}

void getTime12(rtcTime* time) {
    
    getTime(time);
    
    if (time->AMPM == NULL) {
        convertHourFormat(time);
    }
    
}

void convertHourFormat(rtcTime* time) {
    // If 24 to 12
    if (time->AMPM == NULL) {
        time->AMPM = AM;
        
        if (time->hours > 12) {
            time->hours -= 12;
            time->AMPM = PM;
        }
    }
    else { // If 12 to 24
        if (time->AMPM == PM) {
            time->hours += 12;
        }
        
        if (time->hours >= 24) time->hours = 0;
    }
}

void getDateTime(rtcDateTime* datetime) {
    getTime(&datetime->time);
    getDate(&datetime->date);
}

uch reverseBits(uch number) {
    uch reversedNumber = 0;
    
    while (number > 0) {
        reversedNumber <<= 1;
        if (number & 1 == 1) {
            reversedNumber ^= 1;
        } 
        number >>= 1;
    }
    
    return reversedNumber;
}