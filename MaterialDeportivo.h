#ifndef MATERIALDEPORTIVO_H_
#define MATERIALDEPORTIVO_H_


#include "Productos.h"

class MaterialDeportivo : public Producto
{
    char *color;
    int talla;
    char *deporte;
public:
    MaterialDeportivo(char* nombre, char* tipo, char* color, int talla, float precioBase, char* deporte, int stock);
    MaterialDeportivo(const MaterialDeportivo& md);
    virtual ~MaterialDeportivo();
    
    char* getColor();
    int getTalla();
    char* getDeporte();
    
};


#endif