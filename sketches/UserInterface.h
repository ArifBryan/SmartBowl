#pragma once

#include <Arduino.h>

struct UserInterface_TypeDef {
	void Init();
	void Handler();
	void SetBrightness(uint8_t bright);
};

extern UserInterface_TypeDef ui;