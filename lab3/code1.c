// Write a sender and receiver program in C by passing the IP address and the 
// port number of each other through the command line arguments using 
// connection less socket. Both of them will exchange messages with each other 
// continuously. If any one of them will receive the “exit” message from the 
// other end then both of them will close the connection. (Assume both the client 
// and server are running with in the same host)


// # Terminal 1 (Receiver)
// ./receiver 127.0.0.1 8080 9090
//             ↑        ↑    ↑
//      Receiver IP  Receiver Port  Sender Port

// # Terminal 2 (Sender)
// ./sender 127.0.0.1 9090 8080
//            ↑        ↑    ↑
//      Sender IP  Sender Port  Receiver Port


// check other folders i.e sender.c and reciever.c for the first code 
