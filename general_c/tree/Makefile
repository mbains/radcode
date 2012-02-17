CC=g++
CFLAGS=-c -Wall -g
LDFLAGS=
SOURCES=main.cpp treetype.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
HEADERS=$(*.h)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
