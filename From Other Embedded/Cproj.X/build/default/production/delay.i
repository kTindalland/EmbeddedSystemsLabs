# 1 "delay.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "H:/Program Files (x86)/Microchip/MPLABX/v5.35/packs/Microchip/PIC16Fxxx_DFP/1.2.33/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "delay.c" 2
# 1 "./delay.h" 1
# 18 "./delay.h"
    void delay();
# 1 "delay.c" 2


void delay() {
    int i;
    for(i=0x500;i--;) ;
}
