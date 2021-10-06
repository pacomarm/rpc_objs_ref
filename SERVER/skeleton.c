
#include "server.h"

void send_result(int client_sock, person* peep, int size);
char * getObject(int client_sock);

extern struct sockaddr_in client;

int main(int argc, char *argv[])
{
    int socket_desc = initialization();
    
    while(1) {
        
        int client_sock = connection(socket_desc);
        person peep;
        
        char * m = getObject(client_sock);
        char name[20];
        char city[50];
        char street[50];
        char number[12];
        strncpy ( name, m, 12 );
        strncpy ( city, m+12, 10 );
        strncpy ( street, m+23, 11 );
        strncpy ( number, m+35, 3 );
        street[11] = '\0';
        strncpy(peep.name, name, sizeof(peep.name));
        strncpy(peep.addy.city, city, sizeof(peep.addy.city));
        strncpy(peep.addy.street, street, sizeof(peep.addy.street));
        peep.addy.number = atoi(number);
        
        printf("\nEstructura Recibida:\n");
        printf("Name: %s\n", peep.name);
        printf("City: %s\n", peep.addy.city);
        printf("Street: %s\n", peep.addy.street);
        printf("Number: %d\n\n", peep.addy.number);

        strncpy(peep.name, "KendrickFoo", sizeof(peep.name));
        strncpy(peep.addy.city, "SanDiegoCA", sizeof(peep.addy.city));

        printf("\nValores Modificados:\n");
        printf("Name: %s\n", peep.name);
        printf("City: %s\n\n", peep.addy.city);
    
        send_result(client_sock, &peep, sizeof(peep));                // adaptador del resultado                                      // liberamos los recursos
    }
    
    close(socket_desc);
    return 0;
}

char * getObject(int client_sock)
{
    char * message;
    int read_size, length;
    
    // receive the message length from client
    read_size = recv(client_sock, &length, sizeof(length), 0);
    
    // dynamic memory allocation to store the message: LITTLE ENDIAN
    message = (char *) malloc(length);                  // incluye el fin de cadena
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

void send_result(int client_sock, person* peep, int size)
{

    char str[12];
    snprintf(str, 12, "%d", peep->addy.number);
    char buf[256];
    snprintf(buf, sizeof(buf), "%s %s %s %s", peep->name, peep->addy.city, peep->addy.street, str);
    //
    int length = strlen(buf);
    send(client_sock, &length, sizeof(length), 0);
    
    if(send(client_sock, &buf, length, 0) < 0) {
        puts("Send fails");
        exit(1);
    }

}
