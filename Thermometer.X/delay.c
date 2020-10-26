/*
 * File:   delay.c
 * Author: 578004
 *
 * Created on 19 October 2020, 14:11
 */

#include "delay.h"

void delay() {
    
    for (int i = 0; i < 500; i++);
    
}

void delayBy(int amount) {
    for (int i = 0; i < amount; i++);
}
