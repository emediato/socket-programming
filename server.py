#The server’s job is to set up a communication endpoint and passively wait for a connection from the client. There are four general
#steps for basic TCP server communication:

#-----------------------------------
#1. Create a TCP socket using socket().
#We convert the port number from string to numeric value using atoi(); if the first argu-
#ment is not a number, atoi() will return 0, which will cause an error later when we call
#bind().
#On the server, we need to associate our server socket with an address and port number
#so that client connections get to the right place. Since we are writing for IPv4, we use
#a sockaddr_in structure for this. Because we don’t much care which address we are
#on (any one assigned to the machine the server is running on will be OK), we let the
#system pick it by specifying the wildcard address inaddr_any as our desired Internet
#address. (This is usually the right thing to do for servers, and it saves the server from
#having to find out any actual Internet address.) Before setting both address and port
#number in the sockaddr_in, we convert each to network byte order using htonl() and
#htons(). (See Section 5.1.2 for details.)



#-----------------------------------
#2. Assign a port number to the socket with bind().
#As noted above, the server’s socket needs to be associated with a local address and
#port; the function that accomplishes this is bind(). Notice that while the client has to
#supply the server’s address to connect(), the server has to specify its own address to
#bind(). It is this piece of information (i.e., the server’s address and port) that they have
#to agree on to communicate; neither one really needs to know the client’s address. Note
#that bind() may fail for various reasons; one of the most important is that some other
#socket is already bound to the specified port

#-----------------------------------
#3. Tell the system to allow connections to be made to that port, using listen().
#The listen() call tells the TCP implementation to allow incoming connections from
#clients. Before the call to listen(), any incoming connection requests to the socket’s
#address would be silently rejected—that is, the connect() would fail at the client.

#-----------------------------------
#4. Repeatedly do the following:
#• Call accept() to get a new socket for each client connection.
#• Communicate with the client via that new socket using send() and recv().
#• Close the client connection using close().
