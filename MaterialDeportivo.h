#ifndef MATERIALDEPORTIVO_H_
#define MATERIALDEPORTIVO_H_

class MaterialDeportivo
{
private:
    int identificativo;
    char* nombre;
    char* tipo;
    char* color;
    char* talla;
    float precio;
    char* deporte;
    int stock;
public:
    MaterialDeportivo(/* args */);
    ~MaterialDeportivo();
    int getidentificativo();
    char getnombre();
    char gettipo();
    char getcolor();
    char gettalla();
    float getprecio();
    char getdeporte();
    int getstock();
};

#endif