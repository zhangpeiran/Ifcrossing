CC=g++
SRCS=source.cpp
OBJS=$(SRCS:.cpp=.o)
EXEC=Ifcrossing
start:$(OBJS)
	$(CC) -o $(EXEC) $(OBJS)
.cpp.o:
	$(CC) -o $@ -c $<
clean:
	rm -rf $(OBJS)
