CC=gcc
CFLAGS=-c -Wall -g
LDFLAGS= -lcurl
SOURCES=main.c
OBJECTS=$(SOURCES:.c=.o)
HEADERS=$(*.h)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
