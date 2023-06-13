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


#define TIME													1000000
#define TOGGLE          										(0x01u)
#define WDT1													0x44E35000

#define WDT_WSPR												0x48
#define WDT_WWPS												0x34

#define CM_PER_GPIO1											0xAC
#define CM_PER_GPIO1_CLKCTRL_MODULEMODE_ENABLE   				(0x2u)
#define CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK   			(0x00040000u)

#define CM_PER_GPIO2											0xB0
#define CM_PER_GPIO2_CLKCTRL_MODULEMODE_ENABLE   				(0x2u)
#define CM_PER_GPIO2_CLKCTRL_OPTFCLKEN_GPIO_2_GDBCLK   			(0x00040000u)

#define CM_conf_lcd_data2										0x8A8
#define CM_conf_lcd_data3										0x8AC

#define CM_conf_gpmc_ben1      	 								0x0878
#define CM_conf_gpmc_a5         								0x0854
#define CM_conf_gpmc_a6         								0x0818
#define CM_conf_gpmc_a7         								0x081C
#define CM_conf_gpmc_a8         								0x0820
#define CM_conf_gpmc_ad12         								0x0830




#define GPIO_OE                 								0x134
#define GPIO_CLEARDATAOUT       								0x190
#define GPIO_SETDATAOUT         								0x194


unsigned int flagBlink;
unsigned int flagBlink2;
unsigned int flagBlink3;
unsigned int flagBlink4;
unsigned int flagBlink5;
unsigned int flagBlink6;

/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/
static void ledInit();
static void ledInit2();
static void ledToggle();
static void ledToggle2();
static void ledToggle3();
static void ledToggle4();
static void ledToggle5();
static void ledToggle6();

/*****************************************************************************
**                INTERNAL MACRO DEFINITIONS
*****************************************************************************/

/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/
	
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main(void){
	// unsigned char count=9; 

	// /*-----------------------------------------------------------------------------
	//  *  initialize UART modules
	//  *-----------------------------------------------------------------------------*/
	// uartInitModule(UART0, 115200, STOP1, PARITY_NONE, FLOW_OFF);
	
	// /*-----------------------------------------------------------------------------
	//  *  initialize TIMER modules
	//  *-----------------------------------------------------------------------------*/
    // DMTimerSetUp();

	// //uartPutString(UART0,"GPIO INPUT Initialized",23);	
  	// uartPutString(UART0,"Time: ",7);
  	// while(count){
	// 	uartPutC(UART0,0x30+count);
	// 	Delay(1000);
	// 	count--;
	// 	uartPutC(UART0,' ');
	// }
	// uartPutString(UART0,"OK...",5);

	HWREG( WDT1 + WDT_WSPR ) = 0xAAAA;

	while (HWREG((WDT1 + WDT_WWPS)  & (1<<4)) != 0){

	}

	HWREG( WDT1 + WDT_WSPR) =  0x5555;

	while (HWREG((WDT1 + WDT_WWPS)  & (1<<4)) != 0){

	}
	

	flagBlink=0;
	flagBlink2=0;	//init flag
	flagBlink3=0;
	flagBlink4=0;
	flagBlink5=0;
	flagBlink6=0;
	
  	
	/* Configure the green LED control pin. */
  	ledInit();
	ledInit2();
	DMTimerSetUp();
  
  	while (1){
    	/* Change the state of the green LED. */

		// Pinos da beaglebone
    	ledToggle();
		ledToggle4();
		Delay(100);
		ledToggle();
		ledToggle4();
		Delay(100);
		ledToggle2();
		ledToggle3();
		Delay(100);
		ledToggle2();
		ledToggle3();
		Delay(100);

		// Pinos fora da Baglebone
		// Piscar os dois leds juntos
		ledToggle5();
		ledToggle6();
		Delay(100);
		ledToggle5();
		ledToggle6();
		
		// Delay: 100 ms
		// Frequencia: 1 Hz
		// Periodo: 10 delay
		
		/*
		Formula:   	delay = 1000/ (10 * frequencia)
					frequencia(Hz): 1 / periodo (segundos)
		*/
		
	}

	return(0);
} /* ----------  end of function main  ---------- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledInit
 *  Description:  
 * =====================================================================================
 */
void ledInit( ){
	
	unsigned int val_temp; 
	
	/*-----------------------------------------------------------------------------
	 *  configure clock GPIO in clock module
	 *-----------------------------------------------------------------------------*/
	HWREG(SOC_CM_PER_REGS+CM_PER_GPIO1) |= CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK | CM_PER_GPIO1_CLKCTRL_MODULEMODE_ENABLE;
	
	/*-----------------------------------------------------------------------------
	 * configure mux pin in control module
	 *-----------------------------------------------------------------------------*/
 	HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a5) |= 7;
	HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a6) |= 7;
	HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a7) |= 7;
	HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a8) |= 7;
 
	/*-----------------------------------------------------------------------------
	 *  set pin direction 
	 *-----------------------------------------------------------------------------*/
	val_temp = HWREG(SOC_GPIO_1_REGS+GPIO_OE);
	val_temp &= ~(1<<21);
	val_temp &= ~(1<<22);
	val_temp &= ~(1<<23);
	val_temp &= ~(1<<24);

	HWREG(SOC_GPIO_1_REGS+GPIO_OE) = val_temp;
	
}/* -----  end of function ledInit  ----- */

void ledInit2(){
	unsigned int val_temp;

	/*-----------------------------------------------------------------------------
	 *  configure clock GPIO in clock module
	 *-----------------------------------------------------------------------------*/

	HWREG(SOC_CM_PER_REGS + CM_PER_GPIO2) |= CM_PER_GPIO2_CLKCTRL_OPTFCLKEN_GPIO_2_GDBCLK | CM_PER_GPIO2_CLKCTRL_MODULEMODE_ENABLE;

	/*-----------------------------------------------------------------------------
	 * configure mux pin in control module
	 *-----------------------------------------------------------------------------*/

	HWREG(SOC_CONTROL_REGS+CM_conf_lcd_data2) |= 7;
	HWREG(SOC_CONTROL_REGS+CM_conf_lcd_data3) |= 7;

	/*-----------------------------------------------------------------------------
	 *  set pin direction 
	 *-----------------------------------------------------------------------------*/
	val_temp = HWREG(SOC_GPIO_2_REGS+GPIO_OE);
	val_temp &= ~(1<<8);
	val_temp &= ~(1<<9);
	HWREG(SOC_GPIO_2_REGS+GPIO_OE) = val_temp;
	
} /* -----  end of function ledInit2  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledToggle
 *  Description:  
 * =====================================================================================
 */
void ledToggle(){
		
		flagBlink ^= TOGGLE;

		if(flagBlink){
			HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = 1<<21;
		}else{
			HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) = 1<<21;
		}
}/* -----  end of function ledToggle  ----- */

void ledToggle2(){

		flagBlink2^= TOGGLE;

		if(flagBlink2){
			HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = 1<<22;
		}else{
			HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) = 1<<22;
		}
}/* -----  end of function ledToggle  ----- */
void ledToggle3(){

		flagBlink3^= TOGGLE;

		if(flagBlink3){
			HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = 1<<23;
		}else{
			HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) = 1<<23;
		}
}/* -----  end of function ledToggle  ----- */
void ledToggle4(){

		flagBlink4^= TOGGLE;

		if(flagBlink4){
			HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = 1<<24;
		}else{
			HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) = 1<<24;
		}
}/* -----  end of function ledToggle  ----- */
void ledToggle5(){

		flagBlink5^= TOGGLE;

		if(flagBlink5){
			HWREG(SOC_GPIO_2_REGS+GPIO_SETDATAOUT) = 1<<8;
		}else{
			HWREG(SOC_GPIO_2_REGS+GPIO_CLEARDATAOUT) = 1<<8;
		}
}/* -----  end of function ledToggle  ----- */
void ledToggle6(){

		flagBlink6 ^= TOGGLE;

		if(flagBlink6){
			HWREG(SOC_GPIO_2_REGS+GPIO_SETDATAOUT) = 1<<9;
		}else{
			HWREG(SOC_GPIO_2_REGS+GPIO_CLEARDATAOUT) = 1<<9;
		}
}/* -----  end of function ledToggle  ----- */

