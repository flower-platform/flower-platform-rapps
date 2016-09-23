#include <Arduino.h>
#include <HardwareSerial.h>
#include <stdbool.h>
#include <FlowerPlatformMathManip.h>
#include <FlowerPlatformStringManip.h>

#include <Input.h>
#include <Adafruit_SSD1306_Component.h>


class AppGen {
public: 
	
	Input button1;
	Adafruit_SSD1306_Component display;

	char text[40];
	int nr_pressed;

	AppGen()
		: display(24)
	{};

	void _setup() {
        display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.setCursor(0,0);
        nr_pressed = 0;
        sprintf(text,"");
        display.println("Press that button");
        display.display();
        delay(2000);

	}

	void button1_onValueChanged(ValueChangedEvent* event) {
        display.clearDisplay();
        display.setCursor(0,0);
        if ( (event->currentValue == HIGH) ) {
            if ( (nr_pressed == 0) ) {
                display.clearDisplay();
                sprintf(text,"Button pressed. Let the count begin");
                display.setTextSize(2);
                display.println(text);;
                display.display();
                delay(2000);
                display.setCursor(0,0);
                display.setTextSize(2);
                display.clearDisplay();
            }
            sprintf(text,"Number pressed: %d", ++nr_pressed);
        }
        display.println(text);;
        display.display();

	}
	

	void setup() {
		_setup();
		
		button1.pin = 0;
		button1.internalPullUp = true;
		button1.onValueChanged = new DelegatingCallback<AppGen, ValueChangedEvent>(this, &AppGen::button1_onValueChanged); 


		button1.setup();
	}

	void loop() {
		button1.loop();
	}

};

#include "CustomCode.h"

App* app;

void setup() {
	Serial.begin(115200);
	app = new App();
	app->setup();
}

void loop() {
	app->loop();
}
