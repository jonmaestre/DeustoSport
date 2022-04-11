#include "Carrito.h"
#include "Compra.h"
#include "Fecha.h"
#include "Calzado.h"
#include "bbdd.h"
#include <stdio.h>
#include <stdlib.h>

Carrito  crearCarrito(sqlite *db, int idCompra, int idComprador) {

    Compra* compra;
    compra = Compra* comprasConId (sqlite3* db, idCompra);
    
    int i = 0;
    float total = 0;
    while (compra[i] != NULL) {

        char type = obtenerTipoProducto (db, compra[i].idProducto);
        // C -> calzado		M -> material	P -> prenda 	S -> suplemento
        if (type = "C") {
            Calzado calz = obtenerCalzado (db, int compra[i].idProducto);
            total += calz.precio * compra[i].cantidad;
        } else if (type = "M") {
            MaterialDeportivo matD =  obtenerMaterial (db, int compra[i].idProducto);
            total += matD.precio * compra[i].cantidad;
        } else if (type = "P") {
            Prenda pren = obtenerPrenda (db, int compra[i].idProducto);
            total += pren.precio * compra[i].cantidad;
        } else if (type = "S") {
            Suplemento supl = obtenerSuplemento(db, int compra[i].idProducto);
            total += supl.precio * compra[i].cantidad;
        }

        i++;
    } 

    Carrito carrito = {idCompra, idComprador, total};

    return carrito;
}
