#!/usr/bin/python

import os
import signal
import sys
import time
import RPi.GPIO as GPIO



class AppGen :

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
