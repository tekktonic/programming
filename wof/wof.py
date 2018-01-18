"""Copyright (c) 2012, Daniel Wilkins
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the WOF nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 'AS IS' AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL Daniel Wilkins BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
"""
import socket

class WOFConnection:
    def __init__(self, server):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.server = server

    def CleanUp(self):
        self.sock.shutdown(socket.SOCK_RDWR)
        self.sock.close()

    def Size(self, f):
        self.sock.connect((self.server, 1337))
        self.sock.send("SIZE " + f)
        ret = self.sock.recv(1024)
        self.CleanUp()
        if ret != "ERR_NOEXIST\r\n" and ret != "ERR_ISDIR\r\n":
            return ret
        else:
            return None

    def List(self, d = ""):
        self.sock.connect((self.server, 1337))
        ret = ""
        self.sock.send("LIST " + d)
        data = self.sock.recv(1024)
        while data:
            ret += data
            data = self.sock.recv(1024)

        if ret != "ERR_NOEXIST\r\n" and ret != "ERR_ISFILE\r\n":
            return ret
        else:
            return None

        return ret

    def Get(self, f, callback = None, arg = None):# send is the socket to send our stuff to
        self.sock.connect((self.server, 1337))
        self.sock.send("GET " + f)

        data = self.sock.recv(4096)

        while data:
            if callback:
                if arg:
                    callback(data, arg)
                else:
                    callback(data)
            data = self.sock.recv(4096)

    def GetToFile(self, f, outfile):
        self.sock.connect((self.server, 1337))
        self.sock.send("GET " + f)

        out = open(outfile, "w")

        data = self.sock.recv(4096)
        while data:
            out.write(data)
            data = self.sock.recv(4096)

    def GetToText(self, f):
        self.sock.connect((self.server, 1337))

        self.sock.send("GET " + f)

        ret = ""
        data = self.sock.recv(4096)

        while data:
            ret += data
            data = self.sock.recv(4096)

        return ret
