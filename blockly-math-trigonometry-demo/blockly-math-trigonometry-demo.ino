#include <Arduino.h>
#include <HardwareSerial.h>
#include <stdbool.h>
#include <FlowerPlatformMathManip.h>

#include <HttpServer.h>
#include <EthernetNetworkAdapter.h>


class AppGen {
public: 
	
	HttpServer httpServer;
	EthernetNetworkAdapter ethernetNetworkAdapter;


	AppGen()
		: httpServer(80)
		, ethernetNetworkAdapter("192.168.100.253", "00:01:02:03:04:08")
	{};

	double testSinFunction(double number) {
        return sin(number);

	}

	double testCosFunction(double number) {
        return cos(number);

	}

	double testTanFunction(double number) {
        return tan(number);

	}

	double testAsinFunction(double number) {
        return asin(number);

	}

	double testAcosFunction(double number) {
        return acos(number);

	}

	double testAtanFunction(double number) {
        return atan(number);

	}

	double testAtan2Function(double number1, double number0) {
        return atan2(number0 , number1);

	}

	double testConvertRadiansToDegreesFunction(double radians_number) {
        return degrees(radians_number);

	}

	double testFormatDecimalNumberFunction(double places, double number) {
        return setPrecision(places, number);

	}


	void httpServer_onCommandReceived(HttpCommandEvent* event) {
		char command[32];
		event->server->getCommandFromUrl(event->url, command);
		bool urlFound = false;
		
		char returnValueBuf[64] = "";
		char *returnValueJson = NULL;
		
		BufferedPrint out(event->client);
		if (strcmp_P(command, PSTR("")) == 0) {
			event->server->httpSuccess(&out, HttpServer::CONTENT_TYPE_HTML, true);
			static const uint8_t HTML_PAGE[] PROGMEM = {
				31,139,8,0,0,0,0,0,0,0,205,88,235,115,219,54,18,255,156,255,2,198,36,49,121,34,41,41,73,51,141,36,42,231,243,185,253,210,78,50,118,50,157,158,235,201,128,36,72,66,2,31,71,128,182,85,13,255,247,91,128,111,89,113,157,235,76,239,60,99,9,143,197,238,98,159,63,104,117,242,207,15,231,159,126,253,120,129,98,153,240,53,90,169,47,148,70,54,201,115,23,151,12,171,37,74,2,248,18,126,193,114,137,68,225,187,56,150,50,23,139,233,148,108,200,189,19,101,89,196,41,201,153,112,252,44,209,107,83,206,60,49,37,105,84,114,82,108,
				196,116,238,188,113,190,107,231,78,194,82,103,35,240,122,53,173,121,126,133,185,31,164,27,96,201,179,50,8,225,24,61,206,221,46,153,237,101,153,20,178,32,57,8,154,59,175,166,195,37,91,230,92,60,69,164,146,152,5,212,217,252,187,164,197,78,11,171,135,54,48,5,174,79,85,59,33,247,160,185,211,41,160,38,138,89,175,228,107,231,181,243,102,10,102,233,150,142,241,230,44,221,162,130,114,23,11,185,227,84,196,148,74,140,226,130,134,223,46,203,23,135,194,96,5,63,65,8,200,208,231,238,136,244,99,205,58,39,57,45,30,97,166,
				207,158,54,103,195,44,149,226,48,64,128,250,125,72,18,198,119,238,101,230,101,50,59,213,26,156,246,26,156,34,185,203,169,123,42,233,189,84,228,167,202,212,106,119,237,196,89,193,126,95,255,109,31,48,145,115,178,91,176,20,164,82,219,227,153,191,93,222,197,76,82,91,228,196,167,139,52,187,3,245,150,9,41,34,150,46,102,149,115,75,11,57,56,40,137,199,233,193,137,34,33,252,224,196,94,125,48,159,112,155,112,22,165,11,153,229,85,173,196,209,29,31,46,76,83,185,87,23,183,5,251,157,46,94,205,243,251,165,158,222,81,22,
				197,114,241,122,54,91,106,157,227,122,14,185,81,129,219,245,245,208,106,218,100,155,151,5,59,228,115,34,132,139,27,166,88,229,165,26,23,25,231,180,112,241,37,56,225,92,22,28,119,145,184,190,37,5,42,153,219,101,90,22,148,156,26,42,145,173,107,248,236,35,5,223,152,75,152,247,236,140,158,29,144,62,23,126,150,83,108,225,231,202,147,234,155,129,14,197,45,225,106,12,198,38,146,101,41,182,194,50,245,213,200,32,86,108,81,43,50,247,74,3,207,53,34,71,80,82,248,177,97,130,76,82,4,159,11,126,226,150,105,64,67,184,122,
				240,254,200,246,2,99,115,169,78,7,46,198,75,226,8,73,100,41,220,125,181,100,161,225,157,192,162,185,15,186,168,196,19,111,130,167,184,34,78,68,229,63,26,22,110,167,14,51,247,5,149,101,145,162,96,194,42,224,230,147,132,242,115,34,232,167,236,19,68,213,47,76,198,87,202,235,162,63,179,173,149,223,184,91,167,160,16,35,62,53,166,198,245,153,253,175,27,115,26,89,24,61,159,55,10,50,119,227,248,49,41,206,164,49,51,29,153,125,206,33,37,20,111,195,156,108,28,193,25,156,156,171,141,159,178,187,118,99,217,168,3,202,
				180,2,81,56,20,201,192,54,247,31,66,3,127,249,210,137,1,59,192,221,55,174,107,207,205,61,115,183,21,229,130,170,129,35,74,15,220,200,210,200,152,89,27,115,130,17,158,12,23,55,147,87,214,214,225,52,141,100,108,86,141,232,71,140,0,246,170,148,72,191,183,134,185,143,149,105,141,145,129,13,12,147,43,112,12,197,166,9,242,124,56,43,140,161,213,59,191,177,206,133,103,226,172,40,200,206,189,190,129,60,40,12,37,103,139,24,152,2,238,20,26,204,137,137,248,112,151,126,44,32,224,10,185,3,155,232,245,45,120,60,44,40,253,
				153,38,248,229,75,53,251,242,229,242,226,234,243,79,159,112,107,52,8,141,141,195,137,7,197,67,153,18,38,16,159,37,117,217,245,246,230,80,186,147,151,34,54,54,102,5,127,102,181,164,134,111,205,103,179,153,9,116,44,189,205,182,116,16,7,214,198,234,227,167,182,194,246,200,109,249,224,182,28,152,86,144,82,15,122,195,35,25,249,32,1,127,164,41,45,152,127,158,37,121,150,66,194,255,137,100,12,44,207,242,149,126,80,112,19,146,6,66,89,63,248,138,67,207,27,154,163,62,13,107,107,131,125,58,239,69,238,108,25,173,104,19,
				95,203,104,50,25,74,186,142,110,148,103,154,169,75,97,174,162,184,153,59,57,41,32,10,65,125,113,112,104,176,227,62,36,174,198,180,41,44,119,84,205,183,114,108,93,213,2,86,80,208,254,22,236,220,236,13,140,83,223,135,40,29,9,36,186,202,24,95,186,248,66,215,28,101,104,119,175,99,106,129,255,142,45,37,71,15,122,77,244,180,142,153,5,126,169,216,98,197,73,210,4,106,134,132,174,181,10,216,173,42,213,12,122,104,119,76,7,33,110,43,122,78,82,202,145,254,180,161,36,146,146,75,188,126,214,252,173,192,206,73,75,169,198,
				182,238,55,16,40,224,112,4,193,66,235,229,254,196,179,86,36,212,45,74,228,64,172,202,179,177,14,8,170,191,191,69,222,14,61,215,37,103,192,165,102,51,20,28,21,89,153,227,230,50,168,103,235,168,254,140,78,92,244,219,41,116,20,232,237,233,111,167,67,70,207,86,218,132,8,152,184,120,191,239,207,41,123,86,21,238,59,27,183,147,192,254,14,169,129,72,154,193,189,208,3,157,24,182,102,132,215,15,153,172,166,122,107,36,117,160,127,195,250,109,203,250,109,203,250,237,72,209,103,43,150,230,165,84,87,132,212,84,64,104,
				108,174,235,218,74,55,117,105,193,53,48,193,10,152,224,145,165,26,117,49,98,193,241,27,235,134,18,103,60,80,157,251,66,229,47,210,44,81,22,162,99,244,211,209,197,166,112,179,245,35,243,99,33,87,59,201,29,59,233,136,123,143,248,237,255,199,61,232,191,242,143,31,83,127,235,101,247,24,105,92,5,215,229,25,145,11,196,105,40,151,144,16,65,0,93,210,6,196,182,64,175,94,32,140,190,193,214,135,211,227,41,115,232,155,70,141,59,22,200,120,241,253,187,23,189,18,74,165,5,154,207,7,75,128,137,101,150,44,94,191,24,187,198,
				43,97,57,109,133,121,50,69,240,95,35,95,61,226,81,123,253,154,178,198,139,128,70,182,46,174,235,85,83,232,13,83,57,76,187,71,249,169,166,126,234,141,87,83,117,205,245,177,189,63,178,197,48,74,79,14,43,227,216,68,239,230,15,76,244,238,15,44,244,87,217,103,124,229,209,36,111,111,215,116,157,75,42,116,101,175,191,23,144,231,163,141,170,2,188,159,175,79,161,123,168,167,83,143,64,2,203,183,60,141,130,188,81,191,108,78,127,236,27,229,112,223,129,135,13,147,6,94,2,178,24,180,206,14,124,181,16,4,92,115,65,0,122,63,
				224,214,247,200,208,162,90,124,216,195,210,5,54,215,10,134,202,24,158,113,26,76,237,149,49,23,97,43,22,8,174,231,55,14,180,211,196,48,235,198,57,218,155,117,123,58,85,1,238,43,204,100,29,106,10,107,10,174,247,207,156,30,255,116,234,129,109,58,16,237,27,181,170,212,237,159,23,45,120,3,17,205,131,226,61,214,144,58,4,228,162,80,140,254,238,16,140,61,95,134,10,195,4,110,48,161,215,97,141,46,38,216,197,245,76,171,59,193,47,113,245,24,65,11,240,131,202,115,70,209,52,132,212,237,150,97,130,103,53,19,127,232,226,
				218,0,71,64,88,160,142,142,98,199,13,156,22,15,107,232,217,138,39,213,8,132,142,42,46,0,8,176,78,97,135,188,100,193,131,215,228,81,244,57,102,81,100,119,248,144,169,46,227,111,80,51,200,194,80,80,105,191,57,32,27,226,157,28,130,128,20,128,67,160,135,218,62,85,157,240,24,181,173,30,194,144,235,120,125,165,33,118,157,105,71,232,212,75,185,101,48,128,64,53,48,87,248,103,244,14,208,111,101,56,184,134,100,172,55,156,38,209,17,19,253,154,118,169,74,254,154,182,21,254,216,215,255,220,78,45,140,255,54,75,33,192,
				117,77,100,41,99,181,32,91,209,181,203,26,108,227,174,120,117,16,165,126,122,169,141,175,190,43,135,71,76,13,131,250,218,53,224,56,192,249,64,163,194,190,45,201,74,143,105,67,246,52,63,60,197,29,173,27,190,127,232,15,29,29,45,93,141,134,244,103,143,211,71,20,17,223,229,49,131,60,66,221,200,14,136,136,245,175,26,250,247,60,29,64,63,192,75,22,37,52,201,192,161,198,213,229,217,207,230,162,15,182,230,153,11,33,232,237,36,21,95,11,58,229,62,253,11,145,250,165,246,63,195,162,55,111,185,21,0,0
			};
			out.write_P(HTML_PAGE, (sizeof(HTML_PAGE)/sizeof(*HTML_PAGE)));
			out.flush();
			return;
		} else if (strcmp_P(command, PSTR("testSinFunction")) == 0) {
			urlFound = true;
			double number = event->server->getDoubleParameterValue(event->url, "number");
			returnValueJson = returnValueBuf;
			dtoa(returnValueJson, testSinFunction(number));
		} else if (strcmp_P(command, PSTR("testCosFunction")) == 0) {
			urlFound = true;
			double number = event->server->getDoubleParameterValue(event->url, "number");
			returnValueJson = returnValueBuf;
			dtoa(returnValueJson, testCosFunction(number));
		} else if (strcmp_P(command, PSTR("testTanFunction")) == 0) {
			urlFound = true;
			double number = event->server->getDoubleParameterValue(event->url, "number");
			returnValueJson = returnValueBuf;
			dtoa(returnValueJson, testTanFunction(number));
		} else if (strcmp_P(command, PSTR("testAsinFunction")) == 0) {
			urlFound = true;
			double number = event->server->getDoubleParameterValue(event->url, "number");
			returnValueJson = returnValueBuf;
			dtoa(returnValueJson, testAsinFunction(number));
		} else if (strcmp_P(command, PSTR("testAcosFunction")) == 0) {
			urlFound = true;
			double number = event->server->getDoubleParameterValue(event->url, "number");
			returnValueJson = returnValueBuf;
			dtoa(returnValueJson, testAcosFunction(number));
		} else if (strcmp_P(command, PSTR("testAtanFunction")) == 0) {
			urlFound = true;
			double number = event->server->getDoubleParameterValue(event->url, "number");
			returnValueJson = returnValueBuf;
			dtoa(returnValueJson, testAtanFunction(number));
		} else if (strcmp_P(command, PSTR("testAtan2Function")) == 0) {
			urlFound = true;
			double number1 = event->server->getDoubleParameterValue(event->url, "number1");
			double number0 = event->server->getDoubleParameterValue(event->url, "number0");
			returnValueJson = returnValueBuf;
			dtoa(returnValueJson, testAtan2Function(number1, number0));
		} else if (strcmp_P(command, PSTR("testConvertRadiansToDegreesFunction")) == 0) {
			urlFound = true;
			double radians_number = event->server->getDoubleParameterValue(event->url, "radians_number");
			returnValueJson = returnValueBuf;
			dtoa(returnValueJson, testConvertRadiansToDegreesFunction(radians_number));
		} else if (strcmp_P(command, PSTR("testFormatDecimalNumberFunction")) == 0) {
			urlFound = true;
			double places = event->server->getDoubleParameterValue(event->url, "places");
			double number = event->server->getDoubleParameterValue(event->url, "number");
			returnValueJson = returnValueBuf;
			dtoa(returnValueJson, testFormatDecimalNumberFunction(places, number));
		} else if (strcmp_P(command, PSTR("getCommands")) == 0) {
			printCommandDescriptorsAsJson(&out);
			out.flush();
			return;
		} else if (strcmp_P(command, PSTR("getState")) == 0) {
			urlFound = true;
		}
		
		if (urlFound) {
			event->server->httpSuccess(&out);
			printStateAsJson(&out, returnValueJson);
		} else {
			event->server->httpError404(&out);
		}
		out.flush();
	}
	
	void printCommandDescriptorsAsJson(Print* print) {
		print->print(F("["));
		print->print(F("{\"command\":\"testSinFunction\", \"parameters\":\"number:double\"}"));
		print->print(F(",{\"command\":\"testCosFunction\", \"parameters\":\"number:double\"}"));
		print->print(F(",{\"command\":\"testTanFunction\", \"parameters\":\"number:double\"}"));
		print->print(F(",{\"command\":\"testAsinFunction\", \"parameters\":\"number:double\"}"));
		print->print(F(",{\"command\":\"testAcosFunction\", \"parameters\":\"number:double\"}"));
		print->print(F(",{\"command\":\"testAtanFunction\", \"parameters\":\"number:double\"}"));
		print->print(F(",{\"command\":\"testAtan2Function\", \"parameters\":\"number1:double;number0:double\"}"));
		print->print(F(",{\"command\":\"testConvertRadiansToDegreesFunction\", \"parameters\":\"radians_number:double\"}"));
		print->print(F(",{\"command\":\"testFormatDecimalNumberFunction\", \"parameters\":\"places:double;number:double\"}"));
		print->print(F("]"));
	}
	
	void printStateAsJson(Print* print, const char* returnValueJson) {
		print->print(F("{"));
	
				
		write_P(print, PSTR("\"freeMem\": "));
		print->print(freeRam());
		
		if (returnValueJson) {
			print->print(F(",\"__RESULT\":"));
			print->print(returnValueJson);
		}

		print->print("}");
	}

	void setup() {
		httpServer.onCommandReceived = new DelegatingCallback<AppGen, HttpCommandEvent>(this, &AppGen::httpServer_onCommandReceived); 

		ethernetNetworkAdapter.protocolHandler = &httpServer;

		ethernetNetworkAdapter.setup();
	}

	void loop() {
		ethernetNetworkAdapter.loop();
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
