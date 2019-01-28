CC=g++
CFLAGS= -Wall

OBJ = pthread.o serial.o

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -O3 -o $@ $^
test1:
	time ./serial oimage.txt mask.txt of.txt

test2:
	time ./pthread oimage.txt mask.txt of.txt 10

test3:
	time ./pthread oimage.txt mask.txt of.txt 20

test4:
	time ./pthread oimage.txt mask.txt of.txt 15

test5:
	time ./pthread oimage.txt mask.txt of.txt 25

test6:
	time ./pthread oimage.txt mask.txt of.txt 30
clean:
	rm -f *.o *~ core

