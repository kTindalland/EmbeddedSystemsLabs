#ifndef __LCDPANELDRIVER
#define __LCDPANELDRIVER

#include <xc.h> 

#define rs RA1
#define rw RA2
#define e  RA3

void LcdInit();            
void WriteCmd(char x);
void WriteChar(char x);
int StringLength(char s[]);
void WriteString(char s[]);
void SetCursorPos(char line, char col);
void ClearCmd();


// Tested on Sim, Not Board

#endif