#include <BluetoothSerial.h>

#define PWR_LATCH	2

BluetoothSerial SerialBT;

void setup(){
	pinMode(PWR_LATCH, OUTPUT);
	digitalWrite(PWR_LATCH, HIGH);
	delay(100);
	
	SerialBT.begin("ESP32");
}

uint32_t i;
void loop(){
	SerialBT.println(i++);
	delay(500);
}
