CFLAGS = -Wall  -g   # flags de compilação
LDFLAGS = -lm

CC = gcc

# Alvo principal
all: main

# Como criar o executável principal
main: main.o ordebusca.o
	$(CC) -o main main.o ordebusca.o $(LDFLAGS)

# Como criar o arquivo objeto ordebusca.o
ordebusca.o: ordebusca.c
	$(CC) -c $(CFLAGS) ordebusca.c -o ordebusca.o $(LDFLAGS)

# Como criar o arquivo objeto main.o
main.o: main.c
	$(CC) -c $(CFLAGS) main.c -o main.o $(LDFLAGS)

# Como limpar os arquivos objetos e o executável
clean:
	rm -f *.o main
