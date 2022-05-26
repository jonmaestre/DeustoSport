#ifndef CALZADO_H_
#define CALZADO_H_

#include "Productos.h"

class Calzado : public Producto
{
    char *color;
    int talla;
    int genero;
public:
    Calzado(char* nombre, char* tipo, char* color, int talla, float precioBase, int genero, int stock);
    Calzado(const Calzado& c);
    virtual ~Calzado();
    
    char* getColor();
    int getTalla();
    int getGenero();
    
};


#endif