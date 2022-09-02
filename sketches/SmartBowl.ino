#include <BluetoothSerial.h>
#include <Adafruit_GFX.h>    
#include <Adafruit_ST7789.h> 
#include <SPI.h>           
#include <HX711.h>

#define PWR_LATCH	2
#define BTN_PWR		17
#define CHG_CON		4
#define CHG_STA		16
#define VBAT_SENSE	33

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
	pinMode(CHG_CON, INPUT_PULLUP);
	pinMode(CHG_STA, INPUT_PULLUP);
	pinMode(BTN_PWR, INPUT_PULLUP);
	digitalWrite(PWR_LATCH, HIGH);
	ledcSetup(0, 5000, 8);
	ledcAttachPin(TFT_BKLT, 0);
	ledcWrite(0, 0);
	delay(100);
	
	LoadCell.begin(HX_DATA, HX_SCK);
	ledcWrite(0, 30);
	tft.init(240, 240, SPI_MODE2);
	tft.setRotation(1);
	tft.fillScreen(ST77XX_WHITE);
  
	Serial.begin(115200);
	SerialBT.begin("BOWELL");
}

uint32_t i;
uint8_t val = 30;
float adcFiltered;
uint8_t kf = 3;
uint32_t vbat;
uint32_t dspTmr;
void loop(){
	adcFiltered = ((adcFiltered * kf) + LoadCell.get_value(1)) / (kf + 1);
	vbat = analogRead(VBAT_SENSE);
	//Serial.println(vbat);
	if (millis() - dspTmr >= 500) {
		dspTmr = millis();
		if (!digitalRead(CHG_CON)) {
			if (!digitalRead(CHG_STA)) {
				tft.fillRect(0, 0, 240, 24, ST77XX_ORANGE);
			}
			else {
				tft.fillRect(0, 0, 240, 24, ST77XX_GREEN);
			}
		}
		else if (!digitalRead(BTN_PWR)) {
			tft.fillRect(0, 0, 240, 24, ST77XX_BLUE);
			LoadCell.tare();
		}
		else {	
			tft.fillRect(0, 0, 240, 24, 0x1111);
		}
		tft.setTextColor(ST77XX_WHITE);
		tft.setCursor(1, 1);
		tft.setTextSize(3);
		tft.print("Test");
		
		tft.setTextColor(ST77XX_BLACK, ST77XX_WHITE);
		tft.setCursor(1, 26);
		tft.print("Val. : ");
		tft.print(adcFiltered / 1000);
		tft.print(" ");
		//SerialBT.println(abs(adcFiltered / 1000));
		
		tft.setCursor(1, 52);
		tft.print("VBat : ");
		tft.print(vbat);
		tft.print(" ");
		
		tft.setCursor(1, 78);
		if (!digitalRead(CHG_CON)) {
			if (!digitalRead(CHG_STA)) {
				tft.print("Charging     ");
			}
			else {
				tft.print("Charged      ");
			}
		}
		else {
			tft.print("Not charging ");
		}
		tft.setCursor(1, 105);
		tft.print(i);
		
	}
	while (SerialBT.available()) {
		Serial.write(SerialBT.read());
	}
//	ledcWrite(0, val);
//	tft.invertDisplay(true);
//	delay(100);
//	tft.invertDisplay(false);
}
