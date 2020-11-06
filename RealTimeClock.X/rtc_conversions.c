#include "rtc.h"

uch convertSecs(int sec) {
	if (sec < 0 || sec >= 60) return RTC_ERROR;
    
}

uch convertMins(int mins) {
	if (mins < 0 || mins >= 60) return RTC_ERROR;
    
}

uch convertHours(int hours, int is24Hour) {
	if (is24Hour && (hours < 0 || hours >= 24)) return RTC_ERROR;
    if (!is24Hour && (hours < 1 || hours >= 13)) return RTC_ERROR;
    
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
}

uch convertMonth(int month) {
	if (month < 1 || month >= 13) return RTC_ERROR;
    
}

uch convertDay(int day) {
	if (day < 1 || day >= 8) return RTC_ERROR;
    
}

uch convertYear(int year) {
	if (year < 0 || year >= 100) return RTC_ERROR;
    
}





int convertReadSecs(uch secs) {
	
}

int convertReadMins(uch mins) {
	
}

int convertReadHours(uch hours) {
	
}

int convertReadDate(uch date) {
	
}

int convertReadMonth(uch month) {
	
}

int convertReadDay(uch day) {
	
}

int convertReadYear(uch year) {
	
}

