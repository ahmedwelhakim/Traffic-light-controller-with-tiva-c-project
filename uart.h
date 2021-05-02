#include <stdint.h>
#include <stdbool.h>

//
//Prototypes declaration
//

void UART_Init(void);
void UART_PrintSystemState(uint8_t sysState,uint8_t carState);
void UART_PrintString(char * str);
