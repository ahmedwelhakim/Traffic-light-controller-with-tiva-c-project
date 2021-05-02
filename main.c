#include "carTL.h"
#include "pedTL.h"
#include "uart.h"
#include <stdint.h>
#include "driverlib/sysctl.h"


int main(void)
{
	//UART Initialization
	//
	UART_Init();

    //
    //Initialize the Car Traffic Light
    //
    CarTL_Init();

    //Initialize the Pedestrian Traffic Light
    //
    PedTL_Init();



    while(1)
    {
        //
        //Enter Sleep mode until an interrupt occurs
        //
        SysCtlSleep();

    }
}

