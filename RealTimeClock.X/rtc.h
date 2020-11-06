/* 
 * File:   rtc.h
 * Author: kaiti
 *
 * Created on 06 November 2020, 10:53
 */

#ifndef RTC_H
#define	RTC_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    #define uch unsigned char

    #define RTC_READ 0x80
    #define RTC_WRITE 0x00

    #define RTC_SEC = 0x01
    #define RTC_MINS = 0x41
    #define RTC_HOURS = 0x21
    #define RTC_DATE = 0x61
    #define RTC_MONTH = 0x11
    #define RTC_DAY = 0x51
    #define RTC_YEAR = 0x31
    #define RTC_CTRL = 0x71
    #define RTC_TRICKLE_CHARGER = 0x09
    #define RTC_CLK_BURST = 0x7D

    #define RTC_ERROR 0xFF
    
    
    void writeByte(uch addr, uch data);
    void writeBurst(uch sec, uch mins, uch hours, uch date, uch month, uch day, uch year);
    
    uch convertSecs(int sec);
    uch convertMins(int mins);
    uch convertHours(int hours);
    uch convertDate(int date);
    uch convertMonth(int month);
    uch convertDay(int day);
    uch convertYear(int year);
    
    int convertReadSecs(uch secs);
    int convertReadMins(uch mins);
    int convertReadHours(uch hours);
    int convertReadDate(uch date);
    int convertReadMonth(uch month);
    int convertReadDay(uch day);
    int convertReadYear(uch year);
    
    uch readByte(uch addr);
    


#ifdef	__cplusplus
}
#endif

#endif	/* RTC_H */

