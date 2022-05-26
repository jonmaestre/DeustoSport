#include "Prenda.h"
#include "bbdd.h"


namespace prod{

Prenda::Prenda(char* nombre, char* tipo, char* color, int talla, float precioBase, int sexo, int stock): Producto(nombre,tipo,precioBase,stock)
{
    
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
        delete[] this->talla;
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
}
