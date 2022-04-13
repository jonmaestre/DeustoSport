#include "Administrador.h"
#include "Calzado.h"
#include "Carrito.h"
#include "Compra.h"
#include "Comprador.h"
#include "MaterialDeportivo.h"
#include "Prenda.h"
#include "Suplemento.h"
#include "bbdd.h"
#include "Fecha.h"
#include "sqlite3.h"
#include "bbdd.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Carrito crearCarrito(sqlite3 *db, int idCompra, int idComprador) {

    Compra* compra;
    compra = comprasConId (db, idCompra);
    
    int i = 0;
    float total = 0;
    while (compra[i] != *NULL) {

        char type = obtenerTipoProducto (db, compra[i].idProducto);
        // C -> calzado		M -> material	P -> prenda 	S -> suplemento
        if (type == 'C') {
            Calzado calz = obtenerCalzado (db, compra[i].idProducto);
            total += calz.precio * compra[i].cantidad;
        } else if (type == 'M') {
            MaterialDeportivo matD =  obtenerMaterial (db, compra[i].idProducto);
            total += matD.precio * compra[i].cantidad;
        } else if (type == 'P') {
            Prenda pren = obtenerPrenda (db, compra[i].idProducto);
            total += pren.precio * compra[i].cantidad;
        } else if (type == 'S') {
            Suplemento supl = obtenerSuplemento(db, compra[i].idProducto);
            total += supl.precio * compra[i].cantidad;
        }

        i++;
    } 

    time_t t= time(NULL);
    struct tm tiempoLocal = *localtime(&t);
    char fechaHora[70];
    char *formato ="%Y-%m-%d %H:%M-%S";

    int bytesEscritos = strftime(fechaHora, sizeof fechaHora, formato, &tiempoLocal);
    


    Carrito carrito = {idCompra, idComprador, total, bytesEscritos};

    return carrito;
}
