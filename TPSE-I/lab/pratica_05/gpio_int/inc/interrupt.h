#ifndef interrupt_h
#define interrupt_h
#include "hw_types.h"
#include "bbb_regs.h"

extern bool flag_gpio;



void gpioIsrHandler(void);
void ISR_Handler(void);

void gpioSetup();
void butConfig();


#endif