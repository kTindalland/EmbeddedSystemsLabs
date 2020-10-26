# 1 "//adir.hull.ac.uk/home/578/578004/Downloads/SampleLCD.X/delay.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files (x86)/Microchip/MPLABX/v5.35/packs/Microchip/PIC16Fxxx_DFP/1.2.33/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "//adir.hull.ac.uk/home/578/578004/Downloads/SampleLCD.X/delay.c" 2







# 1 "//adir.hull.ac.uk/home/578/578004/Downloads/SampleLCD.X/delay.h" 1



void delay();
void delayBy(int amount);
# 8 "//adir.hull.ac.uk/home/578/578004/Downloads/SampleLCD.X/delay.c" 2


void delay() {

    for (int i = 0; i < 500; i++);

}

void delayBy(int amount) {
    for (int i = 0; i < amount; i++);
}
