/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/02/2017 20:05:55
 *       Revision:  none
 *       Compiler:  arm-none-eabi-gcc
 *
 *         Author:  Francisco Helder (FHC), helderhdw@gmail.com
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */

#include "uart.h"
#include "timer.h"
#include "gpio.h"
#include "interrupt.h"

#define INTERRUPT


bool flag_gpio;
bool flag_timer;


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main(void){
	
	/* Hardware setup */
	gpioInitModule(GPIO1);
	gpioInitModule(GPIO2);
	for(unsigned int i=21; i<=24; i++){
		gpioSetDirection(GPIO1, i, OUTPUT);
		gpioPinMuxSetup(GPIO1, i);
	}
	for(unsigned int i=8; i<=9; i++){
		gpioSetDirection(GPIO2, i, OUTPUT);
		gpioPinMuxSetup(GPIO2, i);
	}
	#ifdef INTERRUPT
		mirClear(95);
		mirClear(98);
		butConfig();
	#endif
	DMTimerSetUp();
	disableWdt();

	while(true){
		if(flag_gpio){
			uartPutString(UART0, "button press!\n\r", 16);
			gpioSetPinValue(GPIO1, 21, HIGH);
			delay(50);
			gpioSetPinValue(GPIO1, 22, HIGH);
			delay(50);
			gpioSetPinValue(GPIO1, 23, HIGH);
			delay(50);
			gpioSetPinValue(GPIO1, 24, HIGH);
			delay(50);

			gpioSetPinValue(GPIO1, 21, LOW);
			delay(50);
			gpioSetPinValue(GPIO1, 22, LOW);
			delay(50);
			gpioSetPinValue(GPIO1, 23, LOW);
			delay(50);
			gpioSetPinValue(GPIO1, 24, LOW);
			delay(50);



			gpioSetPinValue(GPIO2, 8, HIGH);
			gpioSetPinValue(GPIO2, 9, HIGH);
			delay(50);
			gpioSetPinValue(GPIO2, 8, LOW);
			gpioSetPinValue(GPIO2, 9, LOW);
			delay(50);

			gpioSetPinValue(GPIO2, 8, HIGH);
			delay(50);
			gpioSetPinValue(GPIO2, 8, LOW);
			delay(50);
			gpioSetPinValue(GPIO2, 9, HIGH);
			delay(50);
			gpioSetPinValue(GPIO2, 9, LOW);

			flag_gpio = false;
		}
		else{
			//uartPutString(UART0, "button not press!\n\r", 19);
			gpioSetPinValue(GPIO1, 21, HIGH);
			gpioSetPinValue(GPIO1, 22, HIGH);
			gpioSetPinValue(GPIO1, 23, HIGH);
			gpioSetPinValue(GPIO1, 24, HIGH);
			gpioSetPinValue(GPIO2, 8, HIGH);
			gpioSetPinValue(GPIO2, 9, HIGH);
			delay(500);
			gpioSetPinValue(GPIO1, 21, LOW);
			gpioSetPinValue(GPIO1, 22, LOW);
			gpioSetPinValue(GPIO1, 23, LOW);
			gpioSetPinValue(GPIO1, 24, LOW);
			gpioSetPinValue(GPIO2, 8, LOW);
			gpioSetPinValue(GPIO2, 9, LOW);
			delay(500);		
		}
	}

	return(0);
} /* ----------  end of function main  ---------- */


/**
 * COMPILE AND RUN [minicom]
 * setenv app "setenv autoload no; setenv serverip 10.4.1.1; setenv ipaddr 10.4.1.2; tftp 0x80000000 /tfptboot/appTimer.bin; go 0x80000000	"
 * run app
**/