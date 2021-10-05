
#include "client.h"

// extern char * host;
struct sockaddr_in server;

int connection()
{
    int sock;
    
    // create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1) {
        printf("Could not create socket");
    }
    puts("Socket created");
    
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT_NUM);
    
    // connect to remote server
    if (connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("connect failed. Error");
        exit(1);
    }
    
    puts("Connected\n");
    return sock;
}
