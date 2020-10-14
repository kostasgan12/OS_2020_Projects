CFLAGS=-std=c++11 
CFLAGS+=-stdlib=libc++

mngstd: main.o linked_list.o student_class.o hash_table.o helper_functions.o
	g++ $(CFLAGS) -o mngstd main.o linked_list.o student_class.o hash_table.o helper_functions.o
main.o: ./src/components/main.cpp ./src/header_files/main.h
	g++ $(CFLAGS) -c ./src/components/main.cpp
linked_list.o: ./src/components/linked_list_files/linked_list.cpp ./src/header_files/linked_list.h
	g++ $(CFLAGS) -c ./src/components/linked_list_files/linked_list.cpp
student_class.o: ./src/components/classes/student_class.cpp ./src/header_files/student_class.h
	g++ $(CFLAGS) -c ./src/components/classes/student_class.cpp
hash_table.o: ./src/components/classes/hash_table.cpp ./src/header_files/hash_table.h 
	g++ $(CFLAGS) -c ./src/components/classes/hash_table.cpp 
helper_functions.o: ./src/helpers/helper_functions.cpp ./src/helpers/helper_functions.h
	g++ $(CFLAGS) -c ./src/helpers/helper_functions.cpp
clean:
	rm *.o mngstd