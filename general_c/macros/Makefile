OBJECT = macros

CC = g++
COPTS ?= -g

#LIBS = -lm

all : $(OBJECT)

clean :
	rm -f $(OBJECT)

$(OBJECT) : $(OBJECT).cpp
	$(CC) -o $@ $(COPTS) $< $(LIBS)
