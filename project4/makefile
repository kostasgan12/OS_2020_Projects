CFLAGS=-std=c++11 
SANITIZE=-fsanitize=address
OPTIONS=-lpthread

all: quic

quic: main.o  helper_functions.o
	g++ $(CFLAGS) $(SANITIZE) -o quic main.o  helper_functions.o $(OPTIONS)
main.o: ./src/components/main.cpp ./src/header_files/main.h ./src/header_files/global_variables.h
	g++ $(CFLAGS) -c ./src/components/main.cpp 
helper_functions.o: ./src/helpers/helper_functions.cpp ./src/header_files/helper_functions.h ./src/header_files/global_variables.h
	g++ $(CFLAGS) -c ./src/helpers/helper_functions.cpp
clean:
	rm *.o quic