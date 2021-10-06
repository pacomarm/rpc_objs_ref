
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT_NUM 8888

typedef struct Addresses {
    char street[50];
    int number;
    char city[50];
} address;

#pragma pack(1) 
typedef struct People{
    char name[20];
    address addy;
} person;
#pragma pack(0)

// utilerias

int initialization();
int connection(int socket_desc);
int close(int sock);

// servicio(s)

int store(char * m);                        // copy-restore
void send_result(int client_sock, person* peep, int size);
char * getObject(int client_sock);