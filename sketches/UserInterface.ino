#include "UserInterface.h"
#include "Pins.h"
#include <Adafruit_GFX.h>    
#include <Adafruit_ST7789.h> 
#include <Fonts/FreeSans12pt7b.h>
#include "Icons.h"

UserInterface_TypeDef ui;

Adafruit_ST7789 lcd(TFT_CS, TFT_DC, TFT_RST);

void UserInterface_TypeDef::SetBrightness(uint8_t bright) {
	ledcWrite(0, bright * 2.55);
}

void UserInterface_TypeDef::BootScreen() {
	lcd.fillScreen(RGB565_WHITE);
	lcd.drawRGBBitmap(20, 97, BOWELL_icon, BOWELL_ICON_WIDTH, BOWELL_ICON_HEIGHT);
	lcd.setCursor(80, 239);
	lcd.print("Ver.");
	lcd.print(FW_VER);
	SetBrightness(50);
	delay(2000);
	lcd.fillScreen(RGB565_WHITE);
}

void UserInterface_TypeDef::Init() {
	pinMode(TFT_BKLT, OUTPUT);
	ledcSetup(0, 5000, 8);
	ledcAttachPin(TFT_BKLT, 0);
	
	lcd.setFont(&FreeSans12pt7b);
	lcd.setTextColor(RGB565_DARKGREY);
	lcd.init(240, 240, SPI_MODE2);
	lcd.setRotation(1);
}

void UserInterface_TypeDef::Handler() {
	if (millis() - dispTimer >= 250) {
		GFXcanvas16 frame1(209, 20);
		
		frame1.setFont(&FreeSans12pt7b);
		frame1.setTextColor(RGB565_DARKGREY);
		frame1.fillScreen(RGB565_WHITE);
		frame1.setCursor(0, 18);
		frame1.print("Test");
		
		GFXcanvas16 battInfo(28, 18);
		battInfo.fillScreen(RGB565_WHITE);
		battInfo.fillRoundRect(0, 0, 25, 18, 2, RGB565_DARKGREY);
		battInfo.fillRect(25, 6, 3, 6, RGB565_DARKGREY);
		
		uint8_t bar = round(sys.GetBattPercentage() * 0.21);
		uint32_t barColor = (sys.GetBattPercentage() > 20 ? RGB565_WHITE : RGB565_RED);
		barColor = (sys.IsCharging() ? RGB565_ORANGE : barColor);
		barColor = (sys.IsCharged() ? RGB565_GREEN : barColor);
		battInfo.fillRoundRect(2, 2, bar, 14, 1, barColor);
		
		lcd.drawRGBBitmap(0, 0, frame1.getBuffer(), 209, 20);
		lcd.drawRGBBitmap(210, 1, battInfo.getBuffer(), 28, 18);
		
		dispTimer = millis();
	}
}