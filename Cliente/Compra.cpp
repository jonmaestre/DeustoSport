#include "Compra.h"


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

int Compra::getIdentificativo() {
    return this->identificativo;
}

int Compra::getIdProducto() {
    return this->idProducto;
}

int Compra::getIdComprador() {
    return this->idComprador;
}

int Compra::getCantidad() {
    return this->cantidad;
}
