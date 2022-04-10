#include "Carrito.h"
#include "Compra.h"

Carrito  crearCarrito(int idCompra, int idComprador) {

    // BD MÉTODO -> devuelve un array de todas las compras con idCompra
    // EL ÚLTIMO + 1 que sea NULL
    Compra* compra;
    int i = 0;
    float total = 0;
    while (compra[i] != NULL) {
        total += compra[i].precioTotal;
        i++;
    } 

    Carrito carrito = {idCompra, idComprador, total};

    return carrito;
}
