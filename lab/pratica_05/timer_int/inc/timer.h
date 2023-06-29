#ifndef timer_h
#define timer_h
#include "hw_types.h"
#include "bbb_regs.h"
#define DMTIMER_TWPS_W_PEND_TCRR   (0x00000002u)
#define DMTIMER_WRITE_POST_TCRR              (DMTIMER_TWPS_W_PEND_TCRR)

extern bool flag_timer;

void timerEnable();
void timerDisable();
void delay(unsigned int);
void DMTimerCounterSet(unsigned int);
unsigned int DMTimerCounterGet();

#endif