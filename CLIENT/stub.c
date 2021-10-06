
#include "client.h"

extern int sock;
extern struct sockaddr_in server;

char * getObject(int client_sock);

void store(person * ptr, int size)
{
    int read_size, result;
    int c = sizeof(struct sockaddr_in);

    char str[12];
    snprintf(str, 12, "%d", ptr->addy.number);
    char buf[256];
    snprintf(buf, sizeof(buf), "%s %s %s %s", ptr->name, ptr->addy.city, ptr->addy.street, str);
    //
    int length = strlen(buf);
    send(sock, &length, sizeof(length), 0);
    
    if(send(sock, &buf, length, 0) < 0) {
        puts("Send fails");
        exit(1);
    }
    //
    
    char * m = getObject(sock);
    char name[20];
    char city[50];
    char street[50];
    char number[12];
    strncpy ( name, m, 12 );
    strncpy ( city, m+12, 10 );
    strncpy ( street, m+23, 11 );
    strncpy ( number, m+35, 3 );
    street[11] = '\0';
    strncpy(ptr->name, name, sizeof(ptr->name));
    strncpy(ptr->addy.city, city, sizeof(ptr->addy.city));
    strncpy(ptr->addy.street, street, sizeof(ptr->addy.street));
    ptr->addy.number = atoi(number);

    // read_size = recvfrom(sock, ptr, size, 0, (struct sockaddr*) &server, (socklen_t*) &c);
    
    if(read_size == 0) {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1) {
        perror("recv failed");
    }
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
