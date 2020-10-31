PATH_SRC = src/
PATH_BUILD_SRC = build/

all: build client server

client: $(PATH_BUILD_SRC)Clieserv.o $(PATH_BUILD_SRC)client.o $(PATH_BUILD_SRC)process.o $(PATH_BUILD_SRC)help.o $(PATH_BUILD_SRC)filesystem.o
	g++ $(PATH_BUILD_SRC)Clieserv.o $(PATH_BUILD_SRC)client.o $(PATH_BUILD_SRC)process.o $(PATH_BUILD_SRC)help.o $(PATH_BUILD_SRC)filesystem.o -o client -pthread
	
server: $(PATH_BUILD_SRC)Clieserv.o $(PATH_BUILD_SRC)server.o $(PATH_BUILD_SRC)process.o $(PATH_BUILD_SRC)filesystem.o
	g++ $(PATH_BUILD_SRC)Clieserv.o $(PATH_BUILD_SRC)server.o $(PATH_BUILD_SRC)process.o $(PATH_BUILD_SRC)filesystem.o -o server -pthread

$(PATH_BUILD_SRC)server.o: $(PATH_SRC)SERVER.c
	g++ -Wall -c $(PATH_SRC)SERVER.c -o $(PATH_BUILD_SRC)server.o

$(PATH_BUILD_SRC)client.o: $(PATH_SRC)CLIENT.c
	g++ -Wall -c $(PATH_SRC)CLIENT.c -o $(PATH_BUILD_SRC)client.o

$(PATH_BUILD_SRC)process.o: $(PATH_SRC)process.cpp
	g++ -Wall -c $(PATH_SRC)process.cpp -o $(PATH_BUILD_SRC)process.o

$(PATH_BUILD_SRC)filesystem.o: $(PATH_SRC)filesystem.cpp
	g++ -Wall -c $(PATH_SRC)filesystem.cpp -o $(PATH_BUILD_SRC)filesystem.o

$(PATH_BUILD_SRC)Clieserv.o: $(PATH_SRC)Clieserv.c
	g++ -Wall -c $(PATH_SRC)Clieserv.c -o $(PATH_BUILD_SRC)Clieserv.o

$(PATH_BUILD_SRC)help.o: $(PATH_SRC)help.cpp
	g++ -Wall -c $(PATH_SRC)help.cpp -o $(PATH_BUILD_SRC)help.o

build:
	mkdir build

clean:
	rm -rf build/*.o

.PHONY: clean
