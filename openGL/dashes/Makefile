PROG1 = dashes

CC ?= gcc
COPTS ?= -g

LIBS = -L/usr/X11R6/lib -lGL -lGLU -lglut -lXi -lXmu -lXext -lX11 -lm

all : $(PROG1)

clean : 
	rm -f $(PROG1)

$(PROG1) : $(PROG1).cpp
	$(CC) -o $@ $(COPTS) $< $(LIBS)
