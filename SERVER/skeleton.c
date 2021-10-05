
#include "server.h"

void recv_message(int client_sock, person *ptr, int size);
void send_result(int client_sock, person* peep, int size);

extern struct sockaddr_in client;

int main(int argc, char *argv[])
{
    int socket_desc = initialization();
    
    while(1) {
        
        int client_sock = connection(socket_desc);
        person peep;
        recv_message(client_sock, &peep, sizeof(peep));           // adaptador del parámetro        

        strncpy(peep.name, "Kendick Lamar", sizeof(peep.name));
        strncpy(peep.addy.street, "Grove Street", sizeof(peep.addy.street));
        peep.addy.number = 1738;
        strncpy(peep.addy.city, "Compton, CA", sizeof(peep.addy.city));
    
        send_result(client_sock, &peep, sizeof(peep));                // adaptador del resultado                                      // liberamos los recursos
    }
    
    close(socket_desc);
    return 0;
}

void recv_message(int client_sock, person* peep, int size)
{
    int read_size, length;
    int c = sizeof(struct sockaddr_in);
    
    read_size = recvfrom(client_sock, peep, size, 0, (struct sockaddr*) &client, (socklen_t*) &c);
    
    if(read_size == 0) {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1) {
        perror("recv failed");
    }

}

void send_result(int client_sock, person* peep, int size)
{
    if( sendto(client_sock, peep, size, 0, (struct sockaddr*) &client, sizeof(client)) < 0) {
        puts("Send failed");
        exit(1);
    }
}
