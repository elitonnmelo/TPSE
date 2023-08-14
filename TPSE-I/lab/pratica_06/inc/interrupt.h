#ifndef interrupt_h
#define interrupt_h

#include "soc_AM335x.h"
#include "hw_types.h"  
#include "gpio.h"
#include "timer.h"
#include "uart.h"

#define INTC_BASE       						0x48200000
#define INTC_SIR_IRQ    						0x40
#define INTC_CONTROL    						0x48
#define INTC_ILR        						0x100
#define INTC_MIR_CLEAR0 						0x88
#define INTC_MIR_CLEAR1 						0xA8
#define INTC_MIR_CLEAR2 						0xC8
#define INTC_MIR_CLEAR3 						0xE8
#define INTC_SYSCONFIG							0x10
#define INTC_SYSSTATUS							0x14
#define INTC_THRESHOLD							0x68

void ISR_Handler(void);
void mirClear(unsigned int);

#endif