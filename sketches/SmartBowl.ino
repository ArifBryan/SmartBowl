#include <BluetoothSerial.h>
#include <Adafruit_GFX.h>    
#include <Adafruit_ST7789.h> 
#include <SPI.h>           
#include <HX711.h>

#define PWR_LATCH	2

#define TFT_BKLT	19
#define TFT_CS		35
#define TFT_RST		22  
#define TFT_DC		21  

#define HX_DATA		27
#define HX_SCK		26

BluetoothSerial SerialBT;
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
HX711 LoadCell;

void setup(){
	pinMode(PWR_LATCH, OUTPUT);
	digitalWrite(PWR_LATCH, HIGH);
	ledcSetup(0, 5000, 8);
	ledcAttachPin(TFT_BKLT, 0);
	ledcWrite(0, 0);
	delay(100);
	
	LoadCell.begin(HX_DATA, HX_SCK);
	ledcWrite(0, 30);
	tft.init(240, 240, SPI_MODE2);
	tft.fillScreen(ST77XX_BLACK);
  
	SerialBT.begin("ESP32");
}

uint32_t i;
uint8_t val = 30;
void loop(){
	LoadCell.read();
	ledcWrite(0, val);
	SerialBT.println(i++);
	tft.invertDisplay(true);
	delay(500);
	tft.invertDisplay(false);
	delay(500);
}
