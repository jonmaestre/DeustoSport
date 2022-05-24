#ifndef CALZADO_H_
#define CALZADO_H_

class Calzado
{
private:
    int id;
    char* nombre;
    char* tipo;
    char* color;
    char* talla;
    float precio;
    int genero;
    int stock;
public:
    Calzado(/* args */);
    Calzado(/*const Calzado& e*/);
    ~Calzado();
};


#endif