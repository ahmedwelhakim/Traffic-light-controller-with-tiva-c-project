# include <stdint.h>
# include <stdbool.h>
# include "gptm.h"
# include "fsm.h"
# include "btn.h"
# include "driverlib/sysctl.h"
# include "driverlib/gpio.h"
# include "driverlib/interrupt.h"
# include "inc/hw_memmap.h"
# include "uart.h"
void Btn_Init(void)
{
    //
    //Enable clock for ports and check whether peripheral is ready
    //
    SysCtlPeripheralEnable(BTN_PNS_GPIO_PERIPH);
    SysCtlPeripheralEnable(BTN_PEW_GPIO_PERIPH);
    while(!SysCtlPeripheralReady(BTN_PNS_GPIO_PERIPH));
    while(!SysCtlPeripheralReady(BTN_PEW_GPIO_PERIPH));

    //
    //Set Pedestrian Traffic Light Buttons pins as input
    //
    GPIOPinTypeGPIOInput(BTN_PNS_PORT_BASE,BTN_PNS);
    GPIOPinTypeGPIOInput(BTN_PEW_PORT_BASE,BTN_PEW);

    // Pull up resistor
    GPIOPadConfigSet(BTN_PNS_PORT_BASE, BTN_PNS, GPIO_STRENGTH_2MA , GPIO_PIN_TYPE_STD_WPU);
    GPIOPadConfigSet(BTN_PEW_PORT_BASE, BTN_PEW, GPIO_STRENGTH_2MA , GPIO_PIN_TYPE_STD_WPU);

    //
    //GPIO interrupt configuration
    //
    GPIOIntDisable(BTN_PNS_PORT_BASE, BTN_PNS);
    GPIOIntDisable(BTN_PEW_PORT_BASE, BTN_PEW);

    GPIOIntTypeSet(BTN_PNS_PORT_BASE, BTN_PNS, GPIO_FALLING_EDGE);
    GPIOIntTypeSet(BTN_PEW_PORT_BASE, BTN_PEW, GPIO_FALLING_EDGE);

    GPIOIntRegister(BTN_PNS_PORT_BASE, Btn_NS_ISR);
    GPIOIntRegister(BTN_PEW_PORT_BASE, Btn_EW_ISR);

//    //Set highest priority
//    IntPrioritySet(BTN_PNS_PORT_INT, 0);

    GPIOIntEnable(BTN_PNS_PORT_BASE, BTN_PNS);
    GPIOIntEnable(BTN_PEW_PORT_BASE, BTN_PEW);
}

void Btn_NS_ISR(void)
{
    //Clear Interrupt
    GPIOIntClear(BTN_PNS_PORT_BASE, BTN_PNS);

    //Disable both buttons Interrupt
    GPIOIntDisable(BTN_PNS_PORT_BASE, BTN_PNS);
    GPIOIntDisable(BTN_PEW_PORT_BASE, BTN_PEW);


    //Disable CarTL timer
    GPTM_CarTL_Disable();


    //Set and enable the pedestrian timer
    GPTM_PedTL_Disable();
    GPTM_PedTL_SetPeriodInMS(2000); // 2 seconds
    GPTM_PedTL_Enable();

    //Change The FSM state of pedestrian
    FSM_Ped_State=FSM_PED_GO_NS;

    //Change The System State and send it UART
    FSM_Sys_State=FSM_SYS_PED_NS;
    UART_PrintSystemState(FSM_Sys_State,FSM_Car_State);

    //Write All the Traffic Lights LED
    GPIOPinWrite(LED_CNS_PORT_BASE, LED_CNS_ALL, FSM_PedTL[FSM_Ped_State].CarOut[FSM_Car_State]);
    GPIOPinWrite(LED_CEW_PORT_BASE, LED_CEW_ALL, FSM_PedTL[FSM_Ped_State].CarOut[FSM_Car_State]);

    GPIOPinWrite(LED_PNS_PORT_BASE, LED_PNS_ALL, FSM_PedTL[FSM_Ped_State].PedOut);
    GPIOPinWrite(LED_PEW_PORT_BASE, LED_PEW_ALL, FSM_PedTL[FSM_Ped_State].PedOut);
}
void Btn_EW_ISR(void)
{
    //Clear Interrupt
    GPIOIntClear(BTN_PEW_PORT_BASE, BTN_PEW);

    //Disable both buttons Interrupt
    GPIOIntDisable(BTN_PNS_PORT_BASE, BTN_PNS);
    GPIOIntDisable(BTN_PEW_PORT_BASE, BTN_PEW);

    //Disable CarTL timer
    GPTM_CarTL_Disable();



    //Set and enable the pedestrian timer
    GPTM_PedTL_Disable();
    GPTM_PedTL_SetPeriodInMS(2000); // 2 seconds
    GPTM_PedTL_Enable();

    //Change The FSM state of pedestrian
    FSM_Ped_State=FSM_PED_GO_EW;

    //Change The System State and send it UART
     FSM_Sys_State=FSM_SYS_PED_EW;
     UART_PrintSystemState(FSM_Sys_State,FSM_Car_State);

    //Write All the Traffic Lights LED
    GPIOPinWrite(LED_CNS_PORT_BASE, LED_CNS_ALL, FSM_PedTL[FSM_Ped_State].CarOut[FSM_Car_State]);
    GPIOPinWrite(LED_CEW_PORT_BASE, LED_CEW_ALL, FSM_PedTL[FSM_Ped_State].CarOut[FSM_Car_State]);

    GPIOPinWrite(LED_PNS_PORT_BASE, LED_PNS_ALL, FSM_PedTL[FSM_Ped_State].PedOut);
    GPIOPinWrite(LED_PEW_PORT_BASE, LED_PEW_ALL, FSM_PedTL[FSM_Ped_State].PedOut);

}
