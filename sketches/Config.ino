#include "Config.h"
#include <EEPROM.h>

#define EEPROM_SAVE_ADDR	0

Config_TypeDef config;

void Config_TypeDef::Read() {
	EEPROM.get(EEPROM_SAVE_ADDR, param);
}

void Config_TypeDef::Save() {
	EEPROM.put(EEPROM_SAVE_ADDR, param);
	EEPROM.commit();
}

void Config_TypeDef::Init() {
	EEPROM.begin(sizeof(Param_TypeDef));
	Read();
	if (param.key != 0xAA) {
		param = defParam;
		Save();
	}
}