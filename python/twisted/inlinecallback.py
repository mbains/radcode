from twisted.internet import reactor
from twisted.internet.defer         import inlineCallbacks, Deferred

def func2():
    d = Deferred()
    reactor.callLater(5, func3, d)
    return d

def func3(dfr):
    print "func 3 finished"
    dfr.callback("success")

@inlineCallbacks
def func1():
    print "func 1 waiting for func3, 5 seconds"
    d = yield func2()
    print "func 1 done, got ", d

reactor.callWhenRunning(func1)
reactor.run()





