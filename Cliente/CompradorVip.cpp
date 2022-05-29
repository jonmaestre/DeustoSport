#include "CompradorVip.h"
#include<string.h>

#include <iostream>
using namespace std;

CompradorVip::CompradorVip(char* nombre, int identificativo, int telefono, char* correo, char* direccion, char* contrasena, char* nivel): Comprador(nombre, identificativo, telefono, correo, direccion, contrasena)
{
	this->nivel = new char[strlen(nivel)+1];
}

CompradorVip::CompradorVip(const CompradorVip &CV) : Comprador(CV)
{
	this->nivel = CV.nivel;
}

CompradorVip::~CompradorVip()
{
	delete[] nivel;
}


char* CompradorVip::getNivel()
{
	return this->nivel;
}


void CompradorVip::funcion()
{
}

