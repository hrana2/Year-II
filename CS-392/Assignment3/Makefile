#"I pledge my honor that I have abided by the Stevens Honor System" - Himanshu Rana - hrana2 


CC = gcc
OBJS = cs392_exec.o cs392_log.o cs392_signal.o cs392_shell.o 
RM = rm -f

cs392_shell: $(OBJS)
	$(CC) -o cs392_shell $(OBJS)

cs392_shell.o: cs392_shell.c 
	$(CC) -o cs392_shell.o -c cs392_shell.c

cs392_exec.o: cs392_exec.c 
	$(CC) -o cs392_exec.o -c cs392_exec.c 

cs392_log.o: cs392_log.c 
	$(CC) -o cs392_log.o -c cs392_log.c 

cs392_signal.o: cs392_signal.c 
	$(CC) -o cs392_signal.o -c cs392_signal.c 


clean:
	$(RM) *.o 
	$(RM) cs392_shell


re:	clean cs392_shell
