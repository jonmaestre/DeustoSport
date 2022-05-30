#include "Comprador.h"
#include <string.h>
#include <iostream>
using std::cout; using std::endl;

            
    Comprador::Comprador(char* nombre, int identificativo, int telefono, char* correo, char* direccion, char* contrasena) {
        this->nombre = new char[strlen(nombre)+1];
        this->identificativo = identificativo;
        this->telefono = telefono;
        this->correo = new char[strlen(correo)+1];
        this->direccion = new char[strlen(direccion)+1];
        this->contrasena = new char[strlen(contrasena)+1];
    }

    Comprador::Comprador(const Comprador& c) {
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

    void Comprador::rebajaPrecio(){
        int precio;
        cout << "Por ser miembro sin VIP no tienes rebaja en el precio por lo que el precio es:  " << precio << endl;
    }

    char* Comprador::getNombre() {
        return this->nombre;
    }
    int Comprador::getIdentificativo() {
        return this->identificativo;
    }
    int Comprador::getTelefono() {
        return this->telefono;
    }
    char* Comprador::getCorreo() {
        return this->correo;
    }
    char* Comprador::getDireccion() {
        return this->direccion;
    }
    char* Comprador::getContrasena() {
        return this->contrasena;
    }

