#include "thermometer.h"
#include "maths-utils.h"
#include <pic.h>

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
    alive = RA0;
    
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
    
    set_pin_io(0); // Set to write
    set_pin(0); // Set Low
    NOP();
    NOP();
    
    if (wBit) { // Write 1
        set_pin_io(1); // Release pin
    }
    
    // Allow chip to sample
    //therm_delay(2, 7); // 63us
    therm_delay(2, 3); // 63us - SIM
    
    set_pin_io(1); // Release pin
    NOP();
}

/*void write_byte(char byte) {
    
    char mask;
    
    for (mask = 0x80; mask != 0; mask >>= 1) {
        
        if (byte & mask) {
            write_bit(1);
        }
        else {
            write_bit(0);
        }
        
    }
    
}*/

void write_byte(unsigned char val)
{
 unsigned char i;
 unsigned char temp;
 for(i=8;i>0;i--)
 {
   temp=val&0x01;                             //shift the lowest bit                   
   set_pin_io(0);
   set_pin(0);
 //  NOP();                                                                              
 //  NOP();                                                                              
 //  NOP();                                                                              
  NOP();                                                                              
  NOP();                                     //pull high to low,produce write time    
//RB2=0;
   if(temp==1)  set_pin_io(1);                    //if write 1,pull high                   
   therm_delay(2,3);                                //delay 63us                             
   set_pin_io(1);                                                                          
  NOP();                                                                              
 //  NOP();                                                                              
   val=val>>1;                                //right shift a bit               
//RB2=1;       
  }
}

char read_bit() {
    // Pull it down for 15 us
    for (int i = 0; i < 3; i++); // 12us
    NOP();
    NOP();
    NOP(); // The rest of the 3us
    
    int pin_result = RA0;
    
    //therm_delay(2, 7); // 63us
    therm_delay(2, 3); // 63us - SIM
    
    return pin_result;
}

unsigned char read_byte(void)
{
 unsigned char i;
 unsigned char value=0;                                 //read temperature         
 static int j;
 for(i=8;i>0;i--)
 {
   value>>=1; 
   set_pin_io(0);
   set_pin(0);
//RB2=0;
  NOP();                               //6us              
   set_pin_io(1);                                // pull high  
//RB2=1;    
                                                       
   NOP();                                   //4us               
   j=RA0;                                                        
   if(j) value|=0x80;                       
//RB2=0;                    
   therm_delay(2,3);                              //63us     
//RB2=1;         
  }
  return(value);
}

/*char read_byte() {
    
    int result = 0;
    
    for (int i = 0; i < 8; i++) {
        result >>= 1;
        
        if (read_bit()) result |= 0x80;
    }
    
    return result;
}*/

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
        
        if ((number & mask) != 0) {
            result += pow(2, i);
        }
    }
    
    if ((1 << 11) & number) {
        // Negative
        result *= -1;
    }
    
    //return 15.0;
    return result;
    
}
