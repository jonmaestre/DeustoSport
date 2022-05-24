#ifndef COMPRADOR_H_
#define COMPRADOR_H_

class Comprador
{
private:
    char* nombre;
    int identificativo;
    int telefono;
    char* correo;
    char* direccion;
    char* contrasena;

public:
    Comprador(/* args */);
    ~Comprador();
    char getnombre();
    int getidentificativo();
    int gettelefono();
    char getcorreo();
    char getdireccion();
    char getcontrasena();
};



#endif