#include "Producto.h"
#include "string.h"
#include <iostream>
#include "bbdd.h"
using std::cout; using std::endl;


namespace productos {


    Producto::Producto(char* nombre, char* tipo, float precioBase, int stock) {
        sqlite3 *db;
        this->identificativo = maxIdProducto(db);
        this->nombre = new char[strlen(nombre)+1];
        this->tipo = new char[strlen(tipo)+1];
        this->precioBase = precioBase;
        this->stock = stock;
    }

    Producto::Producto(const Producto &p) {
        sqlite3 *db;
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

    void Producto::serializar(){}

    int Producto::getIdentificativo() {
        return this->identificativo;
    }

    char* Producto::getNombre() {
        return this->nombre;
    }

    char* Producto::getTipo() {
        return this->tipo;
    }

    float Producto::getPrecioBase() {
        return this->precioBase;
    }

    int Producto::getStock() {
        return this->stock;
    }



    Calzado::Calzado(char* nombre, char* tipo, char* color, int talla, float precioBase, int stock): Producto(nombre, tipo, precioBase, stock) {
        this->color = new char[strlen(color)+1];
        this->talla = talla;
    }

    Calzado::Calzado(const Calzado &c) : Producto(c) {
        this->color = new char[strlen(c.color)+1];
        this->talla = c.talla;
    }

    Calzado::~Calzado() {
        delete[] color;
    }

    void Calzado::serializar(){
        cout << "Nombre:  " << this->getNombre() << endl;
        cout << "Tipo:  " << this->getTipo() << endl;
        cout << "Color:  " << this->getColor() << endl;
        cout << "Talla:  " << this->getTalla() << endl;
        cout << "Precio:  " << this->getPrecioBase() << endl;
        cout << "Stock:  " << this->getStock() << endl;

    }

    char* Calzado::getColor() {
       return this->color;
    }

    int Calzado::getTalla() {
        return this->talla;
    }



    MaterialDeportivo::MaterialDeportivo(char* nombre, char* tipo, char* color, int talla, float precioBase, char* deporte, int stock): Producto(nombre, tipo, precioBase, stock) {
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

    void MaterialDeportivo::serializar(){
        cout << "Nombre:  " << this->getNombre() << endl;
        cout << "Tipo:  " << this->getTipo() << endl;
        cout << "Color:  " << this->getColor() << endl;
        cout << "Talla:  " << this->getTalla() << endl;
        cout << "Precio:  " << this->getPrecioBase() << endl;
        cout << "Deporte:  " << this->getDeporte() << endl;
        cout << "Stock:  " << this->getStock() << endl;

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



    Prenda::Prenda(char* nombre, char* tipo, char* color, int talla, float precioBase, int stock): Producto(nombre, tipo, precioBase, stock) {
        this->color = new char[strlen(color)+1];
        this->talla = talla;
    }

    Prenda::Prenda(const Prenda &p) : Producto(p) {  
        this->color = new char[strlen(p.color)+1];
        this->talla = p.talla;
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
    void Prenda::serializar(){
        cout << "Nombre:  " << this->getNombre() << endl;
        cout << "Tipo:  " << this->getTipo() << endl;
        cout << "Color:  " << this->getColor() << endl;
        cout << "Talla:  " << this->getTalla() << endl;
        cout << "Precio:  " << this->getPrecioBase() << endl;
        cout << "Stock:  " << this->getStock() << endl;

    }



    Suplemento::Suplemento(char* nombre, char* tipo, float precioBase, int stock, int nivelEnergia): Producto(nombre, tipo, precioBase, stock) {
        this->nivelEnergia = nivelEnergia;
    }

    Suplemento::Suplemento(const Suplemento& s): Producto(s) {
        this->nivelEnergia = nivelEnergia;
    }

    Suplemento::~Suplemento() {
    }

    void Suplemento::serializar(){
        cout << "Nombre:  " << this->getNombre() << endl;
        cout << "Tipo:  " << this->getTipo() << endl;
        cout << "Precio:  " << this->getPrecioBase() << endl;;
        cout << "Stock:  " << this->getStock() << endl;
        cout << "Stock:  " << this->getNivelEnergia() << endl;

    }

    int Suplemento::getNivelEnergia() {
        return this->nivelEnergia;
    }
    
}