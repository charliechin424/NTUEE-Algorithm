# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
OPTFLAGS = -O2

all	: bin/mps
	@echo -n ""

# optimized version
bin/mps	: mps_opt.o src
			$(CC) $(OPTFLAGS) mps_opt.o -ltm_usage -Lsrc -o bin/mps
mps_opt.o 	   	: src/mps.cpp src/tm_usage.h
			$(CC) $(CFLAGS) $< -Ilib -o $@


src: src/libtm_usage.a

src/libtm_usage.a: tm_usage.o
	$(AR) $(ARFLAGS) $@ $<
tm_usage.o: src/tm_usage.cpp src/tm_usage.h
	$(CC) $(CFLAGS) $<

# clean all the .o and executable files
clean:
		rm -rf *.o lib/*.a lib/*.o bin/*

