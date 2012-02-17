import time
class Foo(object):
    def __init__(self):
        self.time = time.time()
        print "Hello World!"

    def __del__(self):
        print "Bye Cruel World!"


