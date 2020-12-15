#include "Delay.h"

void Delay(int n)
{
 for(int i=0;i<n;i++);
}

void therm_delay(char x, char y) {
    for (char i=0; i < x; i++) {
        for (char j = 0; j < y; j++);
    }    
}