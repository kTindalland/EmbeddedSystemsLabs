/*
 * File:   main.c
 * Author: kaiti
 *
 * Created on 14 December 2020, 10:55
 */


#include <xc.h>
#include "LCDPanelInterface.h"
#include "ThermometerDriver.h"
#include "ThermometerInterface.h"
#include "Delay.h"
#include "NumberConverter.h"


void main(void) {
    
    ILCDPanelClear();
    
    while(1) {
        
        ILCDPanelSetCursor(0, 0);
        ThermInit();
        ThermReset();
        
        ThermWriteByte(0xCC); // Ignore ROM matching
        ThermWriteByte(0x44); // Temp convert command.
        
        //Give convert some time.
        for (int i = 0; i < 300; i++) {
            
        }
        
        ThermReset();
        
        ThermWriteByte(0xCC); // Ignore ROM
        ThermWriteByte(0xBE); // Read temp

        
        unsigned char TLV = ThermReadByte();
        unsigned char THV = ThermReadByte();
        
        DQ_HIGH();
        
        unsigned char TZ = (TLV>>4) | (THV<<4) & 0x3F;
        unsigned char TX = TLV <<= 4;
        
        if (TZ > 100) TZ / 100;
        
        
        char mystring[10];
        char decimalstring[5];
        
        nbrcnvt_convert_integer(TZ, mystring);
        nbrcnvt_convert_integer(TX, decimalstring);
        
        ILCDPanelWrite(mystring);
        ILCDPanelWrite(".");
        ILCDPanelWrite(decimalstring);
        ILCDPanelWrite("     ");
        
//        double temperature = IThermGetTemperature();
//        char temperature_string[7];
//        
//        nbrcnvt_convert_double(temperature, temperature_string);
//        
//        ILCDPanelWrite(temperature_string);
        
        Delay(1000);
    }
    
    return;
}