
#include "client.h"

extern int sock;
extern struct sockaddr_in server;

void store(person * ptr, int size)
{
    int read_size, result;
    // person peep;
    int c = sizeof(struct sockaddr_in);
    
    sendto(sock, ptr, size, 0, (struct sockaddr*) &server, sizeof(server));
    read_size = recvfrom(sock, ptr, size, 0, (struct sockaddr*) &server, (socklen_t*) &c);
    
    if(read_size == 0) {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1) {
        perror("recv failed");
    }
}
