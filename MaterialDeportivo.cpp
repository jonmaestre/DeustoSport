#include "MaterialDeportivo.h"
#include "bbdd.h"


namespace prod{

MaterialDeportivo::MaterialDeportivo(char* nombre, char* tipo, char* color, int talla, float precioBase, char* deporte, int stock): Producto(nombre,tipo,precioBase,stock)
{
    
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
}
