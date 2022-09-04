#pragma once

#include <Arduino.h>

struct UserInterface_TypeDef {
	void Init();
	void Handler();
	void SetBrightness(uint8_t bright);
	
private:
	uint32_t dispTimer;
};

extern UserInterface_TypeDef ui;