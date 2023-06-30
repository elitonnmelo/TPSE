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
	//uartPutString(UART0,"Interupt on!",13);
	switch(irq_number){
		case 95:
			timerIrqHandler();
			uartPutString(UART0,"Interupt timer on!\n\r",21);
			break;
		case 98:
			gpioIsrHandler();
			uartPutString(UART0,"Interupt  button on!\n\r",23);
			break;
	}
	// if(irq_number == 95)
	// 	timerIrqHandler();
    // else if(irq_number == 98)
	// 	gpioIsrHandler();
	/* Reconhece a IRQ */
	HWREG(INTC_BASE + INTC_CONTROL) = 0x1;
}
void mirClear(void) {
	
}
