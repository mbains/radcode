from twisted.internet.protocol import DatagramProtocol
from twisted.internet import reactor

class Echo(DatagramProtocol):

    def datagramReceived(self, data, (host, port)):
        print "received %r from %s:%d" % (data, host, port)
        echoList = ["hostname=MANNY-1", "ip-address=127.0.0.1", "mac-address=00:11:02:90:C3:6E", "type=FSN-AuxPanel", ""]
        echoList = [a+"\0" for a in echoList]
        echoStr = ''.join(echoList)
        self.transport.write(echoStr, (host, port))

reactor.listenUDP(40961, Echo())
reactor.run()

