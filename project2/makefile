CFLAGS=-std=c++11 

myprime: main.o  helper_functions.o
	g++ $(CFLAGS) -o myprime main.o  helper_functions.o
main.o: ./src/components/main.cpp ./src/header_files/main.h 
	g++ $(CFLAGS) -c ./src/components/main.cpp 
helper_functions.o: ./src/helpers/helper_functions.cpp ./src/header_files/helper_functions.h
	g++ $(CFLAGS) -c ./src/helpers/helper_functions.cpp
clean:
	rm *.o myprime