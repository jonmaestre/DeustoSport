#include "Compra.h"



namespace acciones
{
    Compra::Compra(int idProducto, int idComprador, int cantidad) {
    this->idProducto = idProducto;
    this->idComprador = idComprador;
    this->cantidad = cantidad;
}

Compra::Compra(const Compra& c) {
    this->idProducto = c.idProducto;
    this->idComprador = c.idComprador;
    this->cantidad = c.cantidad;
}

Compra::~Compra() {

}

int Compra::getidentificativo() {
    return this->identificativo;
}

int Compra::getidProducto() {
    return this->idProducto;
}

int Compra::getidComprador() {
    return this->idComprador;
}

int Compra::getCantidad() {
    return this->cantidad;
}
}
