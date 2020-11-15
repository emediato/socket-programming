CC := gcc
SRCDIR := src
OBJDIR := build
BINDIR := bin

MAIN := main.cpp
SERVIDOR := servidor.c
PROFESSOR := cliente-prof.c
ALUNO := cliente-aluno.c

SRCEXT := c

# -g debug, --coverage para cobertura
#CFLAGS := --coverage -g -Wall -O3 -std=c++11
CFLAGS := -std=c11

all: clean main

clean:
	$(RM) -rf servidor prof aluno

main: $(OBJECTS)
	$(CC) $(CFLAGS) $(SERVIDOR) -I include/ -o servidor
	$(CC) $(CFLAGS) $(PROFESSOR) -I include/ -o prof
	$(CC) $(CFLAGS) $(ALUNO) -I include/ -o aluno
