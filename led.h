#include "driverlib/gpio.h"

//********************************************************
//Define macros for Car Traffic Light Leds
//********************************************************
//********************************************************
//Define macros for Car North South traffic light led pins
//********************************************************
#define LED_CNS_RED    (GPIO_PIN_0)
#define LED_CNS_YELLOW (GPIO_PIN_1)
#define LED_CNS_GREEN  (GPIO_PIN_2)
#define LED_CNS_ALL    (GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2)
#define LED_CNS_PORT_BASE   (GPIO_PORTE_BASE)
#define LED_CNS_GPIO_PERIPH (SYSCTL_PERIPH_GPIOE)

//******************************************************
//Define macros for Car East West traffic light led pins
//******************************************************
#define LED_CEW_RED    (GPIO_PIN_3)
#define LED_CEW_YELLOW (GPIO_PIN_4)
#define LED_CEW_GREEN  (GPIO_PIN_5)
#define LED_CEW_ALL    (GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5)
#define LED_CEW_PORT_BASE   (GPIO_PORTE_BASE)
#define LED_CEW_GPIO_PERIPH (SYSCTL_PERIPH_GPIOE)

//***************************************************
//Define the car traffic light leds output for each state
//note: all the 6 leds must be assigned to different bits
//***************************************************
# define LED_CAR_GO_NS      (LED_CNS_GREEN|LED_CEW_RED)
# define LED_CAR_WAIT_NS    (LED_CNS_YELLOW|LED_CEW_ED)
# define LED_CAR_STOP_NS    (LED_CNS_RED|LED_CEW_RED)
# define LED_CAR_GO_EW      (LED_CNS_RED|LED_CEW_GREEN)
# define LED_CAR_WAIT_EW    (LED_CNS_RED|LED_CEW_YELLOW)
# define LED_CAR_STOP_EW    (LED_CNS_RED|LED_CEW_RED)
//------------------------------------------------------------
//***********************************************************
//Define macros for Pedestrian Traffic Light Leds
//***********************************************************
//***********************************************************
//Define macros for Pedestrian North South traffic light led pins
//***********************************************************
#define LED_PNS_RED    (GPIO_PIN_0)
#define LED_PNS_GREEN (GPIO_PIN_1)
#define LED_PNS_ALL    (GPIO_PIN_0|GPIO_PIN_1)
#define LED_PNS_PORT_BASE   (GPIO_PORTD_BASE)
#define LED_PNS_GPIO_PERIPH (SYSCTL_PERIPH_GPIOD)

//******************************************************
//Define macros for Pedestrian East West traffic light led pins
//******************************************************
#define LED_PEW_RED    (GPIO_PIN_2)
#define LED_PEW_GREEN  (GPIO_PIN_3)
#define LED_PEW_ALL    (GPIO_PIN_2|GPIO_PIN_3)
#define LED_PEW_PORT_BASE   (GPIO_PORTD_BASE)
#define LED_PEW_GPIO_PERIPH (SYSCTL_PERIPH_GPIOD)

//***************************************************
//Define the car traffic light leds output for each state
//note: all the 4 leds must be assigned to different bits
//***************************************************
# define LED_PED_GO_NS      (LED_PNS_GREEN|LED_PEW_RED)
# define LED_PED_STOP_NS    (LED_PNS_RED|LED_PEW_RED)
# define LED_PED_GO_EW      (LED_PNS_RED|LED_PEW_GREEN)
# define LED_PED_STOP_EW    (LED_PNS_RED|LED_PEW_RED)
