CurPath:=$(shell pwd)
libObj:=$(CurPath)/Obj/libobj
clientObj:=$(wildcard $(libObj)/*.o $(libObj)/clientobj/*.o)
serverObj:=$(wildcard $(libObj)/*.o $(libObj)/serverobj/*.o)
gateObj:=$(wildcard $(libObj)/*.o $(libObj)/gateobj/*.o)

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