#include "timer.h"

#define DMTimerWaitForWrite(reg)   \
            if(HWREG(DMTIMER_TSICR) & 0x4)\
            while((reg & HWREG(DMTIMER_TWPS)));

// #define polling
#define DMTIMER_TCRR_HWREG      0x9009403C
#define DMTIMER_WRITE_TCRR      0x4804A002
#define DMTIMER_TCLR_HWREG      0x90094038
#define DMTIMER_TCLR_WRITE      0x4804A001


/*FUNCTION*-------------------------------------------------------
*
* Function Name : DMTimerCounterSet
* Comments      :Set/Write the Counter register with the counter value.
*
* \param   baseAdd       Base Address of the DMTimer Module Register.
* \param   counter       Count value for the timer.
*
* \return  None.
*
* \note    Value can be loaded into the counter register when the counter is 
*          stopped or when it is running.
*
*END*-----------------------------------------------------------*/
void DMTimerCounterSet(unsigned int counter) {
    /* Wait for previous write to complete */
    DMTimerWaitForWrite(DMTIMER_WRITE_POST_TCRR);

    /* Set the counter value */
    HWREG(DMTIMER_TCRR) = counter;
}

/*FUNCTION*-------------------------------------------------------
*
* Function Name : DMTimerCounterGet
* Comments      : Get/Read the counter value from the counter register.
*
* \param   baseAdd       Base Address of the DMTimer Module Register.
*
* \return  This API returns the count value present in the DMTimer Counter
*          register.
*
* \note:   Value can be read from the counter register when the counter is
*          stopped or when it is running.
*END*-----------------------------------------------------------*/
unsigned int DMTimerCounterGet(){
    /* Wait for previous write to complete */
    DMTimerWaitForWrite(DMTIMER_WRITE_TCRR);

    /* Read the counter value from TCRR */
    return (HWREG(DMTIMER_TCRR_HWREG));
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  timerEnable
 *  Description:  
 * =====================================================================================
 */
#ifdef polling
void timerEnable(){
    /* Wait for previous write to complete in TCLR */
	DMTimerWaitForWrite(0x1);

    /* Start the timer */
    HWREG(DMTIMER_TCLR) |= 0x1;
    
}/* -----  end of function timerEnable  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  timerEnable
 *  Description:  
 * =====================================================================================
 */
void timerDisable(){
    /* Wait for previous write to complete in TCLR */
	DMTimerWaitForWrite(0x1);

    /* Stop the timer */
    HWREG(DMTIMER_TCLR) &= ~(0x1);
}/* -----  end of function timerDisable  ----- */
#else 

void timerEnable(){
    /* Wait for previous write to complete in TCLR */
	DMTimerWaitForWrite(DMTIMER_TCLR_WRITE);

    /* Start the timer */
    HWREG(DMTIMER_TCLR_HWREG) |= 0x1;
    
}/* -----  end of function timerEnable  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  timerEnable
 *  Description:  
 * =====================================================================================
 */
void timerDisable(){
    /* Wait for previous write to complete in TCLR */
	DMTimerWaitForWrite(DMTIMER_TCLR_WRITE);

    /* Stop the timer */
    HWREG(DMTIMER_TCLR_HWREG) &= ~(0x1);
}/* -----  end of function timerDisable  ----- */

#endif


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  delay
 *  Description:  
 * =====================================================================================
 */
#ifdef polling
void delay(unsigned int mSec){

    unsigned int countVal = TIMER_OVERFLOW - (mSec * TIMER_1MS_COUNT);

   	/* Wait for previous write to complete */
	DMTimerWaitForWrite(0x2);

    /* Load the register with the re-load value */
	HWREG(DMTIMER_TCRR) = countVal;
	
	flag_timer = false;

    /* Enable the DMTimer interrupts */
	HWREG(DMTIMER_IRQENABLE_SET) = 0x2; 

    /* Start the DMTimer */
	timerEnable();

    while(flag_timer == false);

    /* Disable the DMTimer interrupts */
	HWREG(DMTIMER_IRQENABLE_CLR) = 0x2; 
}
#else
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  delay
 *  Description:  
 * =====================================================================================
 */
void delay(unsigned int mSec){
    while(mSec != 0){
        DMTimerCounterSet(SOC_DMTIMER_7_REGS);
        timerEnable();

        while(DMTimerCounterGet() < TIMER_1MS_COUNT);
        timerDisable();
        mSec--;
    }
}

#endif