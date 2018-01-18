from gnupg import *
import socket


gpg = GPG() # Running concurrent GPGs should be okay(?)
gpg.encoding = "utf-8"
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.connect(("localhost", 6688))

while 1:
    s.send(unicode(gpg.encrypt(raw_input(), "tekk@parlementum.net")))
    print(s.recv(4096))
