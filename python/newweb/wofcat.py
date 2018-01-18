#!/usr/bin/env python
import socket as sock
import sys
import hrsize

s = sock.socket(sock.AF_INET, sock.SOCK_STREAM)

s.setsockopt(sock.SOL_SOCKET, sock.SO_REUSEADDR, 1)

s.connect((sys.argv[1], 1337))

s.send("GET " + sys.argv[2])

out = ""

done = False
first = True
size = 0.0
while not done:
    data = s.recv(4096)
    size += len(data)
    if not data:
        done = True

    if first:
	sys.stderr.write("received: " + hrsize.hrsize(size) + "\n")
	first = False
    else:
	sys.stderr.write("\b\rreceived: " + hrsize.hrsize(size) + "kb\n")
    print(data)
