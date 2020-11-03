#include "thermometer.h"
#include "maths-utils.h"

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
    //therm_delay(2, 70); // 503us
    therm_delay(3, 40); // 503us - SIM
    set_pin_io(1);
    //therm_delay(2, 8); // 70us
    therm_delay(1, 10); // 70us - SIM
   
    char alive;
    alive = get_pin();
    
    // Wait till the end of the time slot
    //therm_delay(2, 60);
    therm_delay(3, 30); // SIM
    
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
        //therm_delay(2, 8); // 70us
        therm_delay(1, 10); // 70us - SIM
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
        //therm_delay(2, 8); // 70us
        therm_delay(1, 10); // 70us - SIM
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

char read_bit() {
    // Pull it down for 15 us
    for (int i = 0; i < 3; i++); // 12us
    NOP();
    NOP();
    NOP(); // The rest of the 3us
    
    
    return get_pin();
}

char read_byte() {
    char answer = read_bit();
    
    for (int i = 1; i < 8; i++) {
        answer <<= i;
        answer |= read_bit();
    }
    
    return answer;
}

void therm_delay(char x, char y) {
    // t = 7 + (3 * (y - 1) + 7) * (x - 1)
    char z;
    do {
        z = y;
        do {;} while (--z);
    } while (--x);
}

double therm_convert_number(int number) {
    
    double result = 0;
    
    for (int i = -4; i <= 6; i++) {
        int index = i + 4;
        
        int mask = 1 << index;
        
        if (number & mask != 0) {
            result += pow(2, i);
        }
    }
    
    if ((1 << 11) & number) {
        // Negative
        result *= -1;
    }
    
    result = 15.0;
    return result;
    
}