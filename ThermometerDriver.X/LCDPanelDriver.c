#include "LCDPanelDriver.h"
#include "Delay.h"
#include <xc.h> 

//begin config
#pragma config FOSC = HS    // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF   // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = ON   // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF  // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF    // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
//end config

#define rs RA1
#define rw RA2
#define e  RA3

void ClearCmd()
{
    WriteCmd(0x1); 
}

void LcdInit()
{
    ADCON1=0x07;               
    TRISA=0x00;             
    TRISD=0x00;
    
    WriteCmd(0x0C); //display on
    WriteCmd(0x38); //8 bits 2 lines 5*7 mode
}

void WriteCmd(char x)
{
 rs=0;      //Command, not data
 rw=0;      //Write, not read
 e=0;       //Pull low enable signal.
 e=1;       //Pull high to build the rising edge
 PORTD=x;     
 Delay(2000);
 e=0;
}

void WriteChar(char x)
{
    rs=1;       //Data, not command
    rw=0;      //Write, not read
    e=0;       //Pull low enable signal.
    e=1;       //Pull high to build the rising edge
    PORTD=x;     
    Delay(1000);
    e=0;
}

int StringLength(char s[]) {
   int c = 0;
   while (s[c] != '\0') // While String Is Not Null
      c++;
   
   return c;
}

void WriteString(char s[])
{ 
    for (int i=0; i<StringLength(s); i++)
    {
        WriteChar(s[i]);
    }
}

void SetCursorPos(char line, char col){
    
    char basePos = line ? 0xC0 : 0x80;
    WriteCmd(basePos + col);
}

void ExampleLcd() // Example of Driver Use
{
    ClearCmd();
    LcdInit();
    while(1)
    {
        SetCursorPos(0,3);
        WriteString("Hello");
        SetCursorPos(1,5);
        WriteString("World!");
    }
}

// Tested on Sim, Not Board