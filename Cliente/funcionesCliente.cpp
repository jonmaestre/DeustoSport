#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <iostream>
#include <dirent.h>

//#include "Estructuras.h"
#include "Comprita.h"
#include "Cliente.h"
#include "bbdd.h"
#include "sqlite3.h"

#define PROGRAMADORES 5

using namespace std;
using std::stoi;
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
//Funciones
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
Cliente registrar (sqlite3 *db) {

    // Reserva el espacio en memoria para cda uno de los aspectos a registrar
    char* nombre;
    
    char* telefono;
    
    char* correo;
    
    char* direccion;
    
    char* contrasena1;
    
    char* contrasena2;
    


    cout << "REGISTRAR \n" << endl;
    cout << "---------------------------------\n" << endl;


    //Registra los aspectos que se piden y guarda las repuestas 
    
    cout << "NOMBRE: \n" << endl;
    cin >> nombre;
    cout << "TELEFONO: \n" << endl;
    cin >> telefono;
    cout << "CORREO ELECTRÓNICO: \n" << endl;
    cin >> correo;
    cout << "DIRECCION: \n" << endl;
    cin >> direccion;
    cout << "CONTRASEÑA: \n" << endl;
    cin >> contrasena1;
    cout <<"REPITA CONTRASEÑA: \n" << endl;
    cin >> contrasena2;

    //Comprueba si existe Un usario con el correo ya registrado 
    bool existe = existeComprador(db, correo);
    while (existe) {
        cout << "El correo introducido ya existe. Por favor, introduzca otro. \n" << endl;
        cout << "CORREO ELECTRÓNICO: \n" << endl;
        cin >> correo;
        bool existe = existeComprador(db, correo);
    }

    //En caso de no escribir la misma contraseña en Contraseña y en repita contraseña pide que se vuelva a escribir
    while (&contrasena1 != &contrasena2) {
        cout << "¡Vaya! Parece que ha habido un error. \n" << endl;
        cout << "Vuelve a introducir la contraseña. \n" << endl;
        cout << "CONTRASEÑA: \n" << endl;
        cin >> contrasena1;
        cout << "REPITA CONTRASEÑA: \n" << endl;
        cin >> contrasena2;
    }

    int tel=stoi(telefono);
    registrarComprador(db, nombre, tel, correo, direccion, contrasena1, true);
    int iden=maxIDComprador(db);
    Cliente *comprador = new Cliente(nombre,iden,tel,correo,direccion,contrasena1);

    return *comprador;
}


Cliente iniciarCliente (sqlite3 *db) {

    //En caso de que el cliente ya este registrado guarda spacio en memoria para el correo y contraseña
    char* correo;
    
    char* contrasena;
    

    cout << "INCIAR SESIÓN \n" << endl;
    cout << "---------------------------------\n" << endl;

    //Se pide su correo y contraseña y los guarda
    cout << "CORREO ELECTRÓNICO: \n" << endl;
    cin >> correo;
    cout << "CONTRASEÑA: \n" << endl;
    cin >> contrasena;


    Cliente *persona;
    Comprador per;

    //En caso de que no encuentre la informacion introducida pide que se registre o reintente meter la informacion de usuario
    bool existe = existeComprador(db, correo);
    if (existe == false) {
        char deNuevo;
        while (existe == false) {
            cout << "¡Vaya! Parece que ha habido un error. \n" << endl;
            cout << "Creemos que no está registrado en DeustoSportKit. \n" << endl;
            cout << "¿Quiere registrarse o reintentar iniciar sesión?" << endl;
            cout << "1. Registrarme\n" << endl;
            cout << "2. Reintentar\n" << endl;
            cout << "\n" << endl;

            do {
                cout << "Opción: " << endl;
                cin >>  &deNuevo;
            } while (deNuevo != 1 || deNuevo != 2);

            if (deNuevo == 1) {
                *persona = registrar(db);
                return *persona;
            } else if (deNuevo == 2) {
                cout << "CORREO ELECTRÓNICO: \n" << endl;
                cin >> correo;
                cout << "CONTRASEÑA: \n" << endl;
                cin >> contrasena;

                bool existe = existeComprador(db, correo);

                if (existe == false) {
                    cout << "¡Vaya! Parece que ha habido un error. \n" << endl;
                    Cliente *clienteMal=new Cliente("",-1,0,"","","");
                    return *clienteMal;
                } else {
                    per = obtenerComprador (db, correo);
                    char* correito = per.correo;
                    char* contra = per.contrasena ;
                    while (contrasena != contra && correo == correito) {
                        cout << "¡Vaya! Parece que ha habido un error. \n" << endl;
                        cout << "Vuelve a meter los datos. \n" << endl;
                        cout << "CORREO ELECTRÓNICO: \n" << endl;
                        cin >> correo;
                        cout << "CONTRASEÑA: \n" << endl;
                        cin >> contrasena;
                        per = obtenerComprador (db, correo);
                        char* correito = per.correo;
                        char* contra = per.contrasena;
                    }
                    Cliente *cliente=new Cliente(per.nombre,per.identificativo,per.telefono,per.correo,per.direccion,per.contrasena);
                    return *cliente;
                }
            } 
        }
    } else {
        
        per = obtenerComprador (db, correo);
        char* correito = per.correo;
        char* contra = per.contrasena;
        while (contrasena != contra && correo == correito) {
            cout << "¡Vaya! Parece que ha habido un error. \n" << endl;
            cout << "Vuelve a meter los datos. \n" << endl;
            cout << "CORREO ELECTRÓNICO: \n" << endl;
            cin >> correo;
            cout << "CONTRASEÑA: \n" << endl;
            cin >> contrasena;

            per = obtenerComprador (db, correo);
            char* correito = per.correo;
            char* contra = per.contrasena;
        }
        Cliente *cliente=new Cliente(per.nombre,per.identificativo,per.telefono,per.correo,per.direccion,per.contrasena);
        return *cliente;
    }
}

