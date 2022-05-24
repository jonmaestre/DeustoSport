#ifndef CALZADO_H_
#define CALZADO_H_

class Calzado
{
private:
    int id;
    char* nombre;
    char* tipo;
    char* color;
    int talla;
    float precio;
    int genero;
    int stock;
public:
    Calzado(char* nombre, char* tipo, char* color, char* talla, float precio, int genero, int stock);
    Calzado(const Calzado& c);
    ~Calzado();
    char* getNombre();
    char* getTipo();
    char* getColor();
    char* getTalla();
    float getPrecio();
    int getGenero();
    int getStock();
};


#endif