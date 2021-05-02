#include <carTL.h>
#include <fsm.h>
#include <gptm.h>
#include "uart.h"
# include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "tm4c123gh6pm.h"
#include <stdbool.h>
#include "driverlib/timer.h"
# include "driverlib/interrupt.h"
#include "led.h"

// Car Traffic Light Initialization
void CarTL_Init(void)
{
    //
    //Enable clock for ports and check whether peripheral is ready
    //
    SysCtlPeripheralEnable(LED_CNS_GPIO_PERIPH);
    SysCtlPeripheralEnable(LED_CEW_GPIO_PERIPH);
    while(!SysCtlPeripheralReady(LED_CNS_GPIO_PERIPH));
    while(!SysCtlPeripheralReady(LED_CEW_GPIO_PERIPH));

    //
    //Set Car Traffic Light LED pins as output
    //
    GPIOPinTypeGPIOOutput(LED_CNS_PORT_BASE,LED_CNS_ALL);
    GPIOPinTypeGPIOOutput(LED_CEW_PORT_BASE,LED_CEW_ALL);

    //
    //Initialize the Car Traffic Light Timer
    //
    GPTM_CarTL_Init();
    GPTM_CarTL_IntRegister(CarTL_ISR);
    GPTM_CarTL_IntEnable();

    //
    //Initialize the first carTL state
    //
    GPIOPinWrite(LED_CNS_PORT_BASE, LED_CNS_ALL,FSM_CarTL[FSM_Car_State].Out );
    GPIOPinWrite(LED_CEW_PORT_BASE, LED_CEW_ALL,FSM_CarTL[FSM_Car_State].Out);
    GPTM_CarTL_SetPeriodInMS(FSM_CarTL[FSM_Car_State].Time);
    GPTM_CarTL_Enable();

    //
    //Initialize the system state and send it
    //with UART
    FSM_Sys_State=FSM_SYS_CAR_NS;
    UART_PrintSystemState(FSM_Sys_State,FSM_Car_State);
}


//Car Traffic Light Interrupt Service Routine
void CarTL_ISR(void)
{
    //Disable the timer
    GPTM_CarTL_Disable();
    GPTM_CarTL_IntClear();

    FSM_Car_State=FSM_CarTL[FSM_Car_State].Next;
    GPTM_CarTL_SetPeriodInMS(FSM_CarTL[FSM_Car_State].Time);

    FSM_Sys_State=FSM_CarTL[FSM_Car_State].SysState;
    UART_PrintSystemState(FSM_Sys_State,FSM_Car_State);

    GPIOPinWrite(LED_CNS_PORT_BASE, LED_CNS_ALL,FSM_CarTL[FSM_Car_State].Out );
    GPIOPinWrite(LED_CEW_PORT_BASE, LED_CEW_ALL,FSM_CarTL[FSM_Car_State].Out);

    GPTM_CarTL_Enable();

}

