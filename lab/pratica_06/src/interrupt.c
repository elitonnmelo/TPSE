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
	HWREG(INTC_BASE + INTC_CONTROL) = 0x1;
}
void mirClear(unsigned int number) {
    unsigned int MIR_CLEAR = number / 32;
    unsigned int  VALUE = number % 32;
    switch (MIR_CLEAR) {
        case 0:
            HWREG(INTC_BASE + INTC_MIR_CLEAR0) |= (1<<VALUE);
            break;
        case 1:
            HWREG(INTC_BASE + INTC_MIR_CLEAR1) |= (1<<VALUE);
            break;
        case 2:
            HWREG(INTC_BASE + INTC_MIR_CLEAR2) |= (1<<VALUE);
            break;
        case 3:
            HWREG(INTC_BASE + INTC_MIR_CLEAR3) |= (1<<VALUE);
            break;
        default:
            break;
    }
}
