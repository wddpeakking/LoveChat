CurrentPath=$(shell pwd)
Src:=$(wildcard *.cpp)
Obj=$(patsubst %.cpp,%.o,$(Src))

all:$(Obj)

install:
	$(shell cp *.o ../Obj/dbobj)
clean:
	rm *.o