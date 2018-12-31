CC=g++

.cpp.o:
	$(CC) -c $< -o $@

.c.o:
	$(CC) -c $< -o $@

all: rscan transmit

rscan.o: rscan.cpp 

transmit.o: transmit.cpp

rscan: rscan.o 
	$(CC) -o $@ $@.o -lwiringPi

transmit: transmit.o
	$(CC) -o $@ $@.o -lwiringPi

clean:
	rm -f *.o core *~ 

mrproper: clean
	rm -f rscan transmit
