/* 
 * File:   lcd.h
 * Author: 578004
 *
 * Created on 19 October 2020, 14:29
 */
#include <xc.h>

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    #define RS RA1
    #define RW RA2
    #define E RA3

    void lcd_init();
    void lcd_soft_init();
    void writecmd(char x);
    void writechar(char x);
    void writestr(char *x);
    void setcursor(int x, int y);


#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

