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


typedef enum _pinNum{
	PIN1=1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6
}pinNum;

bool flag_gpio;


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
 *         Name:  delay
 *  Description:  
 * =====================================================================================
 */
void delay(unsigned int mSec){
    volatile unsigned int count;
    
	for(count=0; count<mSec; count++);

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
 *         Name:  readBut
 *  Description:  
 * =====================================================================================
 */
unsigned int readBut ( ){
	unsigned int temp;
	temp = HWREG(GPIO1_DATAIN)&0x10000000;
	
	return(temp);
}/* -----  end of function readBut  ----- */

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
	
	/* Hardware setup */
	gpioSetup();
	ledConfig();
	butConfig();
	disableWdt();

	putString("gpio Interrupt...\n\r",19);
	ledOff(PIN1);
	ledOff(PIN2);
	delay(10000000);

	while(true){
		if(flag_gpio){
			putString("button press!\n\r",15);
			ledOn(PIN1);
			ledOn(PIN4);
			delay(10000000);
			ledOff(PIN1);
			ledOff(PIN4);
			ledOn(PIN2);
			ledOn(PIN3);
			delay(10000000);
			ledOff(PIN2);
			ledOff(PIN3);
			delay(10000000);

			ledOn(PIN1);
			delay(10000000);
			ledOn(PIN2);
			delay(10000000);
			ledOn(PIN3);
			delay(10000000);
			ledOn(PIN4);
			delay(10000000);

			ledOff(PIN1);
			delay(10000000);
			ledOff(PIN2);
			delay(10000000);
			ledOff(PIN3);
			delay(10000000);
			ledOff(PIN4);
			delay(10000000);



			ledOn(PIN5);
			ledOn(PIN6);
			delay(10000000);
			ledOff(PIN5);
			ledOff(PIN6);
			delay(10000000);

			ledOn(PIN5);
			delay(10000000);
			ledOff(PIN5);
			delay(10000000);
			ledOn(PIN6);
			delay(10000000);
			ledOff(PIN6);
			delay(10000000);

			flag_gpio = false;
		}else{
			ledOn(PIN1);
			ledOn(PIN2);
			ledOn(PIN3);
			ledOn(PIN4);
			ledOn(PIN5);
			ledOn(PIN6);
			delay(10000000);
			ledOff(PIN1);
			ledOff(PIN2);
			ledOff(PIN3);
			ledOff(PIN4);
			ledOff(PIN5);
			ledOff(PIN6);
			delay(10000000);		
		}
	}

	return(0);
}

