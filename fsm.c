# include "fsm.h"
# include <stdint.h>


//****************************************************
//Define fsm global variables
//****************************************************

//Contain the current state of car traffic light
volatile uint8_t FSM_Car_State;

//Contain the current state of pedestrian traffic light
volatile uint8_t FSM_Ped_State;

//contain the current system of the system
volatile uint8_t FSM_Sys_State;


//***************************************************
//Define a constant array of type car fsm with all
//the states informations
//***************************************************
const struct CarFSM FSM_CarTL[6]=
{
 {LED_CAR_GO_NS,5000,FSM_CAR_WAIT_NS,FSM_SYS_CAR_NS},
 {LED_CAR_WAIT_NS,2000,FSM_CAR_STOP_NS,FSM_SYS_CAR_NS},
 {LED_CAR_STOP_NS,1000,FSM_CAR_GO_EW,FSM_SYS_CAR_NS},
 {LED_CAR_GO_EW,5000,FSM_CAR_WAIT_EW,FSM_SYS_CAR_EW},
 {LED_CAR_WAIT_EW,2000,FSM_CAR_STOP_EW,FSM_SYS_CAR_EW},
 {LED_CAR_STOP_EW,1000,FSM_CAR_GO_NS,FSM_SYS_CAR_EW}
};


//***************************************************
//Define a constant array of type Pedestrian fsm with
//all the states informations
//***************************************************
const struct PedFSM FSM_PedTL[4]=
{
 {LED_PED_GO_NS,{LED_CAR_GO_NS,LED_CAR_WAIT_NS,LED_CAR_STOP_NS,
				 LED_CAR_STOP_NS,LED_CAR_STOP_NS,LED_CAR_STOP_EW},FSM_PED_STOP_NS},
 {LED_PED_STOP_NS,{LED_CAR_GO_NS,LED_CAR_WAIT_NS,LED_CAR_STOP_NS,
                   LED_CAR_GO_EW,LED_CAR_WAIT_EW,LED_CAR_STOP_EW},FSM_PED_STOP_NS},
 {LED_PED_GO_EW,{LED_CAR_STOP_NS,LED_CAR_STOP_NS,LED_CAR_STOP_NS,
                 LED_CAR_GO_EW,LED_CAR_WAIT_EW,LED_CAR_STOP_EW},FSM_PED_STOP_EW},
 {LED_PED_STOP_EW,{LED_CAR_GO_NS,LED_CAR_WAIT_NS,LED_CAR_STOP_NS,
                   LED_CAR_GO_EW,LED_CAR_WAIT_EW,LED_CAR_STOP_EW},FSM_PED_STOP_EW}
};
