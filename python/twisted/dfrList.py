from twisted.internet import defer, reactor
from twisted.python.failure import DefaultException

def doDfrList():
    deferred1 = defer.Deferred()
    deferred2 = defer.Deferred()
    deferred3 = defer.Deferred()

    dl = defer.DeferredList([deferred1, deferred2, deferred3])
    dl.addCallback(printResult)
    reactor.callLater(1, callDfr, deferred1)
    reactor.callLater(2, errDfr, deferred2)
    reactor.callLater(3, callDfr, deferred3)

def callDfr(dfr):
    print "callDfr ", dfr
    dfr.callback("pass")


def errDfr(dfr):
    print "errDfr ", dfr
    dfr.errback(DefaultException("error"))


def printResult(result):
    print "Result: ", result


if __name__ == "__main__":
    reactor.callWhenRunning(doDfrList)
    reactor.run()



