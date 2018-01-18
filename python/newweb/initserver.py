#!/usr/bin/env python
import os, sys, re
import socket as sock

s = sock.socket(sock.AF_INET, sock.SOCK_STREAM)
s.setsockopt(sock.SOL_SOCKET, sock.SO_REUSEADDR, 1)
s.bind(("127.0.0.1", 1337))

s.listen(1)

globaldead = False

while not globaldead:
    dead = False

    clientsock, addr = s.accept()

    string = clientsock.recv(1024)
    realstring = string.split()

    if len(realstring) < 1: # if we get an empty message, ignore it
        continue

    elif realstring[0] == "LIST":
        ret = ""
        if len(realstring) == 1: # if there's only LIST and no directory, assume .
            wanteddir = "."
        else:
            wanteddir = realstring[1]

        if os.path.exists(wanteddir):
            if os.path.isdir(wanteddir):
                for contents in os.listdir(wanteddir):
                    if os.path.isdir(os.path.join(wanteddir, contents)):
                        ret += ("D\t" + contents + "\r\n")
                    else:
                        ret += ("F\t" + contents + "\r\n")

                        clientsock.sendall(ret)
            else:
                clientsock.send("ERR_ISFILE\r\n") # we can't exactly list a file, can we?
        else:
            clientsock.send("ERR_NOEXIST\r\n")

    elif realstring[0] == "GET":
        if len(realstring) == 1:
            clientsock.send("ERR_NOARG\r\n")
        elif os.path.isdir(realstring[1]):
            clientsock.send("ERR_ISDIR\r\n")
        else:
            f = open(realstring[1], "r")
            data = f.read(4096)
            while data:
                clientsock.send(data)
                data = f.read(4096)

    elif realstring[0] == "SIZE":
        if len(realstring) == 1:
            clientsock.send("ERR_NOARG\r\n")
        else:
            if os.path.exists(realstring[1]):
                if os.path.isfile(realstring[1]):
                    clientsock.send(str(os.path.getsize(realstring[1])) + "\r\n")
                else:
                    clientsock.send("ERR_ISDIR\r\n")
            else:
                clientsock.send("ERR_NOEXIST\r\n")

    elif realstring[0] == "ENDING":
        if os.name == "nt" or os.name == "ce" or os.name == "os2": # I think all the other OSes use unix line endings
            clientsock.send("WIN")
        else:
            clientsock.send("POSIX")
    
    else:
        pass

    clientsock.shutdown(sock.SHUT_RDWR)
    clientsock.close()

s.shutdown(sock.SHUT_RDWR)
s.close()
