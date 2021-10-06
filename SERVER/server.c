#include "server.h"

void printStruct(person* peep);

int main(int argc, char *argv[])
{
    int socket_desc = initialization();
    
    while(1) {
        
        int client_sock = connection(socket_desc);
        person peep;
        
        char * m = getObject(client_sock); // receives original copy of person object

        //process of copying values of person object sent by client into the local copy of the object
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
        peep.addy.number = atoi(number); // end of copying values to local object
        
        printf("\nEstructura Recibida:\n");
        printStruct(&peep);

        strncpy(peep.name, "KendrickFoo", sizeof(peep.name)); // modifying name of person
        strncpy(peep.addy.city, "SanDiegoCA", sizeof(peep.addy.city)); // modifying city of person

        printf("\n----------\n\n");
        printf("Estructura Modificada:\n");
        printStruct(&peep);
    
        send_result(client_sock, &peep, sizeof(peep));  // sends copy of modified object back to client
    }
    
    close(socket_desc);
    return 0;
}

void printStruct(person* peep){
    printf("Name: %s\n", peep->name);
    printf("City: %s\n", peep->addy.city);
    printf("Street: %s\n", peep->addy.street);
    printf("Number: %d\n", peep->addy.number);
}