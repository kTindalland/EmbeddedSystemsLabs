#include "LCDPanelInterface.h"
#include "LCDPanelDriver.h"    

void ILCDPanelSetCursor(char down, char along)
{
    LcdInit();
    SetCursorPos(down, along);
}

void ILCDPanelClear() {
    LcdInit();
    ClearCmd();    
}

void ILCDPanelWrite(char s[])
{
    LcdInit();
    WriteString(s);
}