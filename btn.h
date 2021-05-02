#include "driverlib/gpio.h"
# include "tm4c123gh6pm.h"
//******************************************************
//Define macros for Pedestrian buttons
//******************************************************
#define BTN_PNS     (GPIO_PIN_4)
#define BTN_PEW     (GPIO_PIN_5)
#define BTN_PNS_PORT_BASE   (GPIO_PORTB_BASE)
#define BTN_PEW_PORT_BASE   (GPIO_PORTC_BASE)
#define BTN_PNS_PORT_INT    (INT_GPIOB)
#define BTN_PEW_PORT_INT    (INT_GPIOC)
#define BTN_PNS_GPIO_PERIPH (SYSCTL_PERIPH_GPIOB)
#define BTN_PEW_GPIO_PERIPH (SYSCTL_PERIPH_GPIOC)

//
//Prototypes
//
void Btn_Init(void);
void Btn_NS_ISR(void);
void Btn_EW_ISR(void);
