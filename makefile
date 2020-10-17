PATH_SRC = src/
PATH_BUILD_SRC = build/

all: build client server

client: $(PATH_BUILD_SRC)Clieserv.o $(PATH_BUILD_SRC)client.o $(PATH_BUILD_SRC)process.o $(PATH_BUILD_SRC)help.o 
	g++ $(PATH_BUILD_SRC)Clieserv.o $(PATH_BUILD_SRC)client.o $(PATH_BUILD_SRC)process.o $(PATH_BUILD_SRC)help.o -o client
	
server: $(PATH_BUILD_SRC)Clieserv.o $(PATH_BUILD_SRC)server.o $(PATH_BUILD_SRC)process.o
	g++ $(PATH_BUILD_SRC)Clieserv.o $(PATH_BUILD_SRC)server.o $(PATH_BUILD_SRC)process.o -o server

$(PATH_BUILD_SRC)Clieserv.o: $(PATH_SRC)Clieserv.c
	g++ -Wall -c $(PATH_SRC)Clieserv.c -o $(PATH_BUILD_SRC)Clieserv.o

$(PATH_BUILD_SRC)server.o: $(PATH_SRC)server.c
	g++ -Wall -c $(PATH_SRC)server.c -o $(PATH_BUILD_SRC)server.o

$(PATH_BUILD_SRC)client.o: $(PATH_SRC)client.c
	g++ -Wall -c $(PATH_SRC)client.c -o $(PATH_BUILD_SRC)client.o

$(PATH_BUILD_SRC)process.o: $(PATH_SRC)process.cpp
	g++ -Wall -c $(PATH_SRC)process.cpp -o $(PATH_BUILD_SRC)process.o

$(PATH_BUILD_SRC)help.o: $(PATH_SRC)help.cpp
	g++ -Wall -c $(PATH_SRC)help.cpp -o $(PATH_BUILD_SRC)help.o

build:
	mkdir build

clean:
	rm -rf build/*.o

.PHONY: clean