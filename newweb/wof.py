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
