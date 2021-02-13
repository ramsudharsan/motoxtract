all: motoxtract


motoxtract: motoxtract.c sha256.c
	$(CC) -o $@ $^