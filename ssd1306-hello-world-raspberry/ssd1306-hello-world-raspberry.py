#!/usr/bin/python

import os
import signal
import sys
import time
import RPi.GPIO as GPIO
from math import sqrt, sin, cos, tan, asin, acos, atan, atan2, degrees, radians, log, exp, ceil, floor
from random import random, randint

from Adafruit_SSD1306_Component import Adafruit_SSD1306_Component
from FlowerPlatformRuntime.Input import Input


class AppGen :

	nr_pressed = None

	def button_onValueChanged(self, event) :
		if ( (self.nr_pressed == None) ):
			self.nr_pressed = 0
		
		if ( (event.currentValue == GPIO.LOW) ):
			self.nr_pressed = (self.nr_pressed + 1)
			text = "Number pressed: " + `self.nr_pressed`
			self.display.clearTextFromPosition(0, 0, text)
			self.display.printText(0, 0, text)
			self.display.displayChanges()
		

	
	def button2_onValueChanged(self, event) :
		if ( (hasattr(self, "prevText") == True) ):
			self.display.clearTextFromPosition(0, 20, self.prevText)
		
		if ( (event.currentValue == GPIO.LOW) ):
			text = "Button 2 pushed"
		else:
			text = "Button 2 released"
		
		self.display.clearTextFromPosition(0, 20, text)
		self.display.printText(0, 20, text)
		self.display.displayChanges()
		self.prevText = text

	
	def setup(self):
		signal.signal(signal.SIGTERM, self.stop)
		signal.signal(signal.SIGINT, self.stop)
		
		self.display = Adafruit_SSD1306_Component(24)

		self.button = Input(18, True)
		self.button.onValueChanged = self.button_onValueChanged

		self.button2 = Input(17, True)
		self.button2.onValueChanged = self.button2_onValueChanged

		self.display.setup()
		self.button.setup()
		self.button2.setup()

	def start(self) :
		self.running = True
		while self.running :
			self.display.loop()
			self.button.loop()
			self.button2.loop()
			time.sleep(0.01)
		GPIO.cleanup()
		sys.exit(0)

	def stop(self, signal, frame) :
		self.display.stop()
		self.button.stop()
		self.button2.stop()
		self.running = False


if __name__ == '__main__' :
	app = AppGen()
	app.setup()
	app.start()
