#pragma once

#include <Arduino.h>

struct Sensor_TypeDef{
	void Init();
	void Handler();
};

extern Sensor_TypeDef sens;