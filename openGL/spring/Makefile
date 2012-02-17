OBJECT = spring

CC ?= gcc
COPTS ?= -g

LIBS = -L/usr/X11R6/lib -lGL -lGLU -lglut -lXi -lXmu -lXext -lX11 -lm

all : $(OBJECT)

clean :
	rm -f $(OBJECT)

$(OBJECT) : $(OBJECT).cpp
	$(CC) -o $@ $(COPTS) $< $(LIBS)
