# include "pedTL.h"
#include <fsm.h>
#include <gptm.h>
# include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "tm4c123gh6pm.h"
#include <stdbool.h>
#include "driverlib/timer.h"
# include "driverlib/interrupt.h"
#include "led.h"
# include "btn.h"
# include "uart.h"
 //Pedestrian Traffic Light Initialization

void PedTL_Init(void)
{


    //
    //Enable clock for ports and check whether peripheral is ready
    //
    SysCtlPeripheralEnable(LED_PNS_GPIO_PERIPH);
    SysCtlPeripheralEnable(LED_PEW_GPIO_PERIPH);
    while(!SysCtlPeripheralReady(LED_PNS_GPIO_PERIPH));
    while(!SysCtlPeripheralReady(LED_PEW_GPIO_PERIPH));

    //
    //Set Pedestrian Traffic Light LED pins as output
    //
    GPIOPinTypeGPIOOutput(LED_PNS_PORT_BASE,LED_PNS_ALL);
    GPIOPinTypeGPIOOutput(LED_PEW_PORT_BASE,LED_PEW_ALL);

    //
    //Initialize the Pedestrian Traffic Light Timer
    //
    GPTM_PedTL_Init();
    GPTM_PedTL_IntRegister(PedTL_ISR1);
    GPTM_PedTL_IntEnable();

    //
    //Write the pedTL to initial condition
    //
    GPIOPinWrite(LED_PNS_PORT_BASE, LED_PNS_ALL, LED_PNS_RED);
    GPIOPinWrite(LED_PEW_PORT_BASE, LED_PEW_ALL, LED_PEW_RED);

    //
    //Initialize Buttons
    //
    Btn_Init();

}


//Car Traffic Light Interrupt Service Routine when gptm pedTL timer Time out first time
void PedTL_ISR1(void)
{
    //Disable the timer and Clear Interrupt
    GPTM_PedTL_Disable();
    GPTM_PedTL_IntClear();
    GPTM_PedTL_SetPeriodInMS(1000); // 1 seconds

    //Fsm state change
    FSM_Ped_State=FSM_PedTL[FSM_Ped_State].Next;

    //Change The System State and send it UART
    if(FSM_Car_State==FSM_CAR_GO_NS|FSM_CAR_WAIT_NS|FSM_CAR_STOP_NS)
    {
        FSM_Sys_State=FSM_SYS_CAR_NS;
    }
    else
    {
    	FSM_Sys_State=FSM_SYS_CAR_EW;
    }
    UART_PrintSystemState(FSM_Sys_State,FSM_Car_State);

    //Write All traffic Light LEDs
    GPIOPinWrite(LED_CNS_PORT_BASE, LED_CNS_ALL,FSM_PedTL[FSM_Ped_State].CarOut[FSM_Car_State]);
    GPIOPinWrite(LED_CEW_PORT_BASE, LED_CEW_ALL,FSM_PedTL[FSM_Ped_State].CarOut[FSM_Car_State]);

    GPIOPinWrite(LED_PNS_PORT_BASE, LED_PNS_ALL, FSM_PedTL[FSM_Ped_State].PedOut);
    GPIOPinWrite(LED_PEW_PORT_BASE, LED_PEW_ALL, FSM_PedTL[FSM_Ped_State].PedOut);

    //Set and enable the CarTL timer
    GPTM_CarTL_Enable();

    //Timer IntRegister to ISR2
    GPTM_PedTL_IntRegister(PedTL_ISR2);

    //Enable the PedTL Timer
    GPTM_PedTL_Enable();

    //Clear the btn interrupt requests due to switch bouncing
    // or user press many time when the pedestrian light is green
    if(FSM_Ped_State == FSM_PED_STOP_NS)
    {
    	GPIOIntClear(BTN_PNS_PORT_BASE, BTN_PNS);
    }
    else
    {
      	GPIOIntClear(BTN_PEW_PORT_BASE, BTN_PEW);
    }


}
//Car Traffic Light Interrupt Service Routine when gptm pedTL timer Time out for second time
void PedTL_ISR2(void)
{
    //Disable the timer and Clear Interrupt
    GPTM_PedTL_Disable();
    GPTM_PedTL_IntClear();

    //Timer IntRegister to ISR1
    GPTM_PedTL_IntRegister(PedTL_ISR1);


    //Enable buttons Interrupt
    GPIOIntEnable(BTN_PNS_PORT_BASE, BTN_PNS);
    GPIOIntEnable(BTN_PEW_PORT_BASE, BTN_PEW);
}
