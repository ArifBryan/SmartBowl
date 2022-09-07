#pragma once

#include <Arduino.h>

struct Sensor_TypeDef{
	void Init();
	void Handler();
	
private:
	uint32_t sampleTmr;

};

extern Sensor_TypeDef sens;