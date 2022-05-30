#include "Cliente.h"
#include <string.h>
#include <iostream>
using std::cout; using std::endl;

            
    Cliente::Cliente(char* nombre, int identificativo, int telefono, char* correo, char* direccion, char* contrasena) {
        this->nombre = new char[strlen(nombre)+1];
        this->identificativo = identificativo;
        this->telefono = telefono;
        this->correo = new char[strlen(correo)+1];
        this->direccion = new char[strlen(direccion)+1];
        this->contrasena = new char[strlen(contrasena)+1];
    }

    Cliente::Cliente(const Cliente& c) {
        this->nombre = new char[strlen(c.nombre)+1];
        this->identificativo = c.identificativo;
        this->telefono = c.telefono;
        this->correo = new char[strlen(c.correo)+1];
        this->direccion = new char[strlen(c.direccion)+1];
        this->contrasena = new char[strlen(c.contrasena)+1];
    }

    Cliente::~Cliente() {
        delete[] nombre;
        delete[] correo;
        delete[] direccion;
        delete[] contrasena;
    }

    void Cliente::rebajaPrecio(){
        int precio;
        cout << "Por ser miembro sin VIP no tienes rebaja en el precio por lo que el precio es:  " << precio << endl;
    }

    char* Cliente::getNombre() {
        return this->nombre;
    }
    int Cliente::getIdentificativo() {
        return this->identificativo;
    }
    int Cliente::getTelefono() {
        return this->telefono;
    }
    char* Cliente::getCorreo() {
        return this->correo;
    }
    char* Cliente::getDireccion() {
        return this->direccion;
    }
    char* Cliente::getContrasena() {
        return this->contrasena;
    }

