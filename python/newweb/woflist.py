#!/usr/bin/env python
import socket as sock
import sys

s = sock.socket(sock.AF_INET, sock.SOCK_STREAM)

s.setsockopt(sock.SOL_SOCKET, sock.SO_REUSEADDR, 1)

s.connect((sys.argv[1], 1337))

s.send("LIST " + sys.argv[2])

out = ""

done = False

while not done:
    data = s.recv(1024)
    out += data
    if not data:
        done = True

print(out)
