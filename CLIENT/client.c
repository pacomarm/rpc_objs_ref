
// store messages using a service

#include "client.h"

int sock;

int main( int argc, char * argv[] )
{

    person peep = { 
        .name = "XXTentacion",
        .addy = {
            .street = "HollyStreet",
            .number = 419,
            .city   = "LosAngeles" 
        }
    };
    printf("Estructura Original:\n");
    printf("Name: %s\n", peep.name);
    printf("City: %s\n", peep.addy.city);
    printf("Street: %s\n", peep.addy.street);
    printf("Number: %d\n", peep.addy.number);

    person *peep_ptr = &peep;

    // peep_ptr->addy.number = 6969;
    // printf("Street No: %d\n", peep_ptr->addy.number);

    sock = connection();            // conección con el servidor
                                    // para llamar servicios
    
    store( peep_ptr, sizeof(peep));        // llamada local (servicio store)

    printf("---------\n");
    printf("Estructura Modificada:\n");
    printf("Name: %s\n", peep.name);
    printf("City: %s\n", peep.addy.city);
    printf("Street: %s\n", peep.addy.street);
    printf("Number: %d\n", peep.addy.number);
    close(sock);                    // cerrar la conección
    return 0;
}
