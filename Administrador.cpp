#include "Administrador.h"
#include "bbdd.h"

Administrador::Administrador(char* nombre, char* contrasena, char* funcion) {
    sqlite3 *db;
    this->nombre = nombre;
    this->identificativo = idMaxAdmin(db);
    this->contrasena = contrasena;
    this->funcion = new char[strlen(funcion)+1];
}

Administrador::Administrador(const Administrador& a) {
    sqlite3 *db;
    this->nombre = a.nombre;
    this->identificativo = idMaxAdmin(db);
    this->contrasena = a.contrasena;
    this->funcion = new char[strlen(a.funcion)+1];
}

Administrador::~Administrador() {
    delete[] this->funcion;
}

char* Administrador::getNombre() {
    return this->nombre;
}

int Administrador::getIdentificativo() {
    return this->identificativo;
}

char* Administrador::getContrasena() {
    return this->contrasena;
}

char* Administrador::getFuncion() {
    return this->funcion;
}
