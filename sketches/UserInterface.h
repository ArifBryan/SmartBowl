#pragma once

#include <Arduino.h>

// Color definitions
#define RGB565_BLACK 0x0000       ///<   0,   0,   0
#define RGB565_NAVY 0x000F        ///<   0,   0, 123
#define RGB565_DARKGREEN 0x03E0   ///<   0, 125,   0
#define RGB565_DARKCYAN 0x03EF    ///<   0, 125, 123
#define RGB565_MAROON 0x7800      ///< 123,   0,   0
#define RGB565_PURPLE 0x780F      ///< 123,   0, 123
#define RGB565_OLIVE 0x7BE0       ///< 123, 125,   0
#define RGB565_LIGHTGREY 0xC618   ///< 198, 195, 198
#define RGB565_DARKGREY 0x7BEF    ///< 123, 125, 123
#define RGB565_BLUE 0x001F        ///<   0,   0, 255
#define RGB565_GREEN 0x07E0       ///<   0, 255,   0
#define RGB565_CYAN 0x07FF        ///<   0, 255, 255
#define RGB565_RED 0xF800         ///< 255,   0,   0
#define RGB565_MAGENTA 0xF81F     ///< 255,   0, 255
#define RGB565_YELLOW 0xFFE0      ///< 255, 255,   0
#define RGB565_WHITE 0xFFFF       ///< 255, 255, 255
#define RGB565_ORANGE 0xFD20      ///< 255, 165,   0
#define RGB565_GREENYELLOW 0xAFE5 ///< 173, 255,  41

struct TextBox_TypeDef {
	TextBox_TypeDef(uint8_t xPos, uint8_t yPos) {
		this->xPos = xPos;
		this->yPos = yPos;
	}
	void DrawText(const char *txt);
	
private:
	uint8_t xPos, yPos;
};

struct UserInterface_TypeDef {
	void Init();
	void Handler();
	void SetBrightness(uint8_t bright);
	void BootScreen();
	TextBox_TypeDef Text[5] = { TextBox_TypeDef(0, 30), TextBox_TypeDef(0, 70), TextBox_TypeDef(0, 110), TextBox_TypeDef(0, 150), TextBox_TypeDef(0, 190) };
	
private:
	uint32_t dispTimer;
};

extern UserInterface_TypeDef ui;