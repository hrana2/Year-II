
#"I pledge my honor that I have abided by the Stevens Honor System" - Himanshu Rana 
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

CC = gcc

CFLAGS = -O0 -g -fPIC
LIBFLAGS =  -shared -fPIC

LIBS = libcs392string.so



$(LIBS): cs392_memcpy.o cs392_strlen.o 
	$(CC) $(LIBFLAGS) -o $@ $^ 

clean:
	rm -rf *.o *.so


