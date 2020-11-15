TP3 - Trabalho prático. Protocolo olímpico com múltiplas conexões. 

Autor: ANDRE LUIS NUNES.

Procedimentos para a execução dos Programas.

Copie todos os arquivos .c e .h para um mesmo diretório.
Copie também o arquivo "Makefile" nesse mesmo diretório.
Feito isso, abra o terminal do linux.
Use o comando 'cd' para navegar até o diretório onde estão os programas copiados.
Digite no terminal <make>.
Feito isso os programas serão compilados pelo compilador 'gcc'.
Terminada a compilação execute primeiro o servidor: ./servidor <porta>.
Em seguida execute o cliente: ./cliente <ip/nome> <porta>.
Este servidor aceita múltiplas conexões simultaneamente.
Obs. <ip/nome> refere-se à máquina na qual está rodando o servidor.
Pronto! O cliente já pode mandar os valores de tempo para o servidor, e 
este imprimirá na tela as respectivas classificações.
Para fechar a conexão, basta o cliente mandar um valor negativo, por exemplo '-1'.



