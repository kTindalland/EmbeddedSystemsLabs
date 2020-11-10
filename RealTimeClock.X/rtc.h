/* 
 * File:   rtc.h
 * Author: kaiti
 *
 * Created on 06 November 2020, 10:53
 */

#include <xc.h>

#ifndef RTC_H
#define	RTC_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    #define uch unsigned char

    #define RTC_READ 0x80
    #define RTC_WRITE 0x00
    #define NULL -1
    #define AM 0
    #define PM 1

    #define RTC_SEC 0x01
    #define RTC_MINS 0x41
    #define RTC_HOURS 0x21
    #define RTC_DATE 0x61
    #define RTC_MONTH 0x11
    #define RTC_DAY 0x51
    #define RTC_YEAR 0x31
    #define RTC_CTRL 0x71
    #define RTC_TRICKLE_CHARGER 0x09
    #define RTC_CLK_BURST 0x7D

    #define RTC_ERROR 0xFF

    #define RST RB5
    #define SCLK RB0
    #define RTC_IO RB4
    
    typedef struct rtcTime {
        int secs;
        int mins;
        int hours;       
        int AMPM;
    } rtcTime;
    
    typedef struct rtcDate {
        int date;
        int month;
        int year;
        int day;        
    } rtcDate;
    
    typedef struct rtcDateTime {
        rtcTime time;
        rtcDate date;        
    } rtcDateTime;
    
    
    
    
    void clearWP();
    
    void writeByte(uch addr, uch data);
    
    uch convertSecs(int sec);
    uch convertMins(int mins);
    uch convertHours(int hours, int is24Hour);
    uch convertDate(int date, int month, int year);
    uch convertMonth(int month);
    uch convertDay(int day);
    uch convertYear(int year);
    
    int convertReadSecs(uch secs);
    int convertReadMins(uch mins);
    int convertReadHours(uch hours, int* AMPM);
    int convertReadDate(uch date);
    int convertReadMonth(uch month);
    int convertReadDay(uch day);
    int convertReadYear(uch year);
    
    uch readByte(uch addr);
    uch readCH();
    void startClock();
    void stopClock();


    void setDate(rtcDate date);
    void setTime(rtcTime time);
    void setDateTime(rtcDateTime datetime);
    void set24HourMode(int mode);
    
    void getDate(rtcDate* date);
    void getTime(rtcTime* time);
    void getTime24(rtcTime* time);
    void getTime12(rtcTime* time);
    
    void getDateTime(rtcDateTime* datetime);
    void convertHourFormat(rtcTime* time);
    
    uch reverseBits(uch number);
    
#ifdef	__cplusplus
}
#endif

#endif	/* RTC_H */

