# Sockets-Client_Server_UDP
In the UDP Server Client program , the following are the main steps that take place in :


# In the UDP Server  the following steps are performed:

1.	A UDP socket is created using create().
2.	Then this socket is bind to the server address using bind(). Bind()               operation is usually assigning a name to a socket 
3.	Then it wait until for the datagram packet to arrive from the client socket.
4.	Server then process the datagram packet and then sends a reply to the client 
5.	Then it goes back to the third step and again wait for the next datagram packet to arrive
6.	
# In the UDP Client  the following steps are performed:
1.	Here also , a UPP socket is created using create()
2.	Client Socket then send a message to the server
3.	Then it waits for the server response 
4.	It then replies to the server and if required, it goes to back to the step two
5.	Then socket descriptor is closed and the client exit.

