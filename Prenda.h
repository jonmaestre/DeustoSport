#ifndef PRENDA_H_
#define PRENDA_H_

#include "Productos.h"

class Prenda : public Producto
{
    char *color;
    int talla;
    int sexo;
public:
    Prenda(char* nombre, char* tipo, char* color, int talla, float precioBase, int sexo, int stock);
    Prenda(const Prenda& p);
    virtual ~Prenda();
    
    char* getColor();
    int getTalla();
    int getSexo();
    
};


#endif