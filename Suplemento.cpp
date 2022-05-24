#include "Suplemento.h"
#include "bbdd.h"

namespace productos
{
    
Suplemento::Suplemento(char* nombre, char* tipo, float precio, int stock) {
    sqlite *db;
    this->id = maxIdProducto(db);
    this->nombre = new char[strlen(nombre)+1];;
    this->tipo = new char[strlen(tipo)+1];;
    this->precio = precio;
    this->stock = stock;
}


Suplemento::Suplemento(const Suplemento& s) {
    sqlite *db;
    this->id = maxIdProducto(db);
    this->nombre = new char[strlen(s.nombre)+1];;
    this->tipo = new char[strlen(s.tipo)+1];;
    this->precio = s.precio;
    this->stock = s.stock;
}

Suplemento::~Suplemento() {
    delete[] this->nombre;
    delete[] this->tipo;
}

int Suplemento::getidentificativo() {
    return this->identificativo;
}

char* Suplemento::getnombre() {
    return this->nombre;
}

char* Suplemento::gettipo() {
    return this->tipo;
}

float Suplemento::getprecio() {
    return this->precio;
}

int Suplemento::getstock() {
    return this->stock;
}

}
