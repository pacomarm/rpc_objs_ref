
#include "server.h"
extern struct sockaddr_in client;

char * getObject(int client_sock) // gets the copy of object sent by client, same explanation as in the client directory
{
    char * message;
    int read_size, length;
    
    // receive the message length from client
    read_size = recv(client_sock, &length, sizeof(length), 0);
    
    // dynamic memory allocation to store the message: LITTLE ENDIAN
    message = (char *) malloc(length);            
    read_size = recv(client_sock, message, length, 0);
    
    if(read_size == 0) {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1) {
        perror("recv failed");
    }
    
    return message;
}

void send_result(int client_sock, person* peep, int size) // used to send copy of modified object back to client
{

    char str[12];
    snprintf(str, 12, "%d", peep->addy.number); // cast address number to a string 
    char buf[256];
    snprintf(buf, sizeof(buf), "%s %s %s %s", peep->name, peep->addy.city, peep->addy.street, str); // create copy of modified object into a buffer
    //
    int length = strlen(buf);
    send(client_sock, &length, sizeof(length), 0); // sends length of buffer to the client
    
    if(send(client_sock, &buf, length, 0) < 0) { // sends buffer to the client
        puts("Send fails");
        exit(1);
    }

}
