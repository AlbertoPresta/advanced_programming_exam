EXE = main \
      test
CXX = g++
CXXFLAGS = -c -Wextra -Wall -std=c++11 -I include
SRC = src/main.cc \
      src/test.cc
OBJ = $(SRC:.cc=.o)
INC = include/Tree.h

all:$(EXE)

main: main.o
	$(CXX) main.o -o main

test: test.o
	$(CXX) test.o -o test 

main.o: $(SRC)
	$(CXX) src/main.cc $(CXXFLAGS) 

test.o: $(SRC)
	$(CXX) src/test.cc $(CXXFLAGS)

main.o: include/Tree.h
Test.o: include/Tree.h

clean:
	$(info clean up)
	@rm -rf $(OBJ) $(EXE) src/*~ include/*~ *~ html latex main.o test.o


