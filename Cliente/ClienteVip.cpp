#include "ClienteVip.h"
#include <string.h>

#include <iostream>
using std::cout; using std::endl;
using namespace std;

ClienteVip::ClienteVip(char* nombre, int identificativo, int telefono, char* correo, char* direccion, char* contrasena, char* nivel): Cliente(nombre, identificativo, telefono, correo, direccion, contrasena)
{
	this->nivel = new char[strlen(nivel)+1];
}

ClienteVip::ClienteVip(const ClienteVip &CV) : Cliente(CV)
{
	this->nivel = CV.nivel;
}

ClienteVip::~ClienteVip()
{
	delete[] nivel;
}


char* ClienteVip::getNivel()
{
	return this->nivel;
}


int ClienteVip::rebajaPrecio(int precio)
{
	char* nivel=this->nivel;
	if (strcmp(nivel, "standar") == 0) {
		precio=precio*0.95;
		cout << "Por ser miembro standar tienes una rebaja del 5 por ciento en el precio por lo que el precio es:  " << precio << endl;


	}else{
		precio=precio*0.85;
		cout << "Por no ser miembro standar tienes una rebaja del 15 por ciento en el precio por lo que el precio es:  " << precio << endl;
	}

	return precio;
}

