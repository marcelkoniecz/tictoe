CC = g++ -pedantic -Wall -g

# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
default: start

# To create the executable file count we need the object files
# countwords.o, counter.o, and scanner.o:
#
start:  gra.o main.o 
	$(CC)  -o a.out gra.o main.o

# To create the object file countwords.o, we need the source
# files countwords.c, scanner.h, and counter.h:
#
gra.o: gra.hpp
	$(CC)  -c gra.cpp

# To create the object file counter.o, we need the source files
# counter.c and counter.h:
#
main.o: gra.cpp
	$(CC)  -c main.cpp


# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) start *.o *~