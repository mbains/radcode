from twisted.web.server import Site
from twisted.web.resource import Resource
from twisted.web.static import File
from twisted.internet import reactor
from twisted.internet.task import LoopingCall
from simplejson import dumps, loads
import random

import cgi

class FormPage(Resource):
    def __init__(self):
        self.people = [{'name': "Bob", 'money': 10, 'age':8}, {'name':"Mary", 'money': 7, 'age':11}]
        self.loopingCall = LoopingCall(self._age)
        self.loopingCall.start(2)
        Resource.__init__(self)

    def _age(self):
        for person in self.people:
            person['money'] +=  random.randrange(3)
            person['age'] += 1
        print self.people

    def render_GET(self, request):
        return '<html><body> OKAY <form method="POST"><input name="the-field" type="text" /></form></body></html>'

    def render_POST(self, request):
        print "request = [%s]" % request.__dict__
        print "content = [%s]" % request.content.readline()
        return dumps(self.people)
        return '<html><body>You submitted: %s</body></html>' % (cgi.escape(request.args["the-field"][0]),)

root = Resource()
root.putChild("form", FormPage())
root.putChild("file", File("file.html"))
factory = Site(root)
reactor.listenTCP(8880, factory)
reactor.run()

