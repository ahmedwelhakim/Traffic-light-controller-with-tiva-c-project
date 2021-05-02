#include <stdint.h>
#include <stdbool.h>
# include "uart.h"
#include "fsm.h"
#include "inc/hw_memmap.h"
#include "driverlib/uart.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
# include "tm4c123gh6pm.h"
//#define PART_TM4C123GH6PM
void UART_Init(void)
{
	//Activate UART0 and Port A Clock
	//
	SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0));
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));

	//
	//disable UART For configuration
	UARTDisable(UART0_BASE);
	// Configuration 9600 baud rate and 8 bit
	UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 9600, UART_CONFIG_WLEN_8);

	UARTFIFOEnable(UART0_BASE);

	GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0|GPIO_PIN_1);

	//UART pins Configuration
	GPIOPinConfigure(GPIO_PA0_U0RX);
	GPIOPinConfigure(GPIO_PA1_U0TX);

	//
	//Enable the UART
	UARTEnable(UART0_BASE);

}
void UART_PrintSystemState(uint8_t sysState,uint8_t carState)
{
	switch (sysState)
	{
	case FSM_SYS_CAR_NS:
		switch (carState)
		{
			case FSM_CAR_GO_NS:
				UART_PrintString("System state is: CAR NORTH SOUTH (GREEN) \n\n \r");
				break;
			case FSM_CAR_WAIT_NS:
				UART_PrintString("System state is: CAR NORTH SOUTH (YELLOW) \n\n \r");
				break;
			case FSM_CAR_STOP_NS:
				UART_PrintString("System state is: CAR NORTH SOUTH (RED) \n\n \r");
				break;
			default:
				break;
		}

		break;
	case FSM_SYS_CAR_EW:
		switch (carState)
		{
			case FSM_CAR_GO_EW:
				UART_PrintString("System state is: CAR EAST WEST (GREEN) \n\n \r");
				break;
			case FSM_CAR_WAIT_EW:
				UART_PrintString("System state is: CAR EAST WEST (YELLOW) \n\n \r");
				break;
			case FSM_CAR_STOP_EW:
				UART_PrintString("System state is: CAR EAST WEST (RED) \n\n \r");
				break;
			default:
				break;
		}
		break;
	case FSM_SYS_PED_NS:
		UART_PrintString("System state is: PEDESTRIAN NORTH SOUTH \n\n \r");
		break;
	case FSM_SYS_PED_EW:
		UART_PrintString("System state is: PEDESTRIAN EAST WEST \n\n \r");
		break;
	default:
		UART_PrintString("System state is: UNDEFINED SYS STATE \n \r");
		break;
	}
}
void UART_PrintString(char * str)
{
  while(*str)
  {
    UARTCharPut(UART0_BASE, *(str++));
  }
}
