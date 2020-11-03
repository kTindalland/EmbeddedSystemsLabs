#include "buttons.h"
#include <xc.h>

void initialiseButtons() {
        
        ADCON1 = 0x07;
        TRISA = 0xFF;
        TRISB = 0xFF;
        
}

int* checkButtons() {
    initialiseButtons();
    int result[8] = { 0 };

    unsigned int mask;
    int i = 0;

    for (mask = 1; mask != 16; mask <<= 1) {

        if (PORTB & mask) {
            result[i] = RIGHT_SIDE_HIGH;
        }
        i++;
    }
    
    for (mask = 1; mask != 16; mask <<= 1) {

        if (PORTA & mask) {
            result[i] = RIGHT_SIDE_HIGH;
        }
        i++;
    }
    
    return result;

}

void initialiseMatrixButtons() {
    TRISC = 0x0F;
}

int checkMatrixButton(int row, int col) {
    
}

void checkMatrixButtons(int result[4][4]) {
    initialiseMatrixButtons();
    
    // Check button states.
    for (int row = 0; row < 4; row++) {
        
        PORTC |= 0xF0; // Clear output
        PORTC &= ~(1 << (row + 4)); // Set row
        int inputs = ~(PORTC | 0xF0);
        
        for (int col = 0; col < 4; col++) {
            result[row][col] = 0;
            
            if (inputs & (1 << col)) {
                result[row][col] = 1;
            }
            
            
        }
        
        for (int i = 0; i < 5000; i++);
    }
    
}
