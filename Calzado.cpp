#include "Calzado.h"
#include "bbdd.h"


namespace prod{

Calzado::Calzado(char* nombre, char* tipo, char* color, int talla, float precioBase, int genero, int stock): Producto(nombre,tipo,precioBase,stock)
{
    
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
        delete this->talla;
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
}
