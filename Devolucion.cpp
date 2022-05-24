#include "Devolucion.h"
#include "Producto.h"
#include "Comprador.h"
#include <String.h>
using namespace std;


namespace acciones 
{
    Devolucion::Devolucion(int idCompra, int idComprado, int idProducto, char* explicacion) {
    this->idCompra = idCompra;
    this->idComprador = idComprador;
    this->idProducto = idProducto;
    this->explicacion = new char[strlen(explicacion)+1];
}

Devolucion::Devolucion(const Devolucion& d) {
    this->idCompra = d.idCompra;
    this->idComprador = d.idComprador;
    this->idProducto = d.idProducto;
    this->explicacion = new char[strlen(d.explicacion)+1];
}

Devolucion::~Devolucion() {
    delete[] this->explicacion;
}

}

