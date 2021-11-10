CC = clang
CF = -Wall

src = main.o

main: $(src)
	$(CC) $(CF) $< -o $@

%.o : %.c
	$(CC) $(CF) -c $< -o $@

clean:
	rm -rf *.o main

