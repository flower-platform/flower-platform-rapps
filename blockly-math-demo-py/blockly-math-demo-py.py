#!/usr/bin/python

import os
import signal
import sys
import time
import RPi.GPIO as GPIO
from math import sqrt, sin, cos, tan, asin, acos, atan, atan2, degrees, radians



class AppGen :

	def testAddFunction(self, num0, num1, num2) :
		return (num0 + num1 + num2)


	def testSubstractFunction(self, num0, num1) :
		return (num0 - num1)


	def testMultiplyFunction(self, num0, num1, num2) :
		return (num0 * num1 * num2)


	def testDivisionFunction(self, num0, num1) :
		return (num0 / num1)


	def testPowFunction(self, num0, num1) :
		return (num0 ** num1)


	def testComparisonFunction(self, num0, num1) :
		if ( (num0 == num1) ):
			return "num0 = num1"
		elif ( (num0 < num1) ):
			return "num0 < num1"
		else:
			return "num0 > num1"
		


	def testRandomIntegerFunction(self, start, end) :
		return random.randint(start, end)


	def testMinFunction(self, num0, num1, num2) :
		return min(3, num0, num1, num2)


	def testRandomFractionFunction(self) :
		return random.random()


	def testSquareRootFunction(self, number) :
		return sqrt(number)


	def testMaxFunction(self, num0, num1, num2) :
		return max(3, num0, num1, num2)


	def testNegFunction(self, number) :
		return -(number)


	def testAbsoluteFunction(self, number) :
		return abs(number)


	def testLogFunction(self, number) :
		return log(number)


	def testExpFunction(self, number) :
		return exp(number)


	def testRoundFunction(self, number) :
		return round(number)


	def testCeilingFunction(self, number) :
		return ceil(number)


	def testSinFunction(self, number) :
		return sin(number)


	def testCosFunction(self, number) :
		return cos(number)


	def testTanFunction(self, number) :
		return tan(number)


	def testAsinFunction(self, number) :
		return asin(number)


	def testAcosFunction(self, number) :
		return acos(number)


	def testFloorFunction(self, number) :
		return floor(number)


	def testAtanFunction(self, number) :
		return atan(number)


	def testComvertRadiansToDegreesFunction(self, radians_number) :
		return radians(radians_number)


	def testAtan2Function(self, number1, number0) :
		return atan2(number0 , number1)


	def testFormatDecimalNumberFunction(self, places, number) :
		return degrees(degrees_number)


	def testRemainderFunction(self, dividend, divisor) :
		return (dividend % divisor)


	def testComvertRadiansToDegreesFunction(self, degrees_number) :
		return degrees(degrees_number)


	def tesQuotientFunction(self, dividend, divisor) :
		return (dividend / divisor)


	def testConvertHexToBase10Function(self, hexadecimalNumber) :
		return int(hexadecimalNumber, 16)


	def testConvertBinaryToBase10Function(self, binaryNumber) :
		return int(binaryNumber, 16)


	def testConvertBase10ToHexFunction(self, number) :
		return int(number, 16)


	def testConvertBase10ToBinaryFunction(self, number) :
		return int(number, 16)


	def setup(self):
		signal.signal(signal.SIGTERM, self.stop)
		signal.signal(signal.SIGINT, self.stop)
		

	def start(self) :
		self.running = True
		while self.running :
			time.sleep(0.01)
		GPIO.cleanup()
		sys.exit(0)

	def stop(self, signal, frame) :
		self.running = False


if __name__ == '__main__' :
	app = AppGen()
	app.setup()
	app.start()
