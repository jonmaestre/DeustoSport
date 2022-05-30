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
    Comprador(char* nombre, int identificativo, int telefono, char* correo, char* direccion, char* contrasena);
    Comprador(const Comprador& c);
    virtual ~Comprador();
    
    virtual void rebajaPrecio();

    char* getNombre();
    int getIdentificativo();
    int getTelefono();
    char* getCorreo();
    char* getDireccion();
    char* getContrasena();
};



#endif