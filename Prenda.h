#ifndef PRENDA_H_
#define PRENDA_H_

typedef struct {
    int identificativo;
    char* nombre;
    char* tipo;
    char* color;
    char* talla;
    float precio;
    int sexo;
    int stock;
} Prenda;


class Prenda
{
private:
    int identificativo;
    char* nombre;
    char* tipo;
    char* color;
    char* talla;
    float precio;
    int sexo;
    int stock;
public:
    Prenda(/* args */);
    ~Prenda();
    int getidentificativo();
    char* getnombre();
    char* gettipo();
    char* getcolor();
    char* gettalla();
    float getprecio();
    int getsexo();
    int getstock();

};



#endif