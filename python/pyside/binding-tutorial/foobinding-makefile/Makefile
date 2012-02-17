LIBFOO_DIR = `pwd`/../libfoo
LIBS = `pkg-config pyside --libs` \
		-L$(LIBFOO_DIR) -lfoo
CXXFLAGS = -I/usr/share/qt4/mkspecs/linux-g++ -I. \
			-I$(LIBFOO_DIR) \
			-I`pwd`/foo \
			-I`pkg-config --variable=includedir pyside`/QtCore/ \
			-I`pkg-config --variable=includedir QtCore` \
			-I`pkg-config --variable=includedir QtCore`/.. \
			-I`pkg-config --variable=includedir QtGui` \
			`pkg-config pyside --cflags`

QT4TYPESYSTEM_DIR = `pkg-config pyside --variable=typesystemdir`
QT4HEADER_DIRS = `pkg-config --variable=includedir QtCore`:`pkg-config --variable=includedir QtCore`/..
PYSIDE_PYTHONPATH = `pkg-config --variable=pythonpath PySide`
PYTHON_INTERPRETER = `pkg-config --variable=python_interpreter shiboken`

all: generate compile link

generate:
	generatorrunner --generatorSet=shiboken \
		global.h \
		--include-paths=$(LIBFOO_DIR):$(QT4HEADER_DIRS):/usr/include \
		--typesystem-paths=.:$(QT4TYPESYSTEM_DIR) \
		--output-directory=. \
		typesystem_foo.xml

compile:
	g++ foo/foo_module_wrapper.cpp foo/math_wrapper.cpp -Wall -fPIC $(CXXFLAGS) -c

link:
	g++ foo_module_wrapper.o math_wrapper.o $(LIBS) -fPIC -shared -Wl,-soname,foo.so -o foo.so

test:
	LD_LIBRARY_PATH=$(LIBFOO_DIR):$(LD_LIBRARY_PATH) PYTHONPATH=$(PYSIDE_PYTHONPATH):$(PYTHONPATH) $(PYTHON_INTERPRETER) -c \
		"import foo; m = foo.Math(); print '5 squared is %d' % m.squared(5)"

clean:
	rm -rf *.o *.so *.?pp *.log *.log foo/*

