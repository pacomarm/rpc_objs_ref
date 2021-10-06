#include "client.h"

int sock;

void printStruct(person* peep);

int main( int argc, char * argv[] )
{

    person peep = { // Creating the person object
        .name = "XXTentacion",
        .addy = {
            .street = "HollyStreet",
            .number = 419,
            .city   = "LosAngeles" 
        }
    };
    person *peep_ptr = &peep; // Pointer to person object

    printf("Estructura Original:\n");
    printStruct(peep_ptr);

    sock = connection();            // server connection
    
    store( peep_ptr, sizeof(peep));    // local call, passing the reference of person object

    printf("\n---------\n");
    
    printf("Estructura Modificada:\n\n"); // Printing the modified person object after getting 
    printStruct(peep_ptr);              // remote call to server (RESTORE)
    close(sock);                    // close connection
    return 0;
}

void printStruct(person* peep){
    printf("Name: %s\n", peep->name);
    printf("City: %s\n", peep->addy.city);
    printf("Street: %s\n", peep->addy.street);
    printf("Number: %d\n", peep->addy.number);
}
