#include "maths-utils.h"

double pow(double x, double y) {
    
    if (y == 0) return 1;
    
    double result = x;
    
    for (int i = abs(y) - 1; i > 0; i--) {
        result = result * x;
    }
    
    if (y < 0) {
        result = 1 / result;
    }
        
    
    return result;
}

double abs(double x) {
    
    if (x > 0) {
        return x;
    } 
    else {
        return x * -1;
    }
    
}
