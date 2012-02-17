from twisted.internet.protocol import Protocol, Factory
from twisted.internet.endpoints import TCP4ServerEndpoint
from twisted.internet import reactor

class Echo(Protocol):

    def connectionMade(self):
        print "connection made"
         
    def connectionLost(self, reason):
        print "connection lost"

    def dataReceived(self, data):
#        from ipdb import set_trace; set_trace()
        print data
        self.transport.write('HTTP/1.1 200 OK\r\n')
        sdata = "<html> <body> stuff here </body></html>"
        self.transport.write('Content-Type: text/html\r\n')
        self.transport.write('Content-Length:%s\r\n' % len(sdata))
        self.transport.write('\r\n')
        self.transport.write(sdata+"\r\n");
        #self.transport.loseConnection()
        

factory = Factory()
factory.protocol = Echo

reactor.listenTCP(8007, factory)
reactor.run()

