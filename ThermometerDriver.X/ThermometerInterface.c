#include "ThermometerInterface.h"
#include "ThermometerDriver.h"

double IThermGetTemperature() {
    // Variable declarations.
    unsigned char msb;
    unsigned char lsb;
    
    unsigned char whole_number;
    unsigned char decimal_number;
    
    unsigned char sign;
    
    double result;
    
    // Measure current ambient temperature.
    ThermMeasureTemp();
    
    // Populate msb and lsb
    ThermGetTemp(&msb, &lsb);
    
    // Get the sign.
    sign = msb & 0xF8;
    
    // Get rid of the sign
    whole_number = msb & 0x07; 
    
    // Move along four
    whole_number <<= 4;
    
    // Move lsb four to the left
    decimal_number = lsb >> 4;
    
    whole_number = whole_number | decimal_number; // Complete whole number.
    result = result + whole_number;
    
    // Make decimal number just the decimal part.
    decimal_number = lsb & 0x0F;
    
    if (decimal_number & 0x08) result = result + 0.5;
    if (decimal_number & 0x04) result = result + 0.25;
    if (decimal_number & 0x02) result = result + 0.125;
    if (decimal_number & 0x01) result = result + 0.0625;
    
    if (sign) result = result * -1.0;
    
    return result;
}
