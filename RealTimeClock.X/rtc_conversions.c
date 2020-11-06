#include "rtc.h"

uch convertSecs(int sec) {
	if (sec < 0 || sec >= 60) return RTC_ERROR;
    
    uch result = 0;
    
    if (readCH()) result |= 0x80;
    
    uch ones = sec % 10;
    uch tens = (sec - ones) / 10;
    
    result |= ones;
    result |= (tens << 4);
    
    return result;
}

uch convertMins(int mins) {
	if (mins < 0 || mins >= 60) return RTC_ERROR;
    
    uch result = 0;
    
    uch ones = mins % 10;
    uch tens = (mins - ones) / 10;
    
    result |= ones;
    result |= (tens << 4);
    
    return result;
}

uch convertHours(int hours, int AMPM) {
	if (AMPM == NULL && (hours < 0 || hours >= 24)) return RTC_ERROR;
    if (AMPM != NULL && (hours < 1 || hours >= 13)) return RTC_ERROR;
    
    uch ones = hours % 10;
    uch tens = (hours - ones) / 10;
    
    uch result = 0;
    
    if (AMPM != NULL){ // 12Hr Mode
        result |= 0x80;// 12Hr Mode
        if (AMPM) result |= 0x40; //PM    
    }
    
    result |= ones;
    result |= (tens <<4);
    
    return result;
}

uch convertDate(int date, int month, int year) {
	if (month != 2){
        if ((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8) ||(month == 10) ||  (month == 12)){
            if (date < 1 || date >= 31) return RTC_ERROR;
        }
        else if (date < 1 || date >= 30) return RTC_ERROR; // Month
    }
    else{
        int isLeapYear = 0;
        if (year % 400 == 0)        isLeapYear = 1;
        else if (year % 100 == 0)   isLeapYear = 0;
        else if (year % 4 == 0)     isLeapYear = 1;
        else                        isLeapYear = 0;
        
        if (isLeapYear && (date < 1 || date >= 29)) return RTC_ERROR; // Leap Year
        else if (date < 1 || date >= 28) return RTC_ERROR;
    }
    
    uch result = 0;
    
    uch ones = date % 10;
    uch tens = (date - ones) / 10;
    
    result |= ones;
    result |= (tens << 4);
    
    return result;
}

uch convertMonth(int month) {
	if (month < 1 || month >= 13) return RTC_ERROR;
    
    uch result = 0;
    
    uch ones = month % 10;
    uch tens = (month - ones) / 10;
    
    result |= ones;
    result |= (tens << 4);
    
    return result;
}

uch convertDay(int day) {
	if (day < 1 || day >= 8) return RTC_ERROR;
    
    uch result = 0;
    result |= day;
    
    return result;
}

uch convertYear(int year) {
	if (year < 0 || year >= 100) return RTC_ERROR;
    
    uch result = 0;
    
    uch ones = year % 10;
    uch tens = (year - ones) / 10;
    
    result |= ones;
    result |= (tens << 4);
    
    return result;
}





int convertReadSecs(uch secs) {
	int result = 0;
    uch ones = secs & 0x0F;
    uch tens = ((secs & 0x70) >> 4 ) * 10;
    
    result += ones;
    result += tens;
    
    return result;
}

int convertReadMins(uch mins) {
	int result = 0;
    uch ones = mins & 0x0F;
    uch tens = ((mins & 0x70) >> 4 ) * 10;
    
    result += ones;
    result += tens;
    
    return result;
}

int convertReadHours(uch hours, int* AMPM) {
    int result = 0;
    
    uch hour12 = hours & 0x80;
    if (hour12) *AMPM = hours & 0x20;
    else *AMPM = NULL;
    
    uch ones = hours & 0x0f;
    uch tens;
    
    if (hour12) tens = (hours & 0x10);
    else tens = (hours & 0x30) >> 4;
    
    result += ones;
    result += tens;

	return result;
}

int convertReadDate(uch date) {
	int result = 0;
    uch ones = date & 0x0F;
    uch tens = ((date & 0x30) >> 4 ) * 10;
    
    result += ones;
    result += tens;
    
    return result;
}

int convertReadMonth(uch month) {
	int result = 0;
    uch ones = month & 0x0F;
    uch tens = ((month & 0x10) >> 4 ) * 10;
    
    result += ones;
    result += tens;
    
    return result;
}

int convertReadDay(uch day) {
	int result = 0;
    
    result = day & 0x07;
    
    return result;
}

int convertReadYear(uch year) {
	int result = 0;
    uch ones = year & 0x0F;
    uch tens = ((year & 0xF0) >> 4 ) * 10;
    
    result += ones;
    result += tens;
    
    return result;
}

