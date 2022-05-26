#include "MaterialDeportivo.h"
#include "bbdd.h"


namespace prod{

MD::MD(char* nombre, char* tipo, char* color, int talla, float precioBase, char* deporte, int stock): Producto(nombre,tipo,precioBase,stock)
{
    
    this->color = new char[strlen(color)+1];
    this->talla = talla;
    this->deporte=new char[strlen(deporte)+1];
}

MD::MD(const MD &md) : Producto(md) {
        
        this->color = new char[strlen(md.color)+1];
        this->talla = md.talla;
        this->deporte = new char[strlen(md.deporte)+1];
    }

MD::~MD() {
        delete[] color;
        delete[] deporte;
    }

char* MD::getColor() {
       return this->color;
}

int MD::getTalla() {
        return this->talla;
}

char* MD::getDeporte() {
        return this->deporte;
}
}
