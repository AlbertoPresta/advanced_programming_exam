EXE = main
CXX = g++
CXXFLAGS = -c -Wextra -Wall -std=c++11 -I include
SRC = src/main.cc
OBJ = $(SRC:.cc=.o)
INC = include/Tree.h

all:main

$(EXE): main.o
	$(CXX) main.o -o main

main.o: $(SRC)
	$(CXX) src/main.cc $(CXXFLAGS) 

main.o: include/Tree.h

clean:
	$(info clean up)
	@rm -rf $(OBJ) $(EXE) src/*~ include/*~ *~ html latex
