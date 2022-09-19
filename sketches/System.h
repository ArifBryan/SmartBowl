#pragma once

#define FW_VER	"2.4"
#define BATT_LOW_THRES	10

struct System_TypeDef {
	void Init(void(*Startup_Handler)(void), void(*Shutdown_Handler)(void));
	void Handler();
	void PowerOff();
	bool IsCharging() {
		return chgStatus > 0;
	}
	bool IsCharged() {
		return chgStatus > 1;
	}
	uint16_t GetVbat() {
		return vBat;
	}
	uint8_t GetBattPercentage() {
		int16_t percent = round((vBat - 3700) / 5);
		percent = (percent < 0 ? 0 : (percent > 100 ? 100 : percent));
		if (chgStatus == 2) {percent = 100;}
		return percent;
	}
	void SetVbatCalValue(float cal) {
		vBatCal = cal;
	}
	bool IsBattLow() {
		return GetBattPercentage() <= BATT_LOW_THRES;
	}
	
private:
	void(*Shutdown_Handler)(void);
	uint32_t pwrBtnTmr;
	uint16_t vBat;
	float vBatCal = 1;
	uint32_t sysTimer;
	uint8_t chgStatus;
	uint32_t powerOffTimer;
};

extern System_TypeDef sys;