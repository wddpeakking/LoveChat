thirdPart = ../thirdpart
lovelib = ../lovelib 
CC = g++
obj		=lovechatClient.o \
			lovelog.o
loveServer:$(obj)
	CC $(obj) -o $@

$(thirdPart)/%.o:$(thirdpart)/%.h $(thirdpart)/%.cpp
	$(CC) -c $< -o $@
$(lovelib)/%.o:$(lovelib)/%.h $(lovelib)/%.cpp
	$(CC) -c $< -o $@

.PHONY:clean
clean:
	rm *.o