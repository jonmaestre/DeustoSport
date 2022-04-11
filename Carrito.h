#ifndef CARRITO_H_
#define CARRITO_H_
#include "Fecha.h"

typedef struct {
   int idCompra;
   int idComprador;
   float precioTotal;
   Fecha* fechaCompra;
} Carrito;


#endif