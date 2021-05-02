#include <stdbool.h>
#include <stdint.h>

//**********************************************************
// GPTM Car Traffic Light prototypes
//**********************************************************
void GPTM_CarTL_Init(void);
void GPTM_CarTL_SetPeriodInMS(uint32_t tms);
void GPTM_CarTL_Disable(void);
void GPTM_CarTL_Enable(void);
void GPTM_CarTL_IntEnable(void);
void GPTM_CarTL_IntDisable(void);
void GPTM_CarTL_IntClear(void);
void GPTM_CarTL_IntRegister(void(*pfnHandeler)(void));

//**********************************************************
// GPTM Pedestrian Traffic Light prototypes
//**********************************************************
void GPTM_PedTL_Init(void);
void GPTM_PedTL_SetPeriodInMS(uint32_t tms);
void GPTM_PedTL_Disable(void);
void GPTM_PedTL_Enable(void);
void GPTM_PedTL_IntEnable(void);
void GPTM_PedTL_IntDisable(void);
void GPTM_PedTL_IntClear(void);
void GPTM_PedTL_IntRegister(void(*pfnHandeler)(void));
