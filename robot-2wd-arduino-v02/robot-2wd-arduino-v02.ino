#include <Arduino.h>
#include <HardwareSerial.h>
#include <stdbool.h>

#include <Output.h>
#include <HttpServer.h>
#include <EthernetNetworkAdapter.h>
#include <NewPing.h>
#include <Timer.h>


class AppGen {
public: 
	
	Output M1A;
	Output M1B;
	Output M2A;
	Output M2B;
	HttpServer httpServer;
	EthernetNetworkAdapter ethernetNetworkAdapter1;
	NewPing newPing;
	Timer timer;

	int distance;
	boolean isStopped;
	AppGen() : newPing(8,7,200) {}
			
	void goLeft() {
        M1A.setValue(0);
        M1B.setValue(255);
        M2A.setValue(0);
        M2B.setValue(0);
        delay(1200);
        goFront();
        isStopped = false;

	}

	void goFront() {
        M1A.setValue(0);
        M2A.setValue(0);
        M1B.setValue(255);
        M2B.setValue(255);
        isStopped = false;

	}

	void goBack() {
        M1A.setValue(255);
        M1B.setValue(0);
        M2A.setValue(255);
        M2B.setValue(0);
        isStopped = false;

	}

	void goRight() {
        M1A.setValue(0);
        M1B.setValue(0);
        M2A.setValue(0);
        M2B.setValue(0);
        delay(1200);
        goFront();
        isStopped = false;

	}

	void stop() {
        isStopped = true;
        M1A.setValue(0);
        M1B.setValue(0);
        M2A.setValue(0);
        M2B.setValue(0);

	}

	void avoid() {
        M1A.setValue(255);
        M1B.setValue(0);
        M2A.setValue(255);
        M2B.setValue(0);
        delay(600);
        stop();

	}

	void timer_onTimer(TimerEvent* event) {
        distance = newPing.ping_cm();
        if ( (((distance > 0) && (distance <= 10)) && (isStopped == false)) ) {
            avoid();
        }

	}

	void httpServer_onCommandReceived(HttpCommandEvent* event) {
		char command[32];
		event->server->getCommandFromUrl(event->url, command);
		bool urlFound = false;
		
		BufferedPrint out(event->client);
		if (strcmp_P(command, PSTR("")) == 0) {
			event->server->httpSuccess(&out, HttpServer::CONTENT_TYPE_HTML, true);
			static const uint8_t HTML_PAGE[] PROGMEM = {
				31,139,8,0,0,0,0,0,0,0,205,88,91,115,219,184,21,126,206,191,128,49,201,138,172,72,74,178,211,204,70,18,149,117,189,105,95,118,39,153,36,59,157,214,235,217,1,73,80,132,4,94,10,128,182,181,26,253,247,61,0,239,178,236,56,237,76,91,207,88,194,229,224,220,207,193,7,45,207,126,252,112,245,229,31,31,223,163,68,165,124,133,150,250,11,101,107,151,20,133,143,75,134,245,18,37,17,124,201,80,176,66,33,41,66,31,39,74,21,114,62,153,144,13,185,247,214,121,190,230,148,20,76,122,97,158,154,181,9,103,129,156,144,108,93,114,
				34,54,114,50,243,94,123,127,110,230,94,202,50,111,35,241,106,57,169,120,62,194,60,140,178,13,176,228,121,25,197,112,140,158,230,238,150,204,13,242,92,73,37,72,1,130,102,222,249,164,191,228,170,130,203,231,136,212,18,243,136,122,155,127,149,84,236,140,176,106,232,2,83,224,250,92,181,83,114,15,154,123,173,2,122,162,153,117,74,94,120,23,222,235,9,184,165,93,58,197,155,179,108,139,4,229,62,150,106,199,169,76,40,85,24,37,130,198,223,46,43,148,199,194,96,5,63,67,8,200,48,231,238,136,10,19,195,186,32,5,21,79,48,
				51,103,71,245,217,56,207,148,60,78,16,160,126,23,147,148,241,157,255,41,15,114,149,143,140,6,163,78,131,17,82,187,130,250,35,69,239,149,38,31,105,87,235,221,149,151,228,130,253,190,250,211,62,98,178,224,100,55,103,25,72,165,110,192,243,112,187,184,75,152,162,174,44,72,72,231,89,126,7,234,45,82,34,214,44,155,79,15,222,45,21,170,119,80,145,128,211,163,19,34,37,252,232,196,94,127,176,144,112,151,112,182,206,230,42,47,14,149,18,39,119,66,48,152,102,106,175,13,119,37,251,157,206,207,103,197,253,194,76,239,40,91,
				39,106,126,49,157,46,140,206,73,53,135,218,56,64,216,141,121,104,57,169,171,45,200,163,29,10,57,145,210,199,53,83,172,235,82,143,69,206,57,21,62,254,4,65,184,82,130,227,54,19,87,183,68,160,146,249,109,165,229,81,201,169,165,11,217,185,134,207,46,83,240,141,189,128,121,199,206,234,216,1,233,75,25,230,5,197,14,126,169,35,169,191,25,232,32,110,9,215,99,112,54,81,44,207,176,19,151,89,168,71,22,113,18,135,58,107,123,175,53,8,124,107,237,73,74,68,152,88,54,200,36,34,250,69,240,51,191,204,34,26,131,233,209,187,19,
				219,115,140,237,133,62,29,249,24,47,136,39,21,81,165,244,247,135,5,139,173,224,12,22,237,125,212,102,37,30,7,99,60,193,7,226,173,169,250,75,205,194,111,213,97,246,94,80,85,138,12,69,99,118,0,110,33,73,41,191,34,146,126,201,191,64,86,253,157,169,228,179,142,186,236,206,108,43,229,55,254,214,19,20,114,36,164,214,196,186,190,116,255,121,99,79,214,14,70,47,103,181,130,204,223,120,97,66,196,165,178,166,182,167,242,95,10,40,9,205,219,178,199,27,79,114,6,39,103,122,227,167,252,174,217,88,212,234,128,50,141,64,20,
				247,69,50,240,205,253,135,216,194,191,253,214,138,1,63,128,237,27,223,119,103,246,158,249,219,3,229,146,234,129,39,203,0,194,200,178,181,53,117,54,246,24,35,60,238,47,110,198,231,206,214,227,52,91,171,196,62,212,162,159,112,2,248,235,160,69,134,157,55,236,125,162,93,107,13,28,108,97,152,124,134,192,80,108,219,32,47,132,179,210,234,123,189,141,27,107,67,120,41,47,133,32,59,255,250,6,234,64,88,90,206,22,49,112,5,216,20,91,204,75,136,252,112,151,125,20,144,112,66,237,192,39,102,125,11,17,143,5,165,63,211,20,
				55,94,130,92,216,120,156,4,208,45,180,239,96,2,9,89,82,159,93,111,111,142,197,121,69,41,19,107,99,31,224,207,62,44,168,21,58,179,233,116,106,3,29,203,110,243,45,237,5,222,217,56,172,177,119,123,194,46,222,179,139,3,183,3,20,207,131,91,224,137,218,123,80,106,127,163,25,21,44,188,202,211,34,207,160,180,255,131,178,139,156,192,9,181,126,208,90,83,146,69,82,251,57,122,36,116,63,210,74,215,92,200,147,1,164,154,81,212,17,249,180,13,89,236,79,23,241,114,176,219,138,172,51,109,17,143,199,125,77,174,227,27,29,178,
				122,234,159,62,11,68,58,201,235,169,87,16,1,73,10,54,75,123,95,175,125,108,151,252,135,84,30,116,115,166,44,188,192,58,178,61,166,61,26,237,145,38,42,96,206,123,2,125,231,1,239,206,167,137,110,99,42,129,219,202,164,208,94,223,69,243,164,17,52,199,246,245,236,198,131,58,75,45,219,201,224,244,112,111,218,238,153,220,132,174,6,9,227,60,166,154,125,24,238,104,126,173,149,245,247,145,93,85,254,55,52,102,166,51,188,234,231,17,19,20,172,184,133,188,171,41,122,201,82,149,17,209,49,33,208,226,116,175,8,149,143,223,
				155,110,171,19,207,223,27,118,115,252,3,174,44,211,131,78,89,51,173,138,103,142,191,211,108,177,230,164,104,10,221,82,193,125,189,140,216,173,190,164,24,160,135,246,152,169,70,220,220,101,5,201,40,71,230,211,133,203,128,148,92,225,213,139,250,111,9,209,73,27,74,61,118,205,77,11,133,3,5,128,160,120,104,181,220,157,120,209,136,132,142,77,137,234,137,213,29,102,168,3,130,123,47,220,162,96,135,94,154,102,219,227,82,177,233,11,94,139,188,44,112,109,12,234,216,122,58,27,208,153,143,126,29,193,93,10,168,38,251,
				117,212,103,244,98,105,92,136,128,137,143,247,251,238,156,246,231,225,128,187,59,157,187,105,228,94,32,61,144,169,123,110,6,247,210,12,76,163,112,13,35,188,122,200,100,57,49,91,3,169,61,253,107,214,111,26,214,111,26,214,111,6,138,190,88,178,172,40,149,54,17,90,149,134,128,67,119,93,87,94,186,169,122,44,174,32,25,214,144,12,15,60,85,171,139,17,139,78,91,108,174,210,36,231,145,198,44,239,117,63,67,134,37,202,99,116,138,126,50,48,108,2,150,173,158,152,159,74,185,42,72,254,48,72,39,194,123,34,110,255,63,225,65,
				255,86,124,194,132,134,219,32,191,199,200,32,74,48,151,231,68,205,17,167,177,90,64,65,68,17,224,3,23,176,234,28,157,191,66,24,125,131,175,143,167,167,75,230,56,54,181,26,119,44,82,201,252,251,183,175,58,37,180,74,115,52,155,245,150,224,53,160,242,116,126,241,106,24,154,160,132,229,172,17,22,168,12,193,127,133,249,205,136,175,27,243,43,202,10,41,3,14,219,250,184,234,87,87,85,51,180,108,29,176,186,103,46,39,21,245,115,45,94,78,180,153,171,83,123,95,243,69,63,75,207,142,59,227,208,69,111,103,15,92,244,246,43,
				30,250,111,249,103,104,178,153,140,160,255,235,103,95,7,166,34,39,116,2,131,224,130,175,92,230,193,35,215,120,239,122,111,129,227,55,92,223,177,67,31,94,223,241,19,215,119,252,245,235,251,88,37,128,128,230,86,110,223,98,29,116,107,245,0,39,180,72,63,212,200,10,92,66,253,238,13,212,188,80,64,66,253,234,121,135,23,45,210,2,212,85,33,46,90,131,43,119,86,193,171,200,143,198,180,129,10,99,236,227,106,102,180,29,227,239,240,225,41,130,230,21,18,29,2,111,16,248,62,238,111,182,44,27,66,104,152,132,253,88,86,14,208,
				32,184,225,70,14,3,56,60,232,117,112,117,131,177,194,141,121,201,162,7,47,216,147,56,120,200,66,228,119,248,152,169,105,160,175,81,61,200,227,88,82,229,190,62,34,235,35,141,2,66,74,4,32,0,184,189,220,144,234,59,232,20,181,171,31,223,80,101,120,245,217,128,253,42,199,79,208,233,215,121,195,160,7,62,170,39,130,70,30,131,167,136,121,159,195,193,21,92,119,213,70,3,219,16,147,221,154,137,144,46,187,138,182,17,254,212,215,255,220,79,117,250,124,163,167,16,32,170,186,130,181,179,78,61,11,244,153,134,196,128,98,
				128,22,71,184,88,99,133,10,12,235,189,71,159,182,3,164,108,27,64,210,245,160,30,215,110,85,211,232,122,104,154,163,214,101,82,147,61,47,46,207,9,79,19,150,239,31,198,199,100,75,67,87,225,18,243,217,33,230,1,197,154,239,138,132,65,93,161,118,228,70,68,38,230,151,21,243,155,162,73,168,191,194,107,26,165,52,205,33,192,214,231,79,151,63,219,243,46,249,234,167,54,164,100,176,83,84,62,150,132,58,156,230,87,42,253,107,241,31,132,173,33,86,61,22,0,0
			};
			out.write_P(HTML_PAGE, (sizeof(HTML_PAGE)/sizeof(*HTML_PAGE)));
			out.flush();
			return;
		} else if (strcmp_P(command, PSTR("goLeft")) == 0) {
			urlFound = true;
			goLeft();
		} else if (strcmp_P(command, PSTR("goFront")) == 0) {
			urlFound = true;
			goFront();
		} else if (strcmp_P(command, PSTR("goBack")) == 0) {
			urlFound = true;
			goBack();
		} else if (strcmp_P(command, PSTR("goRight")) == 0) {
			urlFound = true;
			goRight();
		} else if (strcmp_P(command, PSTR("stop")) == 0) {
			urlFound = true;
			stop();
		} else if (strcmp_P(command, PSTR("getDescriptors")) == 0) {
			printDescriptorsAsJson(&out);
			out.flush();
			return;
		} else if (strcmp_P(command, PSTR("getState")) == 0) {
			urlFound = true;
		}
		
		if (urlFound) {
			event->server->httpSuccess(&out);
			printStateAsJson(&out);
		} else {
			event->server->httpError404(&out);
		}
		out.flush();
	}
	
	void printDescriptorsAsJson(Print* print) {
		print->print(F("{\"inputs\":["));

		print->print(F("],\"commands\":["));
		print->print(F("{\"label\":\"goLeft\", \"command\":\"goLeft\", \"parameters\":\"\"}"));
		print->print(F(",{\"label\":\"goFront\", \"command\":\"goFront\", \"parameters\":\"\"}"));
		print->print(F(",{\"label\":\"goBack\", \"command\":\"goBack\", \"parameters\":\"\"}"));
		print->print(F(",{\"label\":\"goRight\", \"command\":\"goRight\", \"parameters\":\"\"}"));
		print->print(F(",{\"label\":\"stop\", \"command\":\"stop\", \"parameters\":\"\"}"));
		
		print->print(F("]}"));

	}
	
	void printStateAsJson(Print* print) {
		print->print(F("{"));
	
		write_P(print, PSTR("\"freeMem\": "));
		print->print(freeRam());
		print->print("}");
	}

	void setup() {
		M1A.pin = 3;
		M1A.initialValue = 0;
		M1A.isPwm = true;

		M1B.pin = 5;
		M1B.initialValue = 0;
		M1B.isPwm = true;

		M2A.pin = 6;
		M2A.initialValue = 0;
		M2A.isPwm = true;

		M2B.pin = 9;
		M2B.initialValue = 0;
		M2B.isPwm = true;

		httpServer.port = 80;
		httpServer.onCommandReceived = new DelegatingCallback<AppGen, HttpCommandEvent>(this, &AppGen::httpServer_onCommandReceived); 

		ethernetNetworkAdapter1.macAddressStr = "00:0a:95:9d:68:16";
		ethernetNetworkAdapter1.protocolHandler = &httpServer;
		ethernetNetworkAdapter1.ipAddressStr = "192.168.100.252";


		timer.delay = 20;
		timer.autoStart = true;
		timer.onTimer = new DelegatingCallback<AppGen, TimerEvent>(this, &AppGen::timer_onTimer); 

		M1A.setup();
		M1B.setup();
		M2A.setup();
		M2B.setup();
		ethernetNetworkAdapter1.setup();
		timer.setup();
	}

	void loop() {
		M1A.loop();
		M1B.loop();
		M2A.loop();
		M2B.loop();
		ethernetNetworkAdapter1.loop();
		timer.loop();
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
