#! /usr/bin/env python3

"""This is my homework for Coursera: Interfacing with the Raspberry Pi Week 3
   This program simply searches through twitter for tweets
   mentioning "Ian G. Harris" and prints "Ian G. Harris is popular!" when
   3 or more such tweets are found."""

import json
from twython import TwythonStreamer

def get_connection_info():
	with open("authentication.json", "rt") as jsfp:
		authinfo = json.load(jsfp)
		c_key = authinfo["consumer_api_key"]
		c_secret = authinfo["consumer_api_secret"]
		a_token = authinfo["access_token"]
		a_secret = authinfo["access_token_secret"]
	return c_key, c_secret, a_token, a_secret

class IanHunter(TwythonStreamer):
	def __init__(self):
		TwythonStreamer.__init__(self, *get_connection_info())
		self.counter = 0

	def on_success(self, data):
		if "user" in data and "text" in data:
			print("%s(@%s) tweeted:\n\t%s\n\n" % (data["user"]["name"], data["user"]["screen_name"], data["text"]))
			self.counter += 1
			if self.counter > 3:
				print("Ian G. Harris is popular!!")
				self.disconnect()


def main():
	ian_hunter = IanHunter()
	ian_hunter.statuses.filter(track="Ian G. Harris")

if __name__ == "__main__":
	main()
