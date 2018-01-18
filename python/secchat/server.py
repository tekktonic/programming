from gnupg import *
from twisted.internet.protocol import Protocol, Factory
from twisted.internet.endpoints import TCP4ServerEndpoint
from twisted.internet import reactor
import uuid # until we can use usernames
import getpass

clients = {}

passphrase = getpass.getpass("Passphrase: ")

class SecChat(Protocol):
    def connectionMade(self):
        self.id = str(uuid.uuid4())
        print self.id
        clients[self.id] = self
        print clients[self.id]
        print clients

    def connectLost(self):
        print("should be dead")
        clients.remove(self.id)

    def dataReceived(self, data):
        gpg = GPG() # Running concurrent GPGs should be okay(?)
        gpg.encoding = "utf-8"
        out = unicode(gpg.decrypt(data, passphrase=passphrase))
        print data
        print "out: " + out + "\n\n\n"
        for i in clients:
            clients[i].transport.write(out.encode("charmap") + "\n")

class SecChatFactory(Factory):
    protocol = SecChat


endp = TCP4ServerEndpoint(reactor, 6688)
endp.listen(SecChatFactory())

reactor.run()
    
