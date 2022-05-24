#ifndef CARRITO_H_
#define CARRITO_H_

#include "sqlite3.h"



class Carrito
{
private:
   int idCompra;
   int idComprador;
   float precioTotal;
public:
   Carrito(/* args */);
   ~Carrito();
   Carrito crearCarrito(sqlite3 *db, int idCompra, int idComprador);
   Carrito (const Carrito& e );
   int getIdCompra(int idCompra);
   int getidComprador(int idComprador);
   float getprecioTotal(float precioTotal);
   

};



#endif