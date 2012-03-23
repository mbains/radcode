CC=g++
.SUFFIXES: .cpp .o
CFLAGS=-O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x
LDFLAGS=
SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
HEADERS=
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(HEADERS)
	@echo -- Linking $@ from $?
	$(CC)  $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	@echo -- compiling object $@ from $<
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)

