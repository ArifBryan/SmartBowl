#include "UserInterface.h"
#include "Pins.h"
#include <Adafruit_GFX.h>    
#include <Adafruit_ST7789.h> 
#include <Fonts/FreeSans12pt7b.h>

UserInterface_TypeDef ui;

Adafruit_ST7789 lcd(TFT_CS, TFT_DC, TFT_RST);

void UserInterface_TypeDef::SetBrightness(uint8_t bright) {
	ledcWrite(0, bright * 2.55);
}

void UserInterface_TypeDef::Init() {
	pinMode(TFT_BKLT, OUTPUT);
	ledcSetup(0, 5000, 8);
	ledcAttachPin(TFT_BKLT, 0);
	
	lcd.setFont(&FreeSans12pt7b);
	lcd.setTextColor(ST77XX_BLACK);
	lcd.init(240, 240, SPI_MODE2);
	lcd.setRotation(1);
	lcd.fillScreen(ST77XX_WHITE);
	SetBrightness(10);
}

void UserInterface_TypeDef::Handler() {
	if (millis() - dispTimer >= 250) {
		GFXcanvas16 frame1(240, 20);
		
		frame1.setFont(&FreeSans12pt7b);
		frame1.setTextColor(ST77XX_BLACK);
		frame1.fillScreen(ST77XX_WHITE);
		frame1.setCursor(0, 18);
		frame1.print("Test");
		
		GFXcanvas16 battInfo(28, 18);
		battInfo.fillScreen(ST77XX_WHITE);
		battInfo.fillRoundRect(0, 0, 25, 18, 2, ST77XX_BLACK);
		battInfo.fillRect(25, 6, 3, 6, ST77XX_BLACK);
		battInfo.fillRoundRect(2, 2, 21, 14, 1, ST77XX_WHITE);
		
		lcd.drawRGBBitmap(0, 0, frame1.getBuffer(), 240, 20);
		lcd.drawRGBBitmap(210, 1, battInfo.getBuffer(), 28, 18);
		
		dispTimer = millis();
	}
}