#include <Arduino.h>
#include <HardwareSerial.h>
#include <stdbool.h>

#include <Output.h>
#include <Timer.h>


class AppGen {
public: 
	
	Output led;
	Timer timer;


	AppGen()
		: led(13, false, LOW)
		, timer(true)
	{};

	void timer_onTimer(TimerEvent* event) {
        led.toggleHighLow();

	}
	

	void setup() {

		timer.delay = 500;
		timer.onTimer = new DelegatingCallback<AppGen, TimerEvent>(this, &AppGen::timer_onTimer); 

	}

	void loop() {
		timer.loop();
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
