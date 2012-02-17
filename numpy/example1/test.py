
import example
import numpy

a = numpy.array([[5.,4.],[3.,4.]])

k = example.klass()
print "The sum of diagonal elements of %s is %s" % (a, k.trace(a))

karray = example.new_klassArray(10)
example.createKlasses(karray, 10)
print example.klassArray_getitem(karray, 0)
