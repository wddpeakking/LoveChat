CurrentPath=$(shell pwd)
Src:=$(wildcard *.cpp)
Obj=$(patsubst %.cpp,%.o,$(Src))

all:$(Obj)

install:
	$(shell cp *.o ../Obj/loginobj)
clean:
	rm *.o