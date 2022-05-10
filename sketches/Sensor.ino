#include <Arduino.h>

uint32_t loadCellSampleInterval;
uint32_t loadCellSampleTmr;

void Sensor_Handler() {
	if (millis() - loadCellSampleTmr >= loadCellSampleInterval) {
		loadCellSampleTmr = millis();
	}
}