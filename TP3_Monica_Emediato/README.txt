Mônica Emediato

Após dar o comando make, deve-se rodar em terminais diferentes os seguintes comandos (Sempre rode o servidor primeiro):

Para rodar o servidor (apenas faça isso uma vez)
./servidor [porta] 
exemplo:
./servidor 1080

Para rodar o cliente (Pode rodar vários clientes, um em cada terminal)
./cliente [IP] [porta] 
exemplo:
./cliente ::1 1080
./cliente localhost 1080
./cliente 127.0.0.1 1080





ALGORITMOS, FUNÇÕES, PROCEDIMENTOS E DECISÕES DE
IMPLEMENTAÇÃO

• ALGORITMO
Para a implementação dos códigos, foram utilizados um main para o cliente, um
main para o servidor e uma biblioteca “files.h” que o servidor utilizou para tratar as
mensagens.

o Servidor


O main servidor consiste em uma configuração de um server TCP multicliente
utilizando threads para cada conexão, onde cada cliente recebia um processo
diferente. Os serviços que o servidor oferece para seus clientes foram
implementados na biblioteca “files.h” que recebia a mensagem do cliente, realizava
as operações, e retornava uma mensagem de resposta, de modo que o servidor só
recebe a mensagem, analisa qual comando é dado e envia para uma função
específica da biblioteca. Para mensagens que não eram de nenhum comando, o
servidor responde com uma mensagem vazia e na tela do cliente, apenas aparece
um salto de linha, indicando que não foi efetuada nenhuma operação e o servidor
não entendeu a mensagem.


o Cliente

O main do cliente é simples e não possui nenhuma informação a respeito do
servidor ou da biblioteca. Ele apenas configura um cliente TCP que aceita tanto IPv4
quanto IPv6. Em seu loop, ele apenas lê uma mensagem, envia para o servidor,
recebe a mensagem e testa se é uma mensagem de finalização, retornando para o
começo do laço.


o Biblioteca Files


A biblioteca files foi implementada utilizando dois arquivos, files.c e files.h. No
arquivo files.h, são declaradas as funções da biblioteca e cada função tem um
cabeçalho com sua descrição. No arquivo files.c são implementadas as funções
declaradas. Todas as funções trabalham utilizando arquivos, visto que foi a melhor
opção para lidar com textos, já que em C a utilização de strings é bem complicada, o
que torna inviável a utilização de um tipo abstrato de dados. A organização é
dividida em um arquivo com o registro de usuários e senhas, um arquivo para cada
cliente, e para cada texto de cada cliente, um arquivo diferente.

Cada cliente possui um arquivo onde estão listados seus arquivos de texto. Como
cada cliente possui um único nome, cada arquivo de texto é concatenado com o
nome de seu dono, para que vários usuários possam utilizar mesmos nomes para
seus arquivos sem conflito.

Funções da biblioteca files.h

1. Nome: New_user
Entrada: char* login, char* senha
Saída: char* result
Descrição: Recebe um usuário e senha e cadastra eles no arquivo users.txt
ou retorna -1 caso o usuário já exista
2. Nome: Sendmsgtp
Entrada: char *login, char *senha, char *book, char *message
Saída: char *buffer
Descrição: Envia uma mensagem de upload de conteúdo de texto ou sinaliza
erro.
3. Nome: Begintp
Entrada: void
Saída: void
Descrição: Cria arquivo inicial de usuários e senhas.
4. Nome: Readmsgtp
Entrada: char *login, char *senha, char *book
Saída: char* result
Descrição: Recebe usuário, senha, nome do arquivo e exibe o conteúdo do
arquivo ou em caso de erro, sinaliza-o.
5. Nome: List
Entrada: char *login, char *senha
Saída: char *result
Descrição: Recebe login e senha e retorna os arquivos de texto do usuário ou
então reporta erro.

TRATAMENTO IPv4 E IPv6

O servidor deve funcionar tanto para clientes com IPv4 quanto para IPv6. Para isso,
no código “cliente.c” foi usada a estrutura genérica addrinfo e a família do endereço
foi deixada como não especificada para aceitar qualquer tipo.
Podendo assim aceitar qualquer família de endereço. No servidor, foi utilizada a
estrutura sockaddr_in6 e o socket foi configurado para receber tanto conexões com
IPv4 e IPv6.No servidor, foram implementadas threads para tratar vários clientes em paralelo.
Para isso, foi utilizada a biblioteca pthread.h e no Makefile, foi adicionado o comando
-pthread na hora de compilar o servidor.
Para cada cliente, é criado um socket novo, que não precisa mais se comunicar com
o segmento principal. Após isso, dentro do novo processo, o socket do servidor
principal é liberado e a conexão com o cliente começa com o próprio socket.
Quando o cliente encerra a conexão, o socket é liberado o processo encerrado,
enquanto o servidor principal fica sempre esperando novas conexões e transferindo-
as para novos processos.


IMPLEMENTAÇÃO

O escopo foi levemente alterado para que eu pudesse manipular algumas questões, como as strings. 
Entretanto, o trabalho prático foi útil para visualizar a comunicação TCP entre cliente e servidor
utilizando dois tipos diferentes de endereçamento IP, além de desenvolver uma
aplicação para ser utilizada em rede, que exigiu uma implementação muito bem
organizada das funções e procedimentos. 
O servidor sempre responde corretamente às mensagens que são enviadas
corretamente, embora seja imprevisível como ele responderá com mensagens
errôneas, pois o programa poderá ler lixo e utilizar esse conteúdo para operar.
Foi possível testar vários clientes em paralelo e o trabalho foi satisfatório e
 cumpriu o que foi solicitado pela descrição.

	
