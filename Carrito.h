#ifndef CARRITO_H_
#define CARRITO_H_
#include "Fecha.h"

typedef struct {
   int identificativoCompra;
   int identificativoComprador;
   float precioTotal;
   Fecha* fechaCompra;
} Carrito;


#endif