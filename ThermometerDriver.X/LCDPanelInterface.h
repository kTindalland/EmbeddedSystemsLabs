#ifndef __LCDPANELINTERFACE
#define __LCDPANELINTERFACE

void ILCDPanelSetCursor(char down, char along);
void ILCDPanelWrite(char s[]);
void ILCDPanelClear();

#endif