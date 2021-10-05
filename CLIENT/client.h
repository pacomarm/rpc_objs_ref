#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// utilities

int connection();
int close(int sock);

// remote services

void store(person * m, int size);
