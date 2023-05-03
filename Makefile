CC = g++
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/main.o $(OBJ)/algebricExpressionTree.o 
HDRS = $(INC)/linkedStack.hpp $(INC)/node.hpp $(INC)/treenode.hpp $(INC)/algebricExpressionTree.hpp
CFLAGS = -Wall -c -I$(INC) -g

EXE = $(BIN)/exec

run:  $(EXE)

$(BIN)/exec: $(OBJS)
	$(CC) -g -o $(BIN)/exec $(OBJS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/algebricExpressionTree.o: $(HDRS) $(SRC)/algebricExpressionTree.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/algebricExpressionTree.o $(SRC)/algebricExpressionTree.cpp

	





	
clean:
	rm -f $(EXE) $(OBJS) gmon.out