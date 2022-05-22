#ifndef CARRITO_H_
#define CARRITO_H_

#include "sqlite3.h"

typedef struct {
   int idCompra;
   int idComprador;
   float precioTotal;
} Carrito;

Carrito crearCarrito(sqlite3 *db, int idCompra, int idComprador);


#endif