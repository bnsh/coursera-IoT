#! /usr/bin/env python3

"""This is week 4 of the Coursera Interfacing with the Raspberry Pi class.
   It simply dims/brightens the LED that I've attached at pin 12 back and forth."""

import math
import time
import RPi.GPIO as GPIO

def main():
	GPIO.setmode(GPIO.BOARD)
	GPIO.setup(12, GPIO.OUT)
	pwm = GPIO.PWM(12, 50)
	pwm.start(0)

	# So, let's make a sine wave.
	try:
		while True:
			for theta in range(0, 360):
				rate = 100.0 * (1.0 + math.sin(theta * math.pi / 180.0)) / 2.0
				pwm.ChangeDutyCycle(rate)
				time.sleep(2.0/360.0)
	finally:
		GPIO.cleanup()

if __name__ == "__main__":
	main()
