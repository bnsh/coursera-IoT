#! /usr/bin/env python3

"""This program is my homework assignment for week 2 of "Interfacing with the Raspberry Pi"
   on Coursera. It implements a server that simply returns "Got a request!" to the
   client on being called.
"""

import socket

def main():
	mysock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	try:
		mysock.bind(("", 8008))
		mysock.listen(8)

		request_count = 0
		while True:
			conn, (client_addr, client_port) = mysock.accept()
			conn.setblocking(True)
			# read this connection fully.
			data = conn.recv(1048576).decode("utf8")
			if data is not None:
				request_count += 1
				conn.sendall(("""HTTP/1.0 200 OK\r\nContent-Type: text/plain\r\n\r\n

Got a request from (%s:%d: Request %d)
""" % (client_addr, client_port, request_count,)).encode("utf8"))

	except socket.error:
		print("Unable to bind socket.")
	finally:
		print("Closing anyway.")
		mysock.close()

if __name__ == "__main__":
	main()
