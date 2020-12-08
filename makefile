PATH_SRC = src/
PATH_BUILD_SRC = build/
PATHTEST = test/
PATHBUILDTEST = build/test/

all: build client server

client: $(PATH_BUILD_SRC)Clieserv.o $(PATH_BUILD_SRC)client.o $(PATH_BUILD_SRC)filesystem.o
	g++ $(PATH_BUILD_SRC)Clieserv.o $(PATH_BUILD_SRC)client.o $(PATH_BUILD_SRC)filesystem.o -o client -pthread
	
server: $(PATH_BUILD_SRC)Clieserv.o $(PATH_BUILD_SRC)server.o $(PATH_BUILD_SRC)filesystem.o
	g++ $(PATH_BUILD_SRC)Clieserv.o $(PATH_BUILD_SRC)server.o $(PATH_BUILD_SRC)filesystem.o -o server -pthread

$(PATH_BUILD_SRC)server.o: $(PATH_SRC)server.c
	g++ -Wall -c $(PATH_SRC)server.c -o $(PATH_BUILD_SRC)server.o

$(PATH_BUILD_SRC)client.o: $(PATH_SRC)client.c
	g++ -Wall -c $(PATH_SRC)client.c -o $(PATH_BUILD_SRC)client.o

$(PATH_BUILD_SRC)filesystem.o: $(PATH_SRC)filesystem.cpp
	g++ -Wall -c $(PATH_SRC)filesystem.cpp -o $(PATH_BUILD_SRC)filesystem.o

$(PATH_BUILD_SRC)Clieserv.o: $(PATH_SRC)Clieserv.c
	g++ -Wall -c $(PATH_SRC)Clieserv.c -o $(PATH_BUILD_SRC)Clieserv.o

test: build build/test project_test

project_test: $(PATHBUILDTEST)main.o $(PATHBUILDTEST)test.o $(PATHBUILDTEST)filesystem.o
	g++ -Wall $(PATHBUILDTEST)main.o $(PATHBUILDTEST)test.o $(PATHBUILDTEST)filesystem.o -o project_test

$(PATHBUILDTEST)test.o: $(PATHTEST)test.c 
	g++ -Wall -I thirdparty -I src -c $(PATHTEST)test.c -o $(PATHBUILDTEST)test.o

$(PATHBUILDTEST)main.o: $(PATHTEST)main.c
	g++ -Wall -I thirdparty -I src -c $(PATHTEST)main.c -o $(PATHBUILDTEST)main.o

$(PATHBUILDTEST)filesystem.o: $(PATH_SRC)filesystem.cpp $(PATH_SRC)filesystem.h
	g++ -Wall -I thirdparty -I src -c $(PATH_SRC)filesystem.cpp -o $(PATHBUILDTEST)filesystem.o

build:
	mkdir build

build/test:
	mkdir build/test

projectTest: 
	./project_test

clean:
	rm -rf build/*.o

.PHONY: clean