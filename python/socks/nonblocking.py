import socket
import select
import fcntl
import os
import time

def setNonBlock(fdNum):
    flags = fcntl.fcntl(fdNum, fcntl.F_GETFL, 0)
    print "setting %d to nonblock, %d" % (fdNum, fcntl.fcntl(fdNum, fcntl.F_SETFL, flags | os.O_NONBLOCK))

largeStr = 'x' * 10000


def doIt(p):
    while(1):
       (readable, writable, excp)  = select.select([p.fileno()], [], [], 3)
       print "readable: ", readable
       for readyRfile in readable:
           r, info = p.accept()
           setNonBlock(r.fileno()) #TODO: Find out why resource temp unavailable when in nonblock
           print " got %s " % os.read(r.fileno(), 2)
#           time.sleep(5)
           print "total sent = ", r.send("<html> time = %s fd = %d, info = %s, largeString = %s </html>" % (time.time(), r.fileno(), str(info), largeStr))
           r.close()

if __name__ == '__main__':
    psoc= socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
    psoc.bind(('localhost', 8082))
    setNonBlock(psoc.fileno())
 
    psoc.listen(2)
    try:
        doIt(psoc)
    except Exception, e:# KeyboardInterrupt:
        print e
        psoc.close()


       

