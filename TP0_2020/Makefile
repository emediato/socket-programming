library: files.c servidor.c cliente-aluno.c
	gcc -o cliente cliente-aluno.c files.c -Wall -Wextra -pedantic
	gcc -o servidor servidor.c files.c -Wall -Wextra -pedantic -pthread
clean:
	rm servidor *.o *~
	rm cliente *.o *~
	rm files *.o*
