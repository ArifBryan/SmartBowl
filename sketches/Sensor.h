#pragma once

#include <Arduino.h>

struct Sensor_TypeDef{
	void Init();
	void Handler();
	void Tare() {
		offset = rawDataFiltered;
	}
	int32_t GetRawData() {
		return rawDataFiltered;
	}
	float GetWeight() {
		return weight;
	}
	void SetCalValue(float cal) {
		this->cal = cal;
	}
	void SetFilCoeff(float kf) {
		filterKf = kf;
	}
	
private:
	uint32_t sampleTmr;
	float cal;
	int32_t rawData;
	int32_t rawDataFiltered;
	float weight;
	int32_t offset;
	float filterKf;

};

extern Sensor_TypeDef sens;