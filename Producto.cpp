#include "Producto.h"

namespace productos {


    Producto::Producto(char* nombre, char* tipo, float precio, int stock) {
        sqlite3 *db;
        this->identificativo = maxIdProducto(db);
        this->nombre = new char[strlen(nombre)+1];
        this->tipo = new char[strlen(tipo)+1];
        this->precio = precio;
        this->stock = stock;
    }

    Producto::Producto(const Producto &p) {
        sqlite3 *db;
        this->identificativo = maxIdProducto(db);
        this->nombre = new char[strlen(p.nombre)+1];;
        this->tipo = new char[strlen(p.tipo)+1];;
        this->precio = p.precio;
        this->stock = p.stock;
    }

    Producto::~Producto() {
        delete[] this->nombre;
        delete[] this->tipo;
    }

    int Producto::getIdentificativo() {
        return this->identificativo;
    }

    char* Producto::getNombre() {
        return this->nombre;
    }

    char* Producto::getTipo() {
        return this->tipo;
    }

    float Producto::getPrecio() {
        return this->precio;
    }

    int Producto::getStock() {
        return this->stock;
    }



    Calzado::Calzado(char* nombre, char* tipo, char* color, int talla, float precio, int genero, int stock): Producto(nombre, tipo, precio, stock) {
        this->color = new char[strlen(color)+1];
        this->talla = talla;
        this->genero = genero;
    }

    Calzado::Calzado(const Calzado &c) : Producto(c) {
        this->color = new char[strlen(c.color)+1];
        this->talla = c.talla;
        this->genero = c.genero;
    }

    Calzado::~Calzado() {
        delete[] color;
    }

    char* Calzado::getColor() {
       return this->color;
    }

    int Calzado::getTalla() {
        return this->talla;
    }

    int Calzado::getGenero() {
        return this->genero;
    }



    MaterialDeportivo::MaterialDeportivo(char* nombre, char* tipo, char* color, int talla, float precio, char* deporte, int stock): Producto(nombre, tipo, precio, stock) {
        this->color = new char[strlen(color)+1];
        this->talla = talla;
        this->deporte=new char[strlen(deporte)+1];
    }

    MaterialDeportivo::MaterialDeportivo(const MaterialDeportivo &md) : Producto(md) {  
        this->color = new char[strlen(md.color)+1];
        this->talla = md.talla;
        this->deporte = new char[strlen(md.deporte)+1];
    }

    MaterialDeportivo::~MaterialDeportivo() {
        delete[] color;
        delete[] deporte;
    }

    char* MaterialDeportivo::getColor() {
       return this->color;
    }

    int MaterialDeportivo::getTalla() {
        return this->talla;
    }

    char* MaterialDeportivo::getDeporte() {
        return this->deporte;
    }



    Prenda::Prenda(char* nombre, char* tipo, char* color, int talla, float precio, int sexo, int stock): Producto(nombre, tipo, precio, stock) {
    this->color = new char[strlen(color)+1];
    this->talla = talla;
    this->sexo=sexo;
    }

    Prenda::Prenda(const Prenda &p) : Producto(p) {  
        this->color = new char[strlen(p.color)+1];
        this->talla = p.talla;
        this->sexo = p.sexo;
    }

    Prenda::~Prenda() {
        delete[] color;
    }

    char* Prenda::getColor() {
       return this->color;
    }

    int Prenda::getTalla() {
        return this->talla;
    }

    int Prenda::getSexo() {
        return this->sexo;
    }



    Suplemento::Suplemento(char* nombre, char* tipo, float precio, int stock, int nivelEnergia): Producto(nombre, tipo, precio, stock): Producto(nombre, tipo, precio, stock) {
        this->nivelEnergia = nivelEnergia;
    }

    Suplemento::Suplemento(const Suplemento& s): Producto(p) {
        this->nivelEnergia = nivelEnergia;
    }

    Suplemento::~Suplemento() {
    }

    int Suplemento::getNivelEnergia() {
        return this->nivelEnergia;
    }
    
}