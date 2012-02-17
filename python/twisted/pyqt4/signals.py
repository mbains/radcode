import sys
from PyQt4 import QtGui, QtCore
from qt4reactor import install
from qt4reactor import QTReactor
#from twisted.internet import reactor

class SigSlot(QtGui.QWidget):
    def __init__(self, parent=None):
        QtGui.QWidget.__init__(self, parent)

        self.setWindowTitle('signal & slot')

        lcd = QtGui.QLCDNumber(self)
        slider = QtGui.QSlider(QtCore.Qt.Horizontal, self)

        vbox = QtGui.QVBoxLayout()
        vbox.addWidget(lcd)
        vbox.addWidget(slider)

        self.setLayout(vbox)
        self.connect(slider,  QtCore.SIGNAL('valueChanged(int)'), lcd, 
		QtCore.SLOT('display(int)') )

        self.resize(250, 150)


def meth():
	print "called"
		
	#sys.exit(app.exec_())
from twisted.internet import main
app = QtGui.QApplication(sys.argv)
qb = SigSlot()
qb.show()
reactor = QTReactor(app=app)
main.installReactor(reactor)
reactor.callLater(1.0, meth)
reactor.run()
