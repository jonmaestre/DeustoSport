#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <iostream>
using namespace std;

#include "Administrador.h"
#include "Carrito.h"
#include "Compra.h"
#include "Comprador.h"
#include "Producto.h"
#include "bbdd.h"
#include "sqlite3.h"
#include "funcionesAdmin.h"


int main (void) {

    sqlite3 *db;
	int result = sqlite3_open("BaseDatos.db", &db);

    printf("BIENVENIDX A DEUSTOSPORTKIT :) \n");

    printf("1. Iniciar sesion como administrador \n");
    printf("Pulsar 0 para salir \n");
    printf("\n");

    int respuesta;

    do {
	    printf("Opción: \n");
        scanf("i", &respuesta);
    } while (!(respuesta == 0 || respuesta <=1));

    if (respuesta == 0) {
        printf("¡Que pase un buen dia!");
    } else {
        Administrador administrador = iniciarAdmin (db);

        // Si el identificativo del administrador es igual a -1, significa que es un impostor
        if (administrador.identificativo != -1) {
            ventanaAdmin (db, administrador);
        }

    }


}
