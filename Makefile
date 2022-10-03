GXX=g++
FLAGS=-Wall -Wextra -Werror -std=c++17
TEST=-lgtest
OS=$(shell uname -s)
LINUX=-lrt -lpthread -lm -D_GNU_SOURCE
THREAD=-pthread

all:

ant:
	$(GXX) $(THREAD) ACO_algo/main.cc ACO_algo/*/*.cc Matrix/*.cc -o aco -std=c++17 $(FLAGS)
	./aco

winograd:
	$(GXX) $(THREAD) Matrix/*.cc Winograd_algo/Model/*.cc Winograd_algo/main.cc Winograd_algo/Interface/*.cc -o win -std=c++17 $(FLAGS)
	./win

gauss:
	$(GXX) $(THREAD) Matrix/*.cc SLE_algo/main.cc SLE_algo/*/*.cc -o main_gauss -std=c++17 $(FLAGS)
	./main_gauss

clean:
	rm -rf aco main win main_gauss *.a *.o

check:
	cppcheck --enable=all --suppress=missingInclude --suppress=unusedFunction --suppress=constParameter --language=c++ ACO_algo/*.* ACO_algo/*/*.* Winograd_algo/*.* Winograd_algo/*/*.* Matrix/*.*

clang:
	cp misc/.clang-format . && \
	clang-format -n ACO_algo/*.* ACO_algo/*/*.* Winograd_algo/*.* Winograd_algo/*/*.* Matrix/*.* SLE_algo/*/*.* SLE_algo/*.*
	rm -f .clang-format
