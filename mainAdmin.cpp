#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <iostream>

#include "Administrador.h"
#include "Calzado.h"
#include "Carrito.h"
#include "Compra.h"
#include "Comprador.h"
#include "MaterialDeportivo.h"
#include "Prenda.h"
#include "Suplemento.h"
#include "bbdd.h"
#include "sqlite3.h"
#include "main.c"


int main (void) {

    sqlite3 *db;
	int result = sqlite3_open("BaseDatos.db", &db);

    cout << "BIENVENIDX A DEUSTOSPORTKIT :) \n" << endl;

    cout << "1. Iniciar sesion como administrador" << endl;
    cout << "Pulsar 0 para salir" << endl;
    cout << "\n" << endl;

    int respuesta;

    do {
	    cout << "Opción: " << endl;
        cin >> respuesta;
    } while (!(respuesta == 0 || respuesta <=1));

    if (respuesta == 0) {
        cou << "¡Que pase un buen dia!";
    } else {
        Administrador administrador = iniciarAdmin (db);
    }


}
