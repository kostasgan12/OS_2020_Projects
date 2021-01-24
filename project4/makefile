CFLAGS=-std=c++11 
SANITIZE=-fsanitize=address
OPTIONS=-lpthread

all: quic

quic: main.o  main_helper_functions.o
	g++ $(CFLAGS) $(SANITIZE) -o quic main.o  main_helper_functions.o $(OPTIONS)
main.o: ./src/components/main.cpp ./src/header_files/main.h 
	g++ $(CFLAGS) -c ./src/components/main.cpp 
main_helper_functions.o: ./src/helpers/main_helper_functions.cpp ./src/header_files/main_helper_functions.h
	g++ $(CFLAGS) -c ./src/helpers/main_helper_functions.cpp
clean:
	rm *.o quic