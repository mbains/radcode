from twisted.internet import reactor
from twisted.internet.protocol import Protocol, ClientFactory

class Echo(Protocol):
    total = 0
    def __init__(self):

        print("Echo id: ")
        self.numProtocols = 0
        Echo.total += 1
        self.id = Echo.total

        
    def connectionMade(self):
        print("Client: connection made: ", self.id)

    def connectionLost(self, reason):
        print(reason)

    def dataReceived(self, data):
        print("Client Got Data ", data)

    def __del__(self):
        print("Gone")

if __name__ == '__main__':
    factory = ClientFactory()
    factory.protocol = Echo

    for i in range(300):
        reactor.connectTCP('localhost', 8007, factory)
    reactor.run()
    
