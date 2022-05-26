#ifndef ADMINISTRADOR_H_
#define ADMINISTRADOR_H_


class Administrador
{
    private:
        char* nombre;
        int identificativo;
        char* contrasena;
        char* funcion;
    public:
        Administrador(char* nombre, char* contrasena, char* funcion);
        Administrador(const Administrador& a);
        ~Administrador();
        char* getNombre();
        int getIdentificativo();
        char* getContrasena();
        char* getFuncion();
};



#endif
