CC=g++
SRCS=source.cpp
OBJS=$(SRCS:.cpp=.o)
EXEC=Ratiotools
start:$(OBJS)
	$(CC) -o $(EXEC) $(OBJS)
.cpp.o:
	$(CC) -o $@ -c $<
clean:
	rm -rf $(OBJS)
