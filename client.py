#Its job is to initiate communication with a server that is passively waiting to be contacted
#--------------------------------------
#1. Create a TCP socket using socket().
#The IPv4 address and string to echo are passed in as the first two parameters.
#Optionally, the client takes the server port as the third parameter. If no port is
# provided, the client uses the well-known echo protocol port, 7.

#The socket is for IPv4 (af_inet) using
#the stream-based protocol (sock_stream) called TCP (ipproto_tcp). socket() returns an
#integer-valued descriptor or “handle” for the socket if successful. If socket fails, it returns
#–1, and we call our error-handling function, DieWithSystemMessage() (described later), to
#print an informative hint and exit.

#We must set the address family (AF_INET), Internet address, and port number. The
#function inet_pton() converts the string representation of the server’s Internet address
#(passed as a command-line argument in dotted-quad notation) into a 32-bit binary
#representation. The server’s port number was converted from a command-line string
#to binary earlier; the call to htons() (“host to network short”) ensures that the binary
#value is formatted as required by the API.

#-----------------------------------
#2. Establish a connection to the server using connect().
#The connect() function establishes a connection between the given socket and the one
#identified by the address and port in the sockaddr_in structure. Because the Sockets
#API is generic, the pointer to the sockaddr_in address structure (which is specific to
#IPv4 addresses) needs to be cast to the generic type (sockaddr ∗ ), and the actual size of
#the address data structure must be supplied.

#-----------------------------------
#3. Communicate using send and recv().
#Send echo string to server: We find the length of the argument string and save it for later use. A pointer to the
#echo string is passed to the send() call; the string itself was stored somewhere (like all
#command-line arguments) when the application was started. We do not really care where2.1 IPv4 TCP Client
#it is; we just need to know the address of the first byte and how many bytes to send. (Note
#that we do not send the end-of-string marker character (0) that is at the end of the argu-
#ment string—and all strings in C). send() returns the number of bytes sent if successful
#and –1 otherwise. If send() fails or sends the wrong number of bytes, we must deal with the
#error. Note that sending the wrong number of bytes will not happen here. Nevertheless,
#it’s a good idea to include the test because errors can occur in some contexts.

#Receive echo server reply: TCP is a byte-stream protocol. One implication of this type of protocol is that send()
#boundaries are not preserved. In other words: The bytes sent by a call to send() on one
#end of a connection may not all be returned by a single call to recv() on the other end.
#(We discuss this issue in more detail in Chapter 7.) So we need to repeatedly receive bytes
#until we have received as many as we sent. In all likelihood, this loop will only be executed
#once because the data from the server will in fact be returned all at once; however, that
#is not guaranteed to happen, and so we have to allow for the possibility that multiple
#reads are required. This is a basic principle of writing applications that use sockets: you
#must never assume anything about what the network and the program at the other
#end are going to do.



#-----------------------------------
#4. Close the connection with close().The close() function informs the remote socket that communication is ended, and then
#deallocates local resources of the socket.
