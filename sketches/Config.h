#pragma once

#include <Arduino.h>

struct Param_TypeDef {
	float SensCal;
	float SensFil;
	float VbatCal;
	uint8_t Bright;
	uint8_t key;
};

struct Config_TypeDef {
	Param_TypeDef param;
	void RestoreDefault();
	void Save();
	void Read();
	void Init();
};

Param_TypeDef defParam = { 1, 8, 1.75, 30, 0xAA };

extern Config_TypeDef config;