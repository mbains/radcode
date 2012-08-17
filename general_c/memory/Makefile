OBJECT = main

CC = g++
COPTS ?= -g

LIBS = 

all : $(OBJECT)

clean :
	rm -f $(OBJECT)

$(OBJECT) : $(OBJECT).cpp
	$(CC) -g -o $@ $(COPTS) $< $(LIBS)
