#pragma once

#define POWERON_CAUSE_BTN	1
#define POWERON_CAUSE_CHG	2

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
		int8_t percent = (vBat - 3700) / 5;
		percent = (percent < 0 ? 0 : (percent > 100 ? 100 : percent));
		return percent;
	}
	void SetVbatCalValue(float cal) {
		vBatCal = cal;
	}
	
private:
	void(*Shutdown_Handler)(void);
	uint32_t pwrBtnTmr;
	uint8_t powerOnCause;
	uint16_t vBat;
	float vBatCal = 1;
	uint32_t sysTimer;
	uint8_t chgStatus;
};

extern System_TypeDef sys;