#include "lcd.h"
#include "delay.h"
#include <stdio.h>
#include <string.h>

void lcd_init() {
    writecmd(0x0e);
    writecmd(0x1);
    writecmd(0x38);
    
    
    
}

void lcd_soft_init() {
    writecmd(0x0e);
    writecmd(0x38);
    setcursor(0,0);
}

void writechar(char x) {
    RS = 1; // will be data, not a command
    RW = 0; // Will be writing not reading
    PORTD = x; // Output data
    E = 0; // Low enable signal
    delay();
    E = 1;
      
}

void writecmd(char x) {
    RS = 0; // Will be command not data
    RW = 0; // Will be writing
    PORTD = x;
    E = 0;
    delay();
    E = 1;
}

void writestr(char *x) {
    int length = strlen(x);
    
    for (int i = 0; i < length; i++) {
        writechar(x[i]);
    }
}

void setcursor(int x, int y) {
    if (y < 0 || y > 1) { // Validate line number
        return;
    }
    
    if (x < 0 || x > 15) return; // validate column number
    
    int baseNumber = y == 0 ? 0x80 : 0xC0;
    
    writecmd(baseNumber + x);
    
}