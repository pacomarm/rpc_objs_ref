
#include "client.h"

extern int sock;
extern struct sockaddr_in server;

char * getObject(int client_sock);

void store(person * ptr, int size)
{
    int read_size, result;
    int c = sizeof(struct sockaddr_in);

    char str[12];
    snprintf(str, 12, "%d", ptr->addy.number); // storing address number as string in str
    char buf[256];
    snprintf(buf, sizeof(buf), "%s %s %s %s", ptr->name, ptr->addy.city, ptr->addy.street, str); // concatenating strings
    //
    int length = strlen(buf);
    send(sock, &length, sizeof(length), 0); // sending the length of message to send
    
    if(send(sock, &buf, length, 0) < 0) { // send the message containing the COPY of the object
        puts("Send fails");
        exit(1);
    }
    //
    
    char * m = getObject(sock); // receiving the new modified copy of the object from the server
    char name[20];
    char city[50];
    char street[50];
    char number[12];
    strncpy ( name, m, 12 ); // store the name of person in name array
    strncpy ( city, m+12, 10 ); // store the city of person in city array
    strncpy ( street, m+23, 11 ); // store the street of person in steet array
    strncpy ( number, m+35, 3 ); // store the address number of person in number variable
    street[11] = '\0'; // adding of end char array
    strncpy(ptr->name, name, sizeof(ptr->name)); //updating name of person
    strncpy(ptr->addy.city, city, sizeof(ptr->addy.city)); //updating city of person
    strncpy(ptr->addy.street, street, sizeof(ptr->addy.street)); //updating street of person
    ptr->addy.number = atoi(number); //updating address No of person
    
    if(read_size == 0) {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1) {
        perror("recv failed");
    }
}

char * getObject(int client_sock) // used to get copy of person object sent by server
{
    char * message;
    int read_size, length;
    
    // receive the message length from client
    read_size = recv(client_sock, &length, sizeof(length), 0);
    
    // dynamic memory allocation to store the message: LITTLE ENDIAN
    message = (char *) malloc(length);                  
    read_size = recv(client_sock, message, length, 0); // receives message containing copy of person obj
    
    if(read_size == 0) {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1) {
        perror("recv failed");
    }
    
    return message; 
}
