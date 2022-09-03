#pragma once

struct System_TypeDef {
	void Init(void(*Startup_Handler)(void), void(*Shutdown_Handler)(void));
	void Handler();
	
private:
	void(*Shutdown_Handler)(void);
};

extern System_TypeDef sys;