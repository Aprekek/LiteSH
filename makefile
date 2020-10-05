PATH_SRC = src/
PATH_BUILD_SRC = build/

all: build build/src project

project: $(PATH_BUILD_SRC)main.o $(PATH_BUILD_SRC)litesh.o $(PATH_BUILD_SRC)help.o
	g++ $(PATH_BUILD_SRC)main.o $(PATH_BUILD_SRC)litesh.o $(PATH_BUILD_SRC)help.o -o project

$(PATH_BUILD_SRC)main.o: $(PATH_SRC)main.cpp
	g++ -Wall -c $(PATH_SRC)main.cpp -o $(PATH_BUILD_SRC)main.o

$(PATH_BUILD_SRC)litesh.o: $(PATH_SRC)litesh.cpp
	g++ -Wall -c $(PATH_SRC)litesh.cpp -o $(PATH_BUILD_SRC)litesh.o

$(PATH_BUILD_SRC)help.o: $(PATH_SRC)help.cpp
	g++ -Wall -c $(PATH_SRC)help.cpp -o $(PATH_BUILD_SRC)help.o

build:
	mkdir build

build/src:
	mkdir build/src

clean:
	rm -rf build/*.o

.PHONY: clean