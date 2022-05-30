#ifndef CLIENTE_H_
#define CLIENTE_H_



class Cliente
{
private:
    char* nombre;
    int identificativo;
    int telefono;
    char* correo;
    char* direccion;
    char* contrasena;

public:
    Cliente(char* nombre, int identificativo, int telefono, char* correo, char* direccion, char* contrasena);
    Cliente(const Cliente& c);
    virtual ~Cliente();
    
    virtual void rebajaPrecio();

    char* getNombre();
    int getIdentificativo();
    int getTelefono();
    char* getCorreo();
    char* getDireccion();
    char* getContrasena();
};



#endif