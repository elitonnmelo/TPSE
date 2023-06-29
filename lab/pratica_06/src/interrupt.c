#include "interrupt.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ISR_Handler
 *  Description:  
 * =====================================================================================
 */

void ISR_Handler(void){
	/* Verifica se é interrupção do RTC */
	unsigned int irq_number = HWREG(INTC_BASE + INTC_SIR_IRQ) & 0x7f;
	uartP
	switch(irq_number){
		case 95:
			timerIrqHandler();
			break;
		case 98:
			gpioIsrHandler();
			break;
	}
	// if(irq_number == 95)
	// 	timerIrqHandler();
    // else if(irq_number == 98)
	// 	gpioIsrHandler();
	/* Reconhece a IRQ */
	HWREG(INTC_BASE + INTC_CONTROL) = 0x1;
}
