CurPath:=$(shell pwd)
ObjPath:=$(CurPath)/Obj
clientObj:=$(wildcard $(ObjPath)/*.o $(ObjPath)/clientobj/*.o)
serverObj:=$(wildcard $(ObjPath)/*.o $(ObjPath)/serverobj/*.o)

BinPath:=$(CurPath)/Bin
CC:=g++
CFlag:=-Wall -g
all:server client

server:$(serverObj)
	$(CC) $(CFlag) $(serverObj) -o $(BinPath)/$@ -lpthread
client:$(clientObj)
	$(CC) $(CFlag) $(clientObj) -o $(BinPath)/$@ -lpthread

.PHONY:clean
clean:
	rm -rf $(BinPath)/*