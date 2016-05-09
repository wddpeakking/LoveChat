CurPath:=$(shell pwd)
Objpath:=$(CurPath)/Obj
clientObj:=$(wildcard $(Objpath)/libobj/*.o $(Objpath)/clientobj/*.o)
serverObj:=$(wildcard $(Objpath)/libobj/*.o $(Objpath)/serverobj/*.o)
gateObj:=$(wildcard $(Objpath)/libobj/*.o $(Objpath)/gateobj/*.o)

BinPath:=$(CurPath)/Bin
CC:=g++
CFlag:=-Wall -g
all:server client gateserver

server:$(serverObj)
	$(CC) $(CFlag) $(serverObj) -o $(BinPath)/$@ -lpthread
client:$(clientObj)
	$(CC) $(CFlag) $(clientObj) -o $(BinPath)/$@ -lpthread
gateserver:$(gateObj)
	$(CC) $(CFlag) $(gateObj) -o $(BinPath)/$@ -lpthread

.PHONY:clean
clean:
	rm -rf $(BinPath)/*