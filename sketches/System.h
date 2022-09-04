#pragma once

#define POWERON_CAUSE_BTN	1
#define POWERON_CAUSE_CHG	2

struct System_TypeDef {
	void Init(void(*Startup_Handler)(void), void(*Shutdown_Handler)(void));
	void Handler();
	void PowerOff();
	
private:
	void(*Shutdown_Handler)(void);
	uint32_t pwrBtnTmr;
	uint8_t powerOnCause;
};

extern System_TypeDef sys;