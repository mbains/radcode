OBJECT = hpet-example

CC = gcc
COPTS ?= -g -s -Wall -Wstrict-prototypes

#LIBS = -lm

all : $(OBJECT)

clean :
	rm -f $(OBJECT)

$(OBJECT) : $(OBJECT).c
	$(CC) -o $@ $(COPTS) $< $(LIBS)
