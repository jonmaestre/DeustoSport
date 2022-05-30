#include "CompradorVip.h"
#include<string.h>

#include <iostream>
using std::cout; using std::endl;
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


int CompradorVip::rebajaPrecio(int precio)
{
	char* nivel=this->nivel;
	if(nivel=="standar"){
		precio=precio*0.95;
		cout << "Por ser miembro standar tienes una rebaja del 5 por ciento en el precio por lo que el precio es:  " << precio << endl;


	}else{
		precio=precio*0.85;
		cout << "Por no ser miembro standar tienes una rebaja del 15 por ciento en el precio por lo que el precio es:  " << precio << endl;
	}
}

