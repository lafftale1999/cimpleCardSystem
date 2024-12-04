PROG = main.exe 
SRC = main.c src/client.c src/decrypt.c src/encrypt.c src/keygen.c src/mapgen.c src/debugo.c src/interface.c src/utils.c src/safeinput.c src/doorSystem.c
CFLAGS = -g
LIBS = 

all: $(PROG)

$(PROG): $(SRC)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SRC)  $(LIBS) 

clean:
	rm -f $(PROG)

.PHONY: all clean