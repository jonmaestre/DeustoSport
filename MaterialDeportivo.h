#ifndef MATERIALDEPORTIVO_H_
#define MATERIALDEPORTIVO_H_


#include "Productos.h"

class MD : public Producto
{
    char *color;
    int talla;
    char *deporte;
public:
    MD(char* nombre, char* tipo, char* color, int talla, float precioBase, char* deporte, int stock);
    MD(const MD& md);
    virtual ~MD();
    
    char* getColor();
    int getTalla();
    char* getDeporte();
    
};


#endif