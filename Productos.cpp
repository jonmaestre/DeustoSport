#include "Productos.h"
#include <string.h>
#include "bbdd.h"

namespace productos
{
    
Producto::Producto(char* nombre, char* tipo, float precioBase, int stock) {
    sqlite *db;
    this->identificativo = maxIdProducto(db);
    this->nombre = new char[strlen(nombre)+1];;
    this->tipo = new char[strlen(tipo)+1];;
    this->precioBase = precioBase;
    this->stock = stock;
}


Producto::Producto(const Producto &p) {
    sqlite *db;
    this->identificativo = maxIdProducto(db);
    this->nombre = new char[strlen(p.nombre)+1];;
    this->tipo = new char[strlen(p.tipo)+1];;
    this->precioBase = p.precioBase;
    this->stock = p.stock;
}

Producto::~Producto() {
    delete[] this->nombre;
    delete[] this->tipo;
}

int Producto::getidentificativo() {
    return this->identificativo;
}

char* Producto::getnombre() {
    return this->nombre;
}

char* Producto::gettipo() {
    return this->tipo;
}

float Producto::getprecio() {
    return this->precioBase;
}

int Producto::getstock() {
    return this->stock;
}

}
