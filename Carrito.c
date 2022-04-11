#include "Carrito.h"
#include "Compra.h"
#include "Fecha.h"
#include <stdio.h>
#include <stdlib.h>

Carrito  crearCarrito(int idCompra, int idComprador) {

    // BD MÉTODO -> devuelve un array de todas las compras con idCompra
    // EL ÚLTIMO + 1 que sea NULL
    Compra* compra;
    int i = 0;
    float total = 0;
    while (compra[i].cantidad != NULL) {
        total += Carrito[i].precioTotal;
        i++;
    } 

    Carrito carrito = {idCompra, idComprador, total};

    return carrito;
}
