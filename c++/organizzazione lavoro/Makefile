EXE = main
CXX = c++
CXXFLAGS =  -Wextra -Wall -std=c++11 -I include
SRC = src/main.cc
OBJ = $(SRC:.cc=.o)
INC = include/Tree.h


all: $(EXE)

.PHONY: all

clean:
	$(info clean up)
	@rm -rf $(OBJ) $(EXE) src/*~ include/*~ *~ html latex

.PHONY: clean

%.o: %.cc 
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(EXE): $(OBJ)
	$(CXX) $^ -o $(EXE)

main.o: include/Tree.h

