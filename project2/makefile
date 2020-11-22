CFLAGS=-std=c++11 

all: myprime child_program grandchild_program
myprime: main.o  helper_functions.o
	g++ $(CFLAGS) -o myprime main.o  helper_functions.o
main.o: ./src/components/main.cpp ./src/header_files/main.h 
	g++ $(CFLAGS) -c ./src/components/main.cpp 
helper_functions.o: ./src/helpers/helper_functions.cpp ./src/header_files/helper_functions.h
	g++ $(CFLAGS) -c ./src/helpers/helper_functions.cpp

child_program: child_main.o child_helper_functions.o
	g++ $(CFLAGS) -o child_program child_main.o child_helper_functions.o
child_main.o: ./src/components/child_main.cpp ./src/header_files/child_main.h
	g++ $(CFLAGS) -c ./src/components/child_main.cpp
child_helper_functions.o: ./src/helpers/child_helper_functions.cpp ./src/header_files/child_helper_functions.h
	g++ $(CFLAGS) -c ./src/helpers/child_helper_functions.cpp

grandchild_program: grandchild_main.o grandchild_helper_functions.o
	g++ $(CFLAGS) -o grandchild_program grandchild_main.o grandchild_helper_functions.o
grandchild_main.o: ./src/components/grandchild_main.cpp ./src/header_files/grandchild_main.h
	g++ $(CFLAGS) -c ./src/components/grandchild_main.cpp
grandchild_helper_functions.o: ./src/helpers/grandchild_helper_functions.cpp ./src/header_files/grandchild_helper_functions.h
	g++ $(CFLAGS) -c ./src/helpers/grandchild_helper_functions.cpp
clean:
	rm *.o myprime child_program grandchild_program