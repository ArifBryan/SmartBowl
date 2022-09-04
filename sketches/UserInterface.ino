#include "UserInterface.h"
#include "Pins.h"
#include <Adafruit_GFX.h>    
#include <Adafruit_ST7789.h> 

UserInterface_TypeDef ui;

Adafruit_ST7789 lcd(TFT_CS, TFT_DC, TFT_RST);

void UserInterface_TypeDef::SetBrightness(uint8_t bright) {
	ledcWrite(0, bright * 2.55);
}

void UserInterface_TypeDef::Init() {
	pinMode(TFT_BKLT, OUTPUT);
	ledcSetup(0, 5000, 8);
	ledcAttachPin(TFT_BKLT, 0);
	
	lcd.init(240, 240, SPI_MODE2);
	lcd.setRotation(1);
	lcd.fillScreen(ST77XX_WHITE);
	SetBrightness(10);
}

void UserInterface_TypeDef::Handler() {
	
}