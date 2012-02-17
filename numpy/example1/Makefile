all: _example.so

_example.so: example_wrap.cxx example.cpp example.py
	g++ -g -fPIC -shared -DUSE_DL_IMPORT example.cpp example_wrap.cxx -I/usr/include/python2.7 -I/usr/lib/pymodules/python2.7/numpy/core/include/numpy -L/lib/python2.7/config/ -lpython2.7 -o _example.so


example_wrap.cxx: example.i
	swig -c++ -python example.i

example.py: example.i example.h
	swig -c++ -python example.i

clean:
	rm -f example_wrap.cxx _example.so example.py example.pyc
