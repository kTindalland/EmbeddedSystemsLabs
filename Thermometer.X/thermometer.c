#include "thermometer.h"

void set_pin_io(char val) {
    if (val) { // High
        TRISA = TRISA | 0x01;
    }
    else { // Low
        TRISA = ~(~TRISA | 0x01); // Make sure last bit is 0 for output.
    }
}

void set_pin(char val) {
    if (val) { // High
        PORTA = PORTA | 0x01;
    }
    else { // Low
        PORTA = ~(~PORTA | 0x01); // Make sure last bit is 0 for output.
    }
}

char get_pin() {
    char result = PORTA | 0x01;
        
    if (result && PORTA) { // Bit is high
        return 1;
    }
    else { // Bit is low
        return 0;
    }
    
}

int therm_init() {
    
    ADCON1 = 0x07; // Set Port A to general I/O
    set_pin_io(0); // Set pin low for output.
    
    set_pin(0);
    therm_delay(2, 70); // 503us
    set_pin_io(1);
    therm_delay(2, 8); // 70us
   
    char alive;
    alive = get_pin();
    
    // Wait till the end of the time slot
    therm_delay(2, 60);
    
    if (alive == 0) { // Alive
        return 1;
    }
    else { // Dead
        return 0;
    }
}

void skip_ROM() {
    
    write_byte(0xCC);
    
}

void write_bit(char wBit) {
    
    if (wBit) { // Write 1
        set_pin_io(0); // Set to write
        set_pin(0); // Set Low
        // Wait
        therm_delay(2, 8); // 70us
        set_pin_io(1); // Release pin
    }
    else { // Write 0
        set_pin_io(0); // Set to write
        set_pin(0); // Set Low
        // Wait 3us
        NOP();
        NOP();
        NOP();
        set_pin_io(1); // Release pin
        
        // Allow chip to sample
        therm_delay(2, 8); // 70us
    }
    
}

void write_byte(char byte) {
    
    char mask;
    
    for (mask = 0x80; mask != 0; mask >>= 1) {
        
        if (byte & mask) {
            write_bit(1);
        }
        else {
            write_bit(0);
        }
        
    }
    
}

void therm_delay(char x, char y) {
    // t = 7 + (3 * (y - 1) + 7) * (x - 1)
    char z;
    do {
        z = y;
        do {;} while (--z);
    } while (--x);
}