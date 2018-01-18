#!/usr/bin/env python
import socket as sock
import sys
import hrsize

sizesock = sock.socket(sock.AF_INET, sock.SOCK_STREAM)

sizesock.setsockopt(sock.SOL_SOCKET, sock.SO_REUSEADDR, 1)

sizesock.connect((sys.argv[1], 1337))

sizesock.send("SIZE " + sys.argv[2])
remotesize = int(sizesock.recv(1024))

sizesock.shutdown(sock.SHUT_RDWR)
sizesock.close()

s = sock.socket(sock.AF_INET, sock.SOCK_STREAM)
s.setsockopt(sock.SOL_SOCKET, sock.SO_REUSEADDR, 1)

s.connect((sys.argv[1], 1337))
s.send("GET " + sys.argv[2])

if len(sys.argv) > 3:
    out = open(sys.argv[3], "w")
else:
    tmp = sys.argv[2].split("/")
    out = open(tmp[len(tmp) - 1], "w")

done = False
loops = 1
first = True
size = 0
while not done:
    data = s.recv(4096)
    size += len(data)
    if not data:
        done = True
    elif data == "ERR_ISDIR\r\n":
        print("I can't download a directory")
        exit(1)
    else:
        out.write(data)
        if first:
            print("received: " + hrsize.hrsize(size) + " / " + hrsize.hrsize(remotesize))
            first = False
	else:
            print("\b\rreceived: " + hrsize.hrsize(size) + "/" + hrsize.hrsize(remotesize))

	loops += 1

print("\b\r\n")

s.send("DIE")
