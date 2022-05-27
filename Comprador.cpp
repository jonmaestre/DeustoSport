#include "Comprador.h"

namespace usuario
{
            
    Comprador::Comprador(char* nombre, int identificativo, int telefono, char* correo, char* direccion, char* contrasena) {
        this->nombre = new char[strlen(nombre)+1];
        this->identificativo = identificativo;
        this->telefono = telefono;
        this->correo = new char[strlen(correo)+1];
        this->direccion = new char[strlen(direccion)+1];
        this->contrasena = new char[strlen(contrasena)+1];
    }

    Comprador(const Comprador& c) {
        this->nombre = new char[strlen(c.nombre)+1];
        this->identificativo = c.identificativo;
        this->telefono = c.telefono;
        this->correo = new char[strlen(c.correo)+1];
        this->direccion = new char[strlen(c.direccion)+1];
        this->contrasena = new char[strlen(c.contrasena)+1];
    }

    Comprador::~Comprador() {
        delete[] nombre;
        delete[] correo;
        delete[] direccion;
        delete[] contrasena;
    }

    char getNombre() {
        return this->nombre;
    }
    int getIdentificativo() {
        return this->identificativo;
    }
    int getTelefono() {
        return this->telefono;
    }
    char getCorreo() {
        return this->correo;
    }
    char getDireccion() {
        return this->direccion;
    }
    char getContrasena() {
        return this->contrasena;
    }
}
