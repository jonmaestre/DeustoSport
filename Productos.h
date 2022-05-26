#ifndef _PRODUCTOS_H
#define _PRODUCTOS_H

class Producto
{
   int identificativo;
   char *nombre;
   char* tipo;
   float precioBase;
   int stock;

public:
    Producto(char* nombre, char* tipo, float precio, int stock);
    Producto(const Producto &p);
    virtual ~Producto();

    int getidentificativo();
    char* getnombre();
    char* gettipo();
    float getprecio();
    int getstock();

};

#endif