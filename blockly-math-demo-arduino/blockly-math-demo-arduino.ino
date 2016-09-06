#include <Arduino.h>
#include <HardwareSerial.h>
#include <stdbool.h>
#include <FlowerPlatformMathManip.h>
#include <FlowerPlatformStringManip.h>

#include <EthernetNetworkAdapter.h>
#include <HttpServer.h>


class AppGen {
public: 
	
	EthernetNetworkAdapter ethernetNetworkAdapter;
	HttpServer httpServer;


	AppGen()
		: ethernetNetworkAdapter("192.168.100.253", "00:01:02:03:04:05")
		, httpServer(80)
	{};

	int testAddFunction(int num0, int num1, int num2) {
        return (num0 + num1 + num2);

	}

	int testSubstractFunction(int num0, int num1) {
        return (num0 - num1);

	}

	int testMultiplyFunction(int num0, int num1, int num2) {
        return (num0 * num1 * num2);

	}

	int testDivisionFunction(int num0, int num1) {
        return (num0 / num1);

	}

	int testPowFunction(int num0, int num1) {
        return powint(num0, num1);

	}

	String testComparisonFunction(int num0, int num1) {
        if ( (num0 == num1)) {
            return "num0 = num1";
        } else if ( (num0 < num1)) {
            return "num0 < num1";
        } else {
            return "num0 > num1";
        }

	}

	int testRandomIntegerFunction(int from, int to) {
        return rand() % (from - to) + from;

	}

	int testMinFunction(int num0, int num1, int num2) {
        return min_array(3, num0, num1, num2);

	}

	double testRandomFractionFunction() {
        return  static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

	}

	double testSquareRootFunction(int number) {
        return sqrt(number);

	}

	int testMaxFunction(int num0, int num1, int num2) {
        return max_array(3, num0, num1, num2);

	}

	int testNegFunction(int number) {
        return -(number);

	}

	int testAbsoluteFunction(int number) {
        return abs(number);

	}

	double testLogFunction(int number) {
        return log(number);

	}

	double testExpFunction(int number) {
        return exp(number);

	}

	int testRoundFunction(double number) {
        return round(number);

	}

	int testCeilingFunction(double number) {
        return ceil(number);

	}

	double testFloorFunction(double number) {
        return floor(number);

	}

	int testRemainderFunction(int dividend, int divisor) {
        return (dividend % divisor);

	}

	int testConvertHexToBase10Function(String hex) {
        return hexToBase10(hex);

	}

	int testConvertBinaryToBase10Function(String binary) {
        return binaryToBase10(binary);

	}

	String testConverBase10ToHexFunction(int base_10) {
        return hex(base_10);

	}

	String testConverBase10ToBinary0Function(int base_10) {
        return bin(base_10);

	}

	int testQuotientFunction(int dividend, int divisor) {
        return (dividend / divisor);

	}


	void httpServer_onCommandReceived(HttpCommandEvent* event) {
		char command[64];
		event->server->getCommandFromUrl(event->url, command);
		bool urlFound = false;
		
		char returnValueBuf[64] = "";
		char *returnValueJson = NULL;
		
		BufferedPrint out(event->client);
		if (strcmp_P(command, PSTR("")) == 0) {
			event->server->httpSuccess(&out, HttpServer::CONTENT_TYPE_HTML, true);
			static const uint8_t HTML_PAGE[] PROGMEM = {
				31,139,8,0,0,0,0,0,0,0,205,88,89,111,219,72,18,126,206,191,104,55,156,136,92,137,148,101,39,193,68,18,149,241,100,179,243,50,65,130,28,88,236,58,70,208,34,155,100,75,188,166,217,180,173,17,248,223,167,170,121,203,138,199,193,2,187,107,192,34,251,170,187,170,191,226,242,228,239,239,223,124,254,215,135,183,36,84,113,180,34,75,124,144,36,176,88,150,57,180,16,20,167,56,243,224,145,187,82,100,138,228,210,117,104,168,84,150,207,167,83,182,97,119,118,144,166,65,196,89,38,114,219,77,99,61,55,141,196,58,159,178,36,
				40,34,38,55,249,116,102,63,183,95,52,99,59,22,137,189,201,233,106,57,173,104,126,135,184,235,37,27,32,25,165,133,231,195,49,126,156,186,85,8,107,157,166,42,87,146,101,192,104,102,159,79,251,83,150,202,162,252,49,44,145,99,234,113,123,243,123,193,229,78,51,171,94,45,32,10,84,31,43,118,204,238,64,114,187,21,0,7,72,172,19,242,194,190,176,159,79,193,44,237,212,49,218,145,72,182,68,242,200,161,185,218,69,60,15,57,87,148,132,146,251,63,206,203,205,15,153,193,12,125,4,19,224,161,207,221,50,229,134,154,116,198,50,
				46,31,32,166,207,142,234,179,126,154,168,252,48,64,96,247,107,159,197,34,218,57,31,211,117,170,210,145,150,96,212,73,48,34,106,151,113,103,164,248,157,194,237,35,52,53,174,174,236,48,149,226,143,213,223,246,158,200,179,136,237,230,34,1,174,220,90,71,169,187,93,220,134,66,113,43,207,152,203,231,73,122,11,226,45,98,38,3,145,204,207,74,251,134,75,213,59,168,216,58,226,7,39,100,204,162,131,19,123,252,17,46,139,44,22,137,32,153,171,52,43,43,33,142,174,184,160,48,79,212,30,21,183,114,241,7,159,159,207,178,187,
				133,30,222,114,17,132,106,126,113,118,182,208,50,135,213,24,114,163,4,183,107,245,200,114,90,103,219,58,245,118,196,141,88,158,59,180,38,74,49,47,241,93,166,81,196,165,67,63,130,19,222,40,25,209,54,18,87,55,76,146,66,56,109,166,165,94,17,113,3,19,121,114,5,191,93,164,208,107,115,1,99,32,231,139,192,184,162,167,96,64,166,68,154,124,144,233,141,240,184,164,19,191,72,92,156,49,152,185,103,54,22,134,23,239,32,65,140,61,79,208,118,222,92,201,130,79,36,255,189,16,146,255,194,114,62,247,89,148,243,210,44,91,218,
				181,168,70,39,42,136,113,154,187,105,198,233,132,158,98,148,224,83,128,126,242,134,69,248,222,200,209,231,63,9,39,124,18,152,123,212,110,237,24,129,157,115,38,221,208,48,65,31,38,189,47,50,58,113,138,196,227,62,152,213,123,125,100,121,78,169,185,192,211,158,67,233,130,217,185,98,170,200,157,125,185,16,190,177,62,129,73,115,239,181,17,79,199,235,49,157,210,146,217,1,87,191,212,36,156,86,28,97,238,37,87,133,76,136,55,22,37,80,115,89,204,163,55,96,128,207,233,103,136,216,127,10,21,126,194,136,202,187,51,219,
				74,248,141,179,181,37,135,248,115,185,49,53,174,46,173,127,95,155,211,96,66,201,233,172,22,80,56,27,219,13,153,188,84,198,153,105,171,244,75,6,233,134,180,13,115,188,177,243,72,192,201,25,46,252,150,222,54,11,139,90,28,16,166,97,72,252,62,75,1,182,185,123,239,27,244,219,183,150,13,216,1,116,223,56,142,53,51,247,194,217,150,28,124,135,47,118,94,172,33,68,68,18,24,103,147,141,57,166,132,142,251,147,155,241,249,100,107,71,60,9,84,104,150,53,235,7,140,0,246,42,145,165,219,89,195,220,135,104,90,99,96,96,131,194,
				224,19,56,134,83,211,4,126,46,156,205,141,190,213,91,191,137,214,133,151,249,165,148,108,231,92,93,67,142,73,3,249,108,137,0,83,128,78,190,33,236,144,229,239,111,49,166,193,138,106,7,54,209,243,91,240,184,47,57,127,199,99,250,236,25,142,190,125,251,248,246,211,151,223,62,211,198,104,16,26,27,59,98,107,40,76,104,74,24,64,124,22,220,17,87,219,235,67,238,118,86,228,161,177,49,75,248,51,203,5,55,220,201,236,236,236,204,132,125,34,185,73,183,188,23,7,147,205,164,139,159,99,86,216,30,83,62,234,41,31,1,15,204,176,
				123,215,208,3,201,127,47,31,127,229,9,151,194,125,147,198,89,154,64,109,249,15,114,211,155,172,39,46,202,7,181,61,102,137,151,163,51,188,239,248,247,77,189,231,168,139,253,202,248,96,174,214,153,129,115,182,8,150,188,14,183,69,48,30,247,57,93,5,215,232,168,122,232,112,24,99,80,215,99,59,99,18,130,18,196,207,15,14,245,86,156,251,155,203,225,222,4,166,219,93,245,179,108,139,156,7,181,15,164,191,1,59,215,107,61,227,84,250,48,148,145,65,222,99,2,185,202,161,111,117,9,66,67,59,123,29,98,115,250,51,157,32,31,253,
				210,73,162,135,85,8,205,233,51,36,75,145,146,226,49,148,16,5,23,228,210,19,55,120,43,8,184,174,219,99,58,38,105,115,121,100,44,225,17,209,191,22,84,72,86,68,138,174,158,212,127,205,121,48,119,12,41,1,191,179,246,32,142,44,125,211,65,220,128,255,245,237,83,45,237,191,142,32,177,44,46,101,42,191,142,230,68,31,236,44,104,159,234,21,27,208,73,229,183,178,227,216,178,132,50,200,153,234,137,141,105,59,212,129,192,69,229,110,201,122,71,78,117,5,235,81,169,200,244,37,13,100,90,100,180,54,6,233,200,218,8,37,200,137,
				67,190,142,224,242,3,24,146,124,29,245,9,61,89,106,23,160,14,160,216,190,59,135,254,40,75,218,93,194,145,21,123,214,11,130,47,121,92,191,220,229,250,69,39,150,165,9,209,213,125,34,203,169,94,26,112,237,201,95,147,126,217,144,126,217,144,126,57,16,244,201,82,36,89,161,136,14,200,78,65,173,51,228,58,130,184,161,253,174,42,179,93,87,165,139,86,160,138,34,168,26,58,185,150,159,18,225,29,55,1,50,104,124,233,208,139,115,74,244,21,22,166,145,135,56,228,45,150,8,162,153,144,212,39,199,40,76,135,138,244,148,15,121,
				148,85,240,173,226,3,21,129,5,188,22,237,126,80,233,77,121,152,222,58,244,228,222,14,16,65,120,148,128,46,160,39,131,66,7,161,190,204,136,198,86,72,176,193,100,100,246,2,64,25,241,163,148,169,57,145,8,195,40,89,189,99,119,34,46,98,114,113,78,240,6,102,46,166,32,97,81,4,55,173,119,178,156,102,128,206,65,240,129,23,15,38,238,141,143,229,103,21,145,206,48,34,143,196,242,145,32,253,255,137,69,210,4,227,15,197,158,27,114,119,187,78,239,104,235,147,202,5,17,247,213,2,178,223,243,0,97,88,128,164,231,228,252,41,1,
				159,60,222,214,135,195,227,245,225,208,55,181,24,183,194,83,225,252,167,87,79,59,33,80,36,8,148,89,111,10,122,21,149,198,243,139,167,67,215,172,11,152,78,26,102,107,149,16,248,175,66,90,191,69,65,163,126,181,179,174,164,194,221,58,180,42,238,245,173,104,152,232,48,237,30,244,83,181,251,177,26,15,70,195,193,95,152,162,31,164,39,135,183,200,208,66,175,102,247,44,244,234,47,12,244,223,50,207,3,250,103,141,118,245,13,253,145,231,250,22,172,158,115,40,88,131,133,178,36,152,236,35,184,105,177,163,237,192,155,55,
				113,39,107,13,32,215,3,108,81,159,254,208,129,138,254,186,13,253,166,80,6,93,0,10,235,193,140,22,183,54,112,13,92,243,150,65,215,114,143,90,135,39,252,9,215,236,253,14,209,207,169,185,66,4,175,66,232,174,53,14,221,163,49,231,126,195,22,54,92,205,174,109,128,30,177,97,86,32,99,176,118,214,174,233,76,133,78,9,241,229,228,80,82,152,195,78,167,235,62,59,172,216,138,7,182,105,251,15,215,168,68,229,78,215,153,53,184,23,88,212,189,216,107,170,187,17,31,80,30,34,62,253,108,209,158,53,91,248,136,247,60,199,27,243,
				43,191,66,98,99,234,208,106,164,197,29,211,103,180,124,104,67,211,27,121,229,218,30,68,83,191,27,105,150,12,19,60,171,137,184,125,23,87,6,56,2,88,61,60,58,136,29,199,179,155,86,66,195,244,134,61,43,7,128,125,80,112,1,93,129,117,164,229,71,5,222,94,7,77,254,81,164,62,36,33,211,91,122,72,84,87,241,231,164,126,73,125,63,231,202,122,126,176,173,143,13,51,8,2,38,1,115,1,60,176,92,142,87,250,177,221,22,126,159,128,92,167,171,79,186,29,169,50,237,200,62,252,128,209,16,232,193,189,170,137,65,172,55,104,161,244,39,
				12,56,184,130,100,172,22,236,58,209,137,200,187,57,237,82,76,254,106,111,195,252,161,199,255,220,78,77,203,243,99,150,34,128,97,235,200,66,99,53,13,9,238,107,166,43,28,216,22,175,22,107,85,93,43,46,124,183,37,239,31,49,241,76,175,33,234,81,236,245,68,176,7,195,190,41,201,40,199,180,222,246,56,63,60,198,29,141,27,126,186,239,15,29,29,205,190,10,12,233,223,174,167,25,236,8,162,93,22,10,200,35,210,190,89,30,203,67,253,65,72,127,102,213,1,244,15,201,57,137,121,156,130,67,141,79,31,47,223,153,243,46,216,234,47,
				4,16,130,235,157,226,249,247,130,14,221,167,63,220,225,7,244,63,1,20,216,167,2,80,23,0,0
			};
			out.write_P(HTML_PAGE, (sizeof(HTML_PAGE)/sizeof(*HTML_PAGE)));
			out.flush();
			return;
		} else if (strcmp_P(command, PSTR("testAddFunction")) == 0) {
			urlFound = true;
			int num0 = event->server->getIntParameterValue(event->url, "num0");
			int num1 = event->server->getIntParameterValue(event->url, "num1");
			int num2 = event->server->getIntParameterValue(event->url, "num2");
			returnValueJson = returnValueBuf;
			itoa(testAddFunction(num0, num1, num2), returnValueJson, 10);
		} else if (strcmp_P(command, PSTR("testSubstractFunction")) == 0) {
			urlFound = true;
			int num0 = event->server->getIntParameterValue(event->url, "num0");
			int num1 = event->server->getIntParameterValue(event->url, "num1");
			returnValueJson = returnValueBuf;
			itoa(testSubstractFunction(num0, num1), returnValueJson, 10);
		} else if (strcmp_P(command, PSTR("testMultiplyFunction")) == 0) {
			urlFound = true;
			int num0 = event->server->getIntParameterValue(event->url, "num0");
			int num1 = event->server->getIntParameterValue(event->url, "num1");
			int num2 = event->server->getIntParameterValue(event->url, "num2");
			returnValueJson = returnValueBuf;
			itoa(testMultiplyFunction(num0, num1, num2), returnValueJson, 10);
		} else if (strcmp_P(command, PSTR("testDivisionFunction")) == 0) {
			urlFound = true;
			int num0 = event->server->getIntParameterValue(event->url, "num0");
			int num1 = event->server->getIntParameterValue(event->url, "num1");
			returnValueJson = returnValueBuf;
			itoa(testDivisionFunction(num0, num1), returnValueJson, 10);
		} else if (strcmp_P(command, PSTR("testPowFunction")) == 0) {
			urlFound = true;
			int num0 = event->server->getIntParameterValue(event->url, "num0");
			int num1 = event->server->getIntParameterValue(event->url, "num1");
			returnValueJson = returnValueBuf;
			itoa(testPowFunction(num0, num1), returnValueJson, 10);
		} else if (strcmp_P(command, PSTR("testComparisonFunction")) == 0) {
			urlFound = true;
			int num0 = event->server->getIntParameterValue(event->url, "num0");
			int num1 = event->server->getIntParameterValue(event->url, "num1");
			returnValueJson = returnValueBuf;
			strcat(returnValueJson, "\"");
			strcat(returnValueJson, testComparisonFunction(num0, num1).c_str());
			strcat(returnValueJson, "\"");
		} else if (strcmp_P(command, PSTR("testRandomIntegerFunction")) == 0) {
			urlFound = true;
			int from = event->server->getIntParameterValue(event->url, "from");
			int to = event->server->getIntParameterValue(event->url, "to");
			returnValueJson = returnValueBuf;
			itoa(testRandomIntegerFunction(from, to), returnValueJson, 10);
		} else if (strcmp_P(command, PSTR("testMinFunction")) == 0) {
			urlFound = true;
			int num0 = event->server->getIntParameterValue(event->url, "num0");
			int num1 = event->server->getIntParameterValue(event->url, "num1");
			int num2 = event->server->getIntParameterValue(event->url, "num2");
			returnValueJson = returnValueBuf;
			itoa(testMinFunction(num0, num1, num2), returnValueJson, 10);
		} else if (strcmp_P(command, PSTR("testRandomFractionFunction")) == 0) {
			urlFound = true;
			returnValueJson = returnValueBuf;
			dtoa(returnValueJson, testRandomFractionFunction());
		} else if (strcmp_P(command, PSTR("testSquareRootFunction")) == 0) {
			urlFound = true;
			int number = event->server->getIntParameterValue(event->url, "number");
			returnValueJson = returnValueBuf;
			dtoa(returnValueJson, testSquareRootFunction(number));
		} else if (strcmp_P(command, PSTR("testMaxFunction")) == 0) {
			urlFound = true;
			int num0 = event->server->getIntParameterValue(event->url, "num0");
			int num1 = event->server->getIntParameterValue(event->url, "num1");
			int num2 = event->server->getIntParameterValue(event->url, "num2");
			returnValueJson = returnValueBuf;
			itoa(testMaxFunction(num0, num1, num2), returnValueJson, 10);
		} else if (strcmp_P(command, PSTR("testNegFunction")) == 0) {
			urlFound = true;
			int number = event->server->getIntParameterValue(event->url, "number");
			returnValueJson = returnValueBuf;
			itoa(testNegFunction(number), returnValueJson, 10);
		} else if (strcmp_P(command, PSTR("testAbsoluteFunction")) == 0) {
			urlFound = true;
			int number = event->server->getIntParameterValue(event->url, "number");
			returnValueJson = returnValueBuf;
			itoa(testAbsoluteFunction(number), returnValueJson, 10);
		} else if (strcmp_P(command, PSTR("testLogFunction")) == 0) {
			urlFound = true;
			int number = event->server->getIntParameterValue(event->url, "number");
			returnValueJson = returnValueBuf;
			dtoa(returnValueJson, testLogFunction(number));
		} else if (strcmp_P(command, PSTR("testExpFunction")) == 0) {
			urlFound = true;
			int number = event->server->getIntParameterValue(event->url, "number");
			returnValueJson = returnValueBuf;
			dtoa(returnValueJson, testExpFunction(number));
		} else if (strcmp_P(command, PSTR("testRoundFunction")) == 0) {
			urlFound = true;
			double number = event->server->getDoubleParameterValue(event->url, "number");
			returnValueJson = returnValueBuf;
			itoa(testRoundFunction(number), returnValueJson, 10);
		} else if (strcmp_P(command, PSTR("testCeilingFunction")) == 0) {
			urlFound = true;
			double number = event->server->getDoubleParameterValue(event->url, "number");
			returnValueJson = returnValueBuf;
			itoa(testCeilingFunction(number), returnValueJson, 10);
		} else if (strcmp_P(command, PSTR("testFloorFunction")) == 0) {
			urlFound = true;
			double number = event->server->getDoubleParameterValue(event->url, "number");
			returnValueJson = returnValueBuf;
			dtoa(returnValueJson, testFloorFunction(number));
		} else if (strcmp_P(command, PSTR("testRemainderFunction")) == 0) {
			urlFound = true;
			int dividend = event->server->getIntParameterValue(event->url, "dividend");
			int divisor = event->server->getIntParameterValue(event->url, "divisor");
			returnValueJson = returnValueBuf;
			itoa(testRemainderFunction(dividend, divisor), returnValueJson, 10);
		} else if (strcmp_P(command, PSTR("testConvertHexToBase10Function")) == 0) {
			urlFound = true;
			char hexBuf[32];
			event->server->getStringParameterValue(event->url, "hex", hexBuf);
			String hex = hexBuf;
			returnValueJson = returnValueBuf;
			itoa(testConvertHexToBase10Function(hex), returnValueJson, 10);
		} else if (strcmp_P(command, PSTR("testConvertBinaryToBase10Function")) == 0) {
			urlFound = true;
			char binaryBuf[32];
			event->server->getStringParameterValue(event->url, "binary", binaryBuf);
			String binary = binaryBuf;
			returnValueJson = returnValueBuf;
			itoa(testConvertBinaryToBase10Function(binary), returnValueJson, 10);
		} else if (strcmp_P(command, PSTR("testConverBase10ToHexFunction")) == 0) {
			urlFound = true;
			int base_10 = event->server->getIntParameterValue(event->url, "base_10");
			returnValueJson = returnValueBuf;
			strcat(returnValueJson, "\"");
			strcat(returnValueJson, testConverBase10ToHexFunction(base_10).c_str());
			strcat(returnValueJson, "\"");
		} else if (strcmp_P(command, PSTR("testConverBase10ToBinary0Function")) == 0) {
			urlFound = true;
			int base_10 = event->server->getIntParameterValue(event->url, "base_10");
			returnValueJson = returnValueBuf;
			strcat(returnValueJson, "\"");
			strcat(returnValueJson, testConverBase10ToBinary0Function(base_10).c_str());
			strcat(returnValueJson, "\"");
		} else if (strcmp_P(command, PSTR("testQuotientFunction")) == 0) {
			urlFound = true;
			int dividend = event->server->getIntParameterValue(event->url, "dividend");
			int divisor = event->server->getIntParameterValue(event->url, "divisor");
			returnValueJson = returnValueBuf;
			itoa(testQuotientFunction(dividend, divisor), returnValueJson, 10);
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
		print->print(F("{\"command\":\"testAddFunction\", \"parameters\":\"num0:int;num1:int;num2:int\"}"));
		print->print(F(",{\"command\":\"testSubstractFunction\", \"parameters\":\"num0:int;num1:int\"}"));
		print->print(F(",{\"command\":\"testMultiplyFunction\", \"parameters\":\"num0:int;num1:int;num2:int\"}"));
		print->print(F(",{\"command\":\"testDivisionFunction\", \"parameters\":\"num0:int;num1:int\"}"));
		print->print(F(",{\"command\":\"testPowFunction\", \"parameters\":\"num0:int;num1:int\"}"));
		print->print(F(",{\"command\":\"testComparisonFunction\", \"parameters\":\"num0:int;num1:int\"}"));
		print->print(F(",{\"command\":\"testRandomIntegerFunction\", \"parameters\":\"from:int;to:int\"}"));
		print->print(F(",{\"command\":\"testMinFunction\", \"parameters\":\"num0:int;num1:int;num2:int\"}"));
		print->print(F(",{\"command\":\"testRandomFractionFunction\", \"parameters\":\"\"}"));
		print->print(F(",{\"command\":\"testSquareRootFunction\", \"parameters\":\"number:int\"}"));
		print->print(F(",{\"command\":\"testMaxFunction\", \"parameters\":\"num0:int;num1:int;num2:int\"}"));
		print->print(F(",{\"command\":\"testNegFunction\", \"parameters\":\"number:int\"}"));
		print->print(F(",{\"command\":\"testAbsoluteFunction\", \"parameters\":\"number:int\"}"));
		print->print(F(",{\"command\":\"testLogFunction\", \"parameters\":\"number:int\"}"));
		print->print(F(",{\"command\":\"testExpFunction\", \"parameters\":\"number:int\"}"));
		print->print(F(",{\"command\":\"testRoundFunction\", \"parameters\":\"number:double\"}"));
		print->print(F(",{\"command\":\"testCeilingFunction\", \"parameters\":\"number:double\"}"));
		print->print(F(",{\"command\":\"testFloorFunction\", \"parameters\":\"number:double\"}"));
		print->print(F(",{\"command\":\"testRemainderFunction\", \"parameters\":\"dividend:int;divisor:int\"}"));
		print->print(F(",{\"command\":\"testConvertHexToBase10Function\", \"parameters\":\"hex:String\"}"));
		print->print(F(",{\"command\":\"testConvertBinaryToBase10Function\", \"parameters\":\"binary:String\"}"));
		print->print(F(",{\"command\":\"testConverBase10ToHexFunction\", \"parameters\":\"base_10:int\"}"));
		print->print(F(",{\"command\":\"testConverBase10ToBinary0Function\", \"parameters\":\"base_10:int\"}"));
		print->print(F(",{\"command\":\"testQuotientFunction\", \"parameters\":\"dividend:int;divisor:int\"}"));
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
		ethernetNetworkAdapter.protocolHandler = &httpServer;

		httpServer.onCommandReceived = new DelegatingCallback<AppGen, HttpCommandEvent>(this, &AppGen::httpServer_onCommandReceived); 

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
