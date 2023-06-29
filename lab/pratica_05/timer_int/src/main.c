/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  15/05/2018 14:32:47
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Francisco Helder (FHC), helderhdw@gmail.com
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */

#include "bbb_regs.h"
#include "hw_types.h"
#include "interrupt.h"
#include "timer.h"


/**
 * \brief   This macro will check for write POSTED status
 *
 * \param   reg          Register whose status has to be checked
 *
 *    'reg' can take the following values \n
 *    DMTIMER_WRITE_POST_TCLR - Timer Control register \n
 *    DMTIMER_WRITE_POST_TCRR - Timer Counter register \n
 *    DMTIMER_WRITE_POST_TLDR - Timer Load register \n
 *    DMTIMER_WRITE_POST_TTGR - Timer Trigger register \n
 *    DMTIMER_WRITE_POST_TMAR - Timer Match register \n
 *
 **/


typedef enum _pinNum{
	PIN1=1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6
}pinNum;


bool flag_timer;

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  disableWdt
 *  Description:  
 * =====================================================================================
 */
void disableWdt(void){
	HWREG(WDT_WSPR) = 0xAAAA;
	while((HWREG(WDT_WWPS) & (1<<4)));
	
	HWREG(WDT_WSPR) = 0x5555;
	while((HWREG(WDT_WWPS) & (1<<4)));
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  putCh
 *  Description:  
 * =====================================================================================
 */
void putCh(char c){
	while(!(HWREG(UART0_LSR) & (1<<5)));

	HWREG(UART0_THR) = c;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  getCh
 *  Description:  
 * =====================================================================================
 */
char getCh(){
	while(!(HWREG(UART0_LSR) & (1<<0)));

	return(HWREG(UART0_RHR));
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  putString
 *  Description:  
 * =====================================================================================
 */
int putString(char *str, unsigned int length){
	for(int i = 0; i < length; i++){
    	putCh(str[i]);
	}
	return(length);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  getString
 *  Description:  
 * =====================================================================================
 */
int getString(char *buf, unsigned int length){
	for(int i = 0; i < length; i ++){
    	buf[i] = getCh();
   	}
	return(length);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  gpioSetup
 *  Description:  
 * =====================================================================================
 */
// void gpioSetup(){
//   /* set clock for GPIO1, TRM 8.1.12.1.31 */
//   HWREG(CM_PER_GPIO1_CLKCTRL) = 0x40002;
// }

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledConfig
 *  Description:  
 * =====================================================================================
 */
void ledConfig(){
    /*  configure pin mux for output GPIO */
	HWREG(CM_PER_GPMCA5_REGS) |= 0x7;
    HWREG(CM_PER_GPMCA6_REGS) |= 0x7;
    HWREG(CM_PER_GPMCA7_REGS) |= 0x7;
    HWREG(CM_PER_GPMCA8_REGS) |= 0x7;

	HWREG(CM_CONF_LCD_DATA2) |= 0x7;
    HWREG(CM_CONF_LCD_DATA3) |= 0x7;

    /* clear pin 23 and 24 for output, leds USR3 and USR4, TRM 25.3.4.3 */
    HWREG(GPIO1_OE) &= ~(1<<21);
    HWREG(GPIO1_OE) &= ~(1<<22);
	HWREG(GPIO1_OE) &= ~(1<<23);
    HWREG(GPIO1_OE) &= ~(1<<24);

	HWREG(GPIO2_OE) &= ~(1<<8);
    HWREG(GPIO2_OE) &= ~(1<<9);

}/* -----  end of function ledConfig  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledOff
 *  Description:  
 * =====================================================================================
 */
void ledOff(pinNum pin){
	switch (pin) {
		case PIN1:
			HWREG(GPIO1_CLEARDATAOUT) |= (1<<21);
		break;
		case PIN2:	
			HWREG(GPIO1_CLEARDATAOUT) |= (1<<22);
		break;
		case PIN3:
			HWREG(GPIO1_CLEARDATAOUT) |= (1<<23);
			break;
		case PIN4:
			HWREG(GPIO1_CLEARDATAOUT) |= (1<<24);
			break;
		case PIN5:
			HWREG(GPIO2_CLEARDATAOUT) |= (1<<8);
			break;
		case PIN6:
			HWREG(GPIO2_CLEARDATAOUT) |= (1<<9);
			break;
		default:
		break;
	}/* -----  end switch  ----- */
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledOn
 *  Description:  
 * =====================================================================================
 */
void ledOn(pinNum pin){
	switch (pin) {
		case PIN1:
			HWREG(GPIO1_SETDATAOUT) |= (1<<21);
		break;
		case PIN2:
			HWREG(GPIO1_SETDATAOUT) |= (1<<22);
		break;
		case PIN3:
			HWREG(GPIO1_SETDATAOUT) |= (1<<23);
			break;
		case PIN4:
			HWREG(GPIO1_SETDATAOUT) |= (1<<24);
			break;
		case PIN5:
			HWREG(GPIO2_SETDATAOUT) |= (1<<8);
			break;
		case PIN6:
			HWREG(GPIO2_SETDATAOUT) |= (1<<9);
			break;
		default:
		break;
	}/* -----  end switch  ----- */
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main(void){
	char count=9;
	
	/* Hardware setup */
	gpioSetup();
	ledConfig();
	timerSetup();
	butConfig();
	disableWdt();

	// putString("Digite P para polling ou I para interrupcao: ", 45);
	// char value[2];
	// getString(value, 2);

	// if ( value[0] == "I" || value[0] == "i") {
	// 	putString("Inicializando via interrupcao", 29);
	// 	while(count){
	// 		putString("Dentro do while interrupcao", 28);
	// 		putCh(0x30+count);
	// 		putCh(' ');
	// 		delay(1000);
	// 		count--;
	// 	}
	// }
	// else if (value[0] == "P" || value[0] == "p") {
	// 	putString("Inicializando via polling", 25);
	// 	while(count){
	// 		putString("Dentro do while polling", 14);
	// 		putCh(0x30+count);
	// 		putCh(' ');
	// 		Delay(1000);
	// 		count--;
	// 	}
	// }
	// else {
	// 	putString("Fail: invalid argument", 22);
	// }

	// putString("Timer Interrupt: ",17);
	// while(count){
	// 	putCh(0x30+count);
	// 	putCh(' ');
	// 	delay(1000);
	// 	//count--;

	// 	ledOn(PIN1);
	// 	ledOn(PIN2);
	// 	ledOn(PIN3);
	// 	ledOn(PIN4);
	// 	ledOn(PIN5);
	// 	ledOn(PIN6);
	// 	putString("HIGH\n\r", 6);
	// 	delay(1000);
	// 	ledOff(PIN1);
	// 	ledOff(PIN2);
	// 	ledOff(PIN3);
	// 	ledOff(PIN4);
	// 	ledOff(PIN5);
	// 	ledOff(PIN6);
	// 	putString("LOW\n\r", 5);
	// 	delay(1000);
	// 	count--;
		
	// }

	while(true){
		if(flag_gpio){
			putString("button press!\n\r",15);
			ledOn(PIN1);
			ledOn(PIN4);
			delay(1000);
			ledOff(PIN1);
			ledOff(PIN4);
			ledOn(PIN2);
			ledOn(PIN3);
			delay(1000);
			ledOff(PIN2);
			ledOff(PIN3);
			delay(1000);

			ledOn(PIN1);
			delay(1000);
			ledOn(PIN2);
			delay(1000);
			ledOn(PIN3);
			delay(1000);
			ledOn(PIN4);
			delay(1000);

			ledOff(PIN1);
			delay(1000);
			ledOff(PIN2);
			delay(1000);
			ledOff(PIN3);
			delay(1000);
			ledOff(PIN4);
			delay(1000);



			ledOn(PIN5);
			ledOn(PIN6);
			delay(1000);
			ledOff(PIN5);
			ledOff(PIN6);
			delay(1000);

			ledOn(PIN5);
			delay(1000);
			ledOff(PIN5);
			delay(1000);
			ledOn(PIN6);
			delay(1000);
			ledOff(PIN6);
			delay(1000);

			flag_gpio = false;
		}else{
			ledOn(PIN1);
			ledOn(PIN2);
			ledOn(PIN3);
			ledOn(PIN4);
			ledOn(PIN5);
			ledOn(PIN6);
			delay(1000);
			ledOff(PIN1);
			ledOff(PIN2);
			ledOff(PIN3);
			ledOff(PIN4);
			ledOff(PIN5);
			ledOff(PIN6);
			delay(1000);		
		}
	}

	
	putString("...OK",5);

	return(0);
}
/**
 * COMPILE AND RUN [minicom]
 * setenv app "setenv autoload no; setenv serverip 10.4.1.1; setenv ipaddr 10.4.1.2; tftp 0x80000000 /tfptboot/appTimer.bin; go 0x80000000;"
 * run app
**/





