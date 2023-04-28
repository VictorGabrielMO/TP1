CC = g++
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/main.o
HDRS = $(INC)/linkedstack.hpp $(INC)/node.hpp

EXE = $(BIN)/exec

run:  $(EXE) 

$(BIN)/exec: $(OBJS)
	$(CC) -pg -o $(BIN)/exec $(OBJS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) -o $(OBJ)/main.o -c $(SRC)/main.cpp

	





	
clean:
	rm -f $(EXE) $(OBJS) gmon.out