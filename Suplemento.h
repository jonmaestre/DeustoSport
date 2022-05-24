#ifndef SUPLEMENTO_H_
#define SUPLEMENTO_H_

typedef struct {
   int identificativo;
   char* nombre;
   char* tipo;
   float precio;
   int stock;
} Suplemento;


class Suplemento
{
private:
   int identificativo;
   char* nombre;
   char* tipo;
   float precio;
   int stock;

public:
   Suplemento(/* args */);
   ~Suplemento();
   int getidentificativo();
   char* getnombre();
   char* gettipo();
   float getprecio();
   int getstock();

};

Suplemento::Suplemento(/* args */)
{
}

Suplemento::~Suplemento()
{
}


#endif