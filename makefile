PATH_SRC = src/
PATH_BUILD_SRC = build/
PATH_LIB = src/lib/

all: build client server

client: $(PATH_BUILD_SRC)Clieserv.o $(PATH_BUILD_SRC)client.o $(PATH_BUILD_SRC)process.o $(PATH_BUILD_SRC)help.o libfs.so
	g++ $(PATH_BUILD_SRC)Clieserv.o $(PATH_BUILD_SRC)client.o $(PATH_BUILD_SRC)process.o $(PATH_BUILD_SRC)help.o -L. -lfs -o client -pthread 
	
server: $(PATH_BUILD_SRC)Clieserv.o $(PATH_BUILD_SRC)server.o $(PATH_BUILD_SRC)process.o libfs.so
	g++ $(PATH_BUILD_SRC)Clieserv.o $(PATH_BUILD_SRC)server.o $(PATH_BUILD_SRC)process.o -L. -lfs -o server -pthread 

libfs.so: $(PATH_BUILD_SRC)lib.o
	g++ -shared -o libfs.so $(PATH_BUILD_SRC)lib.o 

$(PATH_BUILD_SRC)server.o: $(PATH_SRC)server.c
	g++ -c $(PATH_SRC)server.c -o $(PATH_BUILD_SRC)server.o

$(PATH_BUILD_SRC)client.o: $(PATH_SRC)client.c
	g++ -Wall -c $(PATH_SRC)client.c -o $(PATH_BUILD_SRC)client.o

$(PATH_BUILD_SRC)process.o: $(PATH_SRC)process.cpp
	g++ -Wall -c $(PATH_SRC)process.cpp -o $(PATH_BUILD_SRC)process.o

$(PATH_BUILD_SRC)lib.o: $(PATH_LIB)lib.cpp
	g++ -Wall -fPIC -c $(PATH_LIB)lib.cpp -o $(PATH_BUILD_SRC)lib.o

$(PATH_BUILD_SRC)Clieserv.o: $(PATH_SRC)Clieserv.c
	g++ -Wall -c $(PATH_SRC)Clieserv.c -o $(PATH_BUILD_SRC)Clieserv.o

$(PATH_BUILD_SRC)help.o: $(PATH_SRC)help.cpp
	g++ -Wall -c $(PATH_SRC)help.cpp -o $(PATH_BUILD_SRC)help.o

build:
	mkdir build

clean:
	rm -rf build/*.o

.PHONY: clean