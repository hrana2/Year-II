#"I pledge my honor that I have abided by the Stevens Honor System" - Himanshu Rana - hrana2

CC = gcc
OBJS = cs392_thread.o
RM = rm -rf
LDFLAGS	= -pthread

cs392_thread: $(OBJS)

cs392_thread.o: cs392_thread.c 
	$(CC) -c cs392_thread.c -o $(OBJS) $(LDFLAGS)
	
clean: 
	$(RM) *.o 
	$(RM) cs392_thread

re: clean cs392_thread