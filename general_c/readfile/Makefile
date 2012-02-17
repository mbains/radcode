CC=g++
.SUFFIXES: .cpp .o
CFLAGS=-O0 -g3 -Wall -c -fmessage-length=0
LDFLAGS=
SOURCES=readfile.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
HEADERS=
EXECUTABLE=readfile

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(HEADERS)
	@echo -- Linking $@ from $?
	$(CC)  $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	@echo -- compiling object $@ from $<
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)

