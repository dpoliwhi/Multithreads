GXX=g++
FLAGS=-Wall -Wextra -Werror
TEST=-lgtest
OS=$(shell uname -s)
LINUX=-lrt -lpthread -lm -D_GNU_SOURCE
THREAD=-pthread 

all: run clean

run:
	$(GXX) $(THREAD) main.cpp */*.cpp -o run  -std=c++17 # $(FLAGS)
	./run

clean:
	rm -rf run *.a *.o
