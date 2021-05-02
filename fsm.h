
#include <stdint.h>
#include <stdbool.h>
#include "led.h"

//****************************************************
// Declare the fsm golbal variables
//****************************************************
extern volatile uint8_t FSM_Car_State;

extern volatile uint8_t FSM_Ped_State;

extern volatile uint8_t FSM_Sys_State;

//***************************************************
//Define the system states
//***************************************************
# define FSM_SYS_CAR_NS      (0)
# define FSM_SYS_CAR_EW      (1)
# define FSM_SYS_PED_NS      (2)
# define FSM_SYS_PED_EW      (3)


//****************************************************
//First Car Traffic Light FSM
//****************************************************
//****************************************************
// Define struct for car traffic light States
//****************************************************
struct CarFSM
{
  uint8_t Out;  // output bits for car traffic led
  uint16_t Time; // delay in Milli Second
  uint8_t Next;// The next state
  uint8_t SysState;// System State
};


//***************************************************
//Define the states of Car Traffic Light
//***************************************************
# define FSM_CAR_GO_NS      (0)
# define FSM_CAR_WAIT_NS    (1)
# define FSM_CAR_STOP_NS    (2)
# define FSM_CAR_GO_EW      (3)
# define FSM_CAR_WAIT_EW    (4)
# define FSM_CAR_STOP_EW    (5)

//***************************************************
//Declare a constant array of type car fsm
//***************************************************
extern const struct CarFSM FSM_CarTL[6];

//----------------------------------------------------
//****************************************************
//Second Pedestrian Traffic Light FSM
//****************************************************
//****************************************************
// Define struct for Pedestrian traffic light States
//****************************************************
struct PedFSM
{
  uint8_t PedOut;  // output bits for pedestrian traffic led
  uint8_t CarOut[6];  // output bits for Car traffic led and take the car state as index
  uint8_t Next;// The next state
};
//****************************************************
//Define the states of Pedestrian Traffic Light
//****************************************************
# define FSM_PED_GO_NS      (0)
# define FSM_PED_STOP_NS    (1)
# define FSM_PED_GO_EW      (2)
# define FSM_PED_STOP_EW    (3)

//***************************************************
//Declare a constant array of type Pedestrian fsm
//***************************************************
extern const struct PedFSM FSM_PedTL[4];

