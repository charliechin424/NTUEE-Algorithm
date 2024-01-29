# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c

OPTFLAGS = -O3

all	: bin/cb
	@echo -n ""

# optimized version
bin/cb	: src/cb.o 
			$(CC) $(OPTFLAGS) src/cb.o  -o bin/cb
src/cb.o : src/cb.cpp 
			$(CC) $(CFLAGS) $< -Ilib -o $@

# clean all the .o and executable files
clean:
		rm -rf *.o lib/*.a lib/*.o bin/*