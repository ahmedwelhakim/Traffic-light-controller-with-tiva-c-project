#include <gptm.h>
# include <stdint.h>
# include "inc/hw_memmap.h"
# include "driverlib/sysctl.h"
# include "tm4c123gh6pm.h"
# include "driverlib/timer.h"
# include "driverlib/interrupt.h"
#include <stdbool.h>
//*********************************************************************************
//*********************************************************************************
// GPTM Car Traffic Light APIs
//*********************************************************************************
//*********************************************************************************
void GPTM_CarTL_Init(void)
{   //
    //Timer 0 initialization for car traffic light
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);//Enable clock for Timer0
    while( !SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0));//Check whether ready

    TimerDisable(TIMER0_BASE,TIMER_BOTH); //First disable the timer to configure

    // Configure the timer0 As timerA periodic Count down
    TimerConfigure(TIMER0_BASE,TIMER_CFG_PERIODIC_UP);
    TimerIntClear(TIMER0_BASE,TIMER_TIMA_TIMEOUT ); // Clear the interrupt flag
    TimerControlStall(TIMER0_BASE, TIMER_BOTH, true);

//    //Set priority lower than ped timer and btns
//    IntPrioritySet(INT_TIMER0A, 0x20);
}
void GPTM_CarTL_SetPeriodInMS(uint32_t tms)
{
    TimerLoadSet(TIMER0_BASE, TIMER_BOTH, tms*16000 -1);
}
void GPTM_CarTL_Disable(void)
{
    TimerDisable(TIMER0_BASE,TIMER_BOTH);
}
void GPTM_CarTL_Enable(void)
{
    TimerEnable(TIMER0_BASE,TIMER_BOTH);
}
void GPTM_CarTL_IntEnable(void)
{
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
}
void GPTM_CarTL_IntDisable(void)
{
    TimerIntDisable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
}
void GPTM_CarTL_IntClear(void)
{
    TimerIntClear(TIMER0_BASE,TIMER_TIMA_TIMEOUT );
}
void GPTM_CarTL_IntRegister(void(*pfnHandeler)(void))
{
    TimerIntRegister(TIMER0_BASE, TIMER_A, pfnHandeler);
}


//*********************************************************************************
//*********************************************************************************
// GPTM Pedestrian Traffic Light APIs
//*********************************************************************************
//*********************************************************************************


void GPTM_PedTL_Init(void)
{   //
    //Timer 1 initialization for car traffic light
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);//Enable clock for Timer1
    while( !SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER1));//Check whether ready

    TimerDisable(TIMER1_BASE,TIMER_BOTH); //First disable the timer to configure

    // Configure the timer1 As timerA periodic Count down
    TimerConfigure(TIMER1_BASE,TIMER_CFG_PERIODIC_UP);
    TimerIntClear(TIMER1_BASE,TIMER_TIMA_TIMEOUT ); // Clear the interrupt flag
    TimerControlStall(TIMER1_BASE, TIMER_BOTH, true);

//    //Set highest priority
//    IntPrioritySet(INT_TIMER1A, 0);
}
void GPTM_PedTL_SetPeriodInMS(uint32_t tms)
{
    TimerLoadSet(TIMER1_BASE, TIMER_BOTH, tms*16000 -1);
}
void GPTM_PedTL_Disable(void)
{
    TimerDisable(TIMER1_BASE,TIMER_BOTH);
}
void GPTM_PedTL_Enable(void)
{
    TimerEnable(TIMER1_BASE,TIMER_BOTH);
}
void GPTM_PedTL_IntEnable(void)
{
    TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
}
void GPTM_PedTL_IntDisable(void)
{
    TimerIntDisable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
}
void GPTM_PedTL_IntClear(void)
{
    TimerIntClear(TIMER1_BASE,TIMER_TIMA_TIMEOUT );
}
void GPTM_PedTL_IntRegister(void(*pfnHandeler)(void))
{
    TimerIntRegister(TIMER1_BASE, TIMER_A, pfnHandeler);
}


