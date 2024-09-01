CC = gcc
CFLAGS = -Wall -Wextra

build: app.c
	$(CC) $(CFLAGS) -o tema1 app.c

clean:
	rm -f tema1
run:
	./tema1