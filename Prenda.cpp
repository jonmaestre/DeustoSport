#include "Prenda.h"

Prenda::Prenda(char* nombre, char* tipo, char* color, char* talla, float precio, int sexo, int stock) {
    sqlite *db;
    this->id = maxIdProducto(db);
    this->nombre = new char[strlen(nombre)+1];
    this->tipo = new char[strlen(tipo)+1];
    this->color = new char[strlen(color)+1];
    this->talla = new char[strlen(talla)+1];
    this->precio = precio;
    this->sexo = sexo;
    this->stock = stock;
}

Prenda::Prenda(const Predna& p) {
    sqlite *db;
    this->id = maxIdProducto(db);
    this->nombre = new char[strlen(p.nombre)+1];
    this->tipo = new char[strlen(p.tipo)+1];
    this->color = new char[strlen(color)+1];
    this->talla = new char[strlen(talla)+1];
    this->precio = precio;
    this->sexo = sexo;
    this->stock = stock;
}

Prenda::~Prenda() {
    delete[] this->nombre;
    delete[] this->tipo;
    delete[] this->color;
    delete[] this->talla;
}

int Prenda::getidentificativo() {
    return this->identificativo;
}

char* Prenda::getnombre() {
    return this->nombre;
}

char* Prenda::gettipo() {
    return this->tipo;
}

char* Prenda::getcolor() {
    return this->color;
}

char* Prenda::gettalla() {
    return this->talla;
}

float Prenda::getprecio() {
    return this->precio;
}

int Prenda::getsexo() {
    return this->sexo;
}

int Prenda::getstock() {
    return this->stock;
}
