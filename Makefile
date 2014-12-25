CC	= g++
CFLAGS	= -c -Wall -pedantic
LDFLAGS	= -lncurses
SOURCES	= lissacurses.cc
OBJECTS	= lissacurses.o
BIN	= lissacurses

all: $(SOURCES) $(BIN)
	
$(BIN): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

clean:
	rm $(BIN)
	rm -f *.o *.core

.cc.o:
	$(CC) $(CFLAGS) $< -o $@

