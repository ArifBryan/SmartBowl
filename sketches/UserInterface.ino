#include "UserInterface.h"
#include "Pins.h"
#include <Adafruit_GFX.h>    
#include <Adafruit_ST7789.h> 
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans18pt7b.h>
#include <Fonts/FreeSans24pt7b.h>
#include "Icons.h"

UserInterface_TypeDef ui;

Adafruit_ST7789 lcd(TFT_CS, TFT_DC, TFT_RST);

bool startup = 1;

void UserInterface_TypeDef::SetBrightness(uint8_t bright) {
	ledcWrite(0, bright * 2.55);
}

void UserInterface_TypeDef::BootScreen() {
	lcd.fillScreen(RGB565_WHITE);
	lcd.drawRGBBitmap(20, 97, BOWELL_icon, BOWELL_ICON_WIDTH, BOWELL_ICON_HEIGHT);
	lcd.setCursor(80, 235);
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
	lcd.setRotation(3);
	lcd.fillScreen(RGB565_WHITE);
}

void UserInterface_TypeDef::Handler() {
	if (millis() - dispTimer >= 250 || startup) {
		
		uint32_t statBarColor = RGB565_DARKCYAN;
		GFXcanvas16 statBar(210, 25);
		
		statBar.setFont(&FreeSans12pt7b);
		statBar.fillScreen(statBarColor);
		statBar.setTextColor(RGB565_WHITE);
		statBar.setCursor(0, 21);
		statBar.print("BOWELL");
		
		GFXcanvas16 battInfo(30, 25);
		battInfo.fillScreen(statBarColor);
		battInfo.fillRoundRect(0, 4, 25, 18, 2, RGB565_WHITE);
		battInfo.fillRect(25, 10, 3, 6, RGB565_WHITE);
		
		uint8_t bar = round(sys.GetBattPercentage() * 0.21);
		uint32_t barColor = (sys.GetBattPercentage() > 20 ? statBarColor : RGB565_RED);
		barColor = (sys.IsCharging() ? RGB565_ORANGE : barColor);
		barColor = (sys.IsCharged() ? RGB565_GREEN : barColor);
		battInfo.fillRoundRect(2, 6, bar, 14, 1, barColor);
				
		lcd.drawRGBBitmap(0, 0, statBar.getBuffer(), 210, 25);
		lcd.drawRGBBitmap(210, 0, battInfo.getBuffer(), 30, 25);
		
		dispTimer = millis();
		startup = 0;
	}
}

void UserInterface_TypeDef::BatteryScreen() {
	if (millis() - dispTimer >= 250 || startup) {
		
		uint32_t battColor = RGB565_WHITE;
		GFXcanvas16 battInfo(200, 140);
		battInfo.fillScreen(battColor);
		battInfo.fillRoundRect(0, 0, 190, 140, 4, RGB565_BLACK);
		battInfo.fillRect(190, 50, 10, 40, RGB565_BLACK);
		
		uint8_t bar = round(sys.GetBattPercentage() * 1.80);
		uint32_t barColor = (sys.GetBattPercentage() > 20 ? battColor : RGB565_RED);
		barColor = (sys.IsCharging() ? RGB565_ORANGE : barColor);
		barColor = (sys.IsCharged() ? RGB565_GREEN : barColor);
		battInfo.fillRoundRect(5, 5, bar, 130, 2, barColor);
		
		lcd.drawRGBBitmap(20, 50, battInfo.getBuffer(), battInfo.width(), battInfo.height());
		
		dispTimer = millis();
		startup = 0;
	}
}

void TextBox_TypeDef::DrawText(const char *txt) {
	GFXcanvas16 frame(240, 40);
	
	frame.fillScreen(RGB565_WHITE);
	frame.setFont(&FreeSans18pt7b);
	frame.setTextColor(RGB565_DARKGREY);
	int16_t x1, y1;
	uint16_t w, h;
	frame.getTextBounds(txt, 1, 3, &x1, &y1, &w, &h);
	frame.setCursor((240 - w) / 2 - 1, 30);
	frame.print(txt);
	
	lcd.drawRGBBitmap(xPos, yPos, frame.getBuffer(), 240, 40);	
}
