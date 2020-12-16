CFLAGS=-std=c++11 
SANITIZE=-fsanitize=address
OPTIONS=-lpthread

all: chef saladmaker

chef: chef_main.o  chef_helper_functions.o
	g++ $(CFLAGS) $(SANITIZE) -o chef chef_main.o  chef_helper_functions.o $(OPTIONS)
chef_main.o: ./src/components/chef_main.cpp ./src/header_files/chef_main.h 
	g++ $(CFLAGS) -c ./src/components/chef_main.cpp 
chef_helper_functions.o: ./src/helpers/chef_helper_functions.cpp ./src/header_files/chef_helper_functions.h
	g++ $(CFLAGS) -c ./src/helpers/chef_helper_functions.cpp

saladmaker: saladmaker_main.o saladmaker_helper_functions.o
	g++ $(CFLAGS) -o saladmaker saladmaker_main.o saladmaker_helper_functions.o
saladmaker_main.o: ./src/components/saladmaker_main.cpp ./src/header_files/saladmaker_main.h
	g++ $(CFLAGS) -c ./src/components/saladmaker_main.cpp
saladmaker_helper_functions.o: ./src/helpers/saladmaker_helper_functions.cpp ./src/header_files/saladmaker_helper_functions.h
	g++ $(CFLAGS) -c ./src/helpers/saladmaker_helper_functions.cpp

clean:
	rm *.o chef saladmaker 