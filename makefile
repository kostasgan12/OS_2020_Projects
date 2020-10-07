mngstd: main.o 
	g++ -o mngstd main.o 
main.o: ./src/components/main.cpp ./src/header_files/main.h
	g++ -c ./src/components/main.cpp
clean:
	rm *.o mngstd