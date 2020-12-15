#include "ThermometerDriver.h"
#include "Delay.h"


void ThermInit() {
    ADCON1 = 0x07;
    TRISA = 0x00;
}

void ThermReset() {
    
    char presence = 1;
    
    while (presence) {
        
        DQ_LOW();
        
        therm_delay(1, 50);
        
        DQ_HIGH();
        
        therm_delay(2, 3);
        
        presence = DQ;
        therm_delay(2, 60);
    }
    
}

void ThermWriteByte(unsigned char value) {
    
    unsigned char i;
    unsigned char temp;
    
    for (i = 8; i > 0; i--) {
        
        temp = value & 0x01;
        
        DQ_LOW();
        
        NOP();
        NOP();
        
        if (temp == 1) DQ_HIGH();
        therm_delay(2, 3);
        
        DQ_HIGH();
        NOP();
        
        value = value >> 1;
        
    }
    
}

unsigned char ThermReadByte() {
    unsigned char i;
    unsigned char value = 0;
    static unsigned char j;
    
    for (i = 8; i > 0; i--) {
        
        value >>= 1;
        DQ_LOW();
        
        NOP();
        
        DQ_HIGH();
        
        NOP();
        
        j = DQ;
        if (j == 1) value |= 0x80;
        
        therm_delay(2, 3);
        
    }
    
    return value;
}

void ThermMeasureTemp() {
    
    ThermInit();
    ThermReset();
    
    ThermWriteByte(0xCC); // Ignore ROM
    ThermWriteByte(0x44); // Read ambient temp command.
    
    // Give it some time to work.
    for (int i = 0; i < 300; i++);    
}

void ThermGetTemp(unsigned char* msb, unsigned char* lsb) {
    
    ThermInit();
    ThermReset();
    
    ThermWriteByte(0xCC); // Ignore ROM
    ThermWriteByte(0xBE); // Read Temp
    
    *lsb = ThermReadByte();
    *msb = ThermReadByte();
    
    DQ_HIGH();
    
}

