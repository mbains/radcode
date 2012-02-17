from twisted.internet import reactor
from twisted.internet.protocol import Protocol, Factory

class Echo(Protocol):
    total = 0
    def __init__(self):

        print "Echo"
        self.numProtocols = 0

        
    def connectionMade(self):
        print "connection made"
        self.numProtocols = self.numProtocols+1
        if self.numProtocols > 100:
            self.transport.write("too many connections")
            self.transport.loseConnection()

    def connectionLost(self, reason):
        print reason

    def dataReceived(self, data):
        Echo.total += 1
        self.transport.write("%s" % Echo.total)
        self.transport.loseConnection()

    def __del__(self):
        print "Gone"

if __name__ == '__main__':
    factory = Factory()
    factory.protocol = Echo

    reactor.listenTCP(8007, factory)
    reactor.run()
    