#ifndef interrupt_h
#define interrupt_h

#include "hw_types.h"
#include "bbb_regs.h"

#define DMTimerWaitForWrite(reg)   \
            if(HWREG(DMTIMER_TSICR) & 0x4)\
            while((reg & HWREG(DMTIMER_TWPS)));

extern bool flag_timer;

extern bool flag_gpio;

void timerIrqHandle(void);
void ISRHandle(void);
void timerSetup(void);

void gpioIsrHandler(void);
void ISR_Handler(void);

void gpioSetup();
void butConfig();

#endif