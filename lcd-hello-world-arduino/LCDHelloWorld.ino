#include <Arduino.h>
#include <HardwareSerial.h>
#include <stdbool.h>

#include <LiquidCrystalComponent.h>


class AppGen {
public: 
	
	LiquidCrystalComponent lcd;

	AppGen() : lcd(9,8,7,6,5,3) {}
			

	void setup() {

		lcd.setup();
	}

	void loop() {
		lcd.loop();
	}
	
};

#include "CustomCode.h"

App app;

void setup() {
	Serial.begin(115200);
	app.setup();
}

void loop() {
	app.loop();
}
