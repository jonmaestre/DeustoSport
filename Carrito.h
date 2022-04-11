#include "Fecha.h"

#ifndef CARRITO_H_
#define CARRITO_H_

typedef struct {
   int identificativoCompra;
   int identificativoComprador;
   float precioTotal;
   Fecha fechaCompra;
} Carrito;


#endif