
CFLAGS=
build: mp3

mp3: mp3.o
	gcc mp3.o $(CFLAGS) -o mp3
mp3.o: mp3.c mp3.h
	gcc -c mp3.c $(CFLAGS) -o mp3.o

run:
	./mp3

clean:
	rm *.o mp3
