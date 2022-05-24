#include "Calzado.h"
#include "bbdd.h"

Calzado(char* nombre, char* tipo, char* color, char* talla, float precio, int genero, int stock) {
    sqlite *db;
    this->id = maxIdProducto(db);
    this->nombre = new char[strlen(nombre)+1];
    this->tipo = new char[strlen(tipo)+1];
    this->color = new char[strlen(color)+1];
    this->talla = new char[strlen(talla)+1];
    this->precio = precio;
    this->genero = generao;
    this->stock = stock;
}

Calzado(const Calzado& c) {
    sqlite *db;
    this->id = maxIdProducto(db);
    this->nombre = new char[strlen(c.nombre)+1];
    this->tipo = new char[strlen(c.tipo)+1];
    this->color = new char[strlen(c.color)+1];
    this->talla = new char[strlen(c.talla)+1];
    this->precio = c.precio;
    this->genero = c.generao;
    this->stock = c.stock;
}

~Calzado() {
    delete[] this->nombre;
    delete[] this->tipo;
    delete[] this->color;
    delete[] this->talla;
}

char* getNombre() {
    return this->nombre;
}

char* getTipo() {
    return this->tipo;
}

char* getColor() {
    return this->color;
}

int getTalla() {
    return this->talla;
}

float getPrecio() {
    return this->precio;
}

int getGenero() {
    return this->genero;
}

int getStock() {
    return this->stock:
}