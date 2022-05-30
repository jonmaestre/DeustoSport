#include "Comprita.h"


Comprita::Comprita(int idProducto, int idComprador, int cantidad) {
    this->idProducto = idProducto;
    this->idComprador = idComprador;
    this->cantidad = cantidad;
}

Comprita::Comprita(const Comprita& c) {
    this->idProducto = c.idProducto;
    this->idComprador = c.idComprador;
    this->cantidad = c.cantidad;
}

Comprita::~Comprita() {

}

int Comprita::getIdentificativo() {
    return this->identificativo;
}

int Comprita::getIdProducto() {
    return this->idProducto;
}

int Comprita::getIdComprador() {
    return this->idComprador;
}

int Comprita::getCantidad() {
    return this->cantidad;
}
