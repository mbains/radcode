from twisted.internet.task import LoopingCall
from twisted.internet import reactor


var = 1 

def func():
    global var
    print "called ", var, "times"
    if var >= 5:
        l.stop()
    var += 1


def start():
    l.start(1)

if __name__ == '__main__':
    reactor.callWhenRunning(start)
    
    l = LoopingCall(func)
    reactor.run()
