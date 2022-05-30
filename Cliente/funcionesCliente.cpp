#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <iostream>
using namespace std;



#include "Compra.h"
#include "Cliente.h"
#include "bbdd.h"
#include "sqlite3.h"
#include "funcionesCliente.h"

#define PROGRAMADORES 5

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
//Funciones
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
Comprador registrar (sqlite3 *db) {

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

    registrarComprador(db, nombre, *telefono, correo, direccion, contrasena1);

    Comprador comprador = obtenerComprador(db, correo);

    return comprador;
}


Comprador iniciarCliente (sqlite3 *db) {

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


    Comprador* persona;

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
                *persona = registrar (db);
                return persona;
            } else if (deNuevo == 2) {
                cout << "CORREO ELECTRÓNICO: \n" << endl;
                cin >> correo;
                cout << "CONTRASEÑA: \n" << endl;
                cin >> contrasena;

                bool existe = existeComprador(db, correo);

                if (existe == false) {
                    cout << "¡Vaya! Parece que ha habido un error. \n" << endl;
                    return NULL;
                } else {
                    *persona = obtenerComprador (db, correo);
                    char* correito = (*persona)->correo;
                    char* contra = *Comprador::persona ;
                    while (contrasena != contra && correo == correito) {
                        cout << "¡Vaya! Parece que ha habido un error. \n" << endl;
                        cout << "Vuelve a meter los datos. \n" << endl;
                        cout << "CORREO ELECTRÓNICO: \n" << endl;
                        cin >> correo;
                        cout << "CONTRASEÑA: \n" << endl;
                        cin >> contrasena;
                        *persona = obtenerComprador (db, correo);
                        char* correito = (persona)->Comprador::correo;
                        char* contra = (persona)->Comprador::contrasena;
                    }

                    return persona;
                }
            } 
        }

    } else {
        
        Cliente persona = obtenerComprador (db, correo);
        char* correito = persona.correo;
        char* contra = persona.contrasena;
        while (contrasena != contra && correo == correito) {
            cout << "¡Vaya! Parece que ha habido un error. \n" << endl;
            cout << "Vuelve a meter los datos. \n" << endl;
            cout << "CORREO ELECTRÓNICO: \n" << endl;
            cin >> correo;
            cout << "CONTRASEÑA: \n" << endl;
            cin >> contrasena;

            persona = obtenerComprador (db, correo);
            char* correito = (*persona)->correo;
            char* contra = (*persona)->contrasena;
        }
        return persona;
    }
}

// Funcion para añadir al carrito el elemento deseado


void devolverCompra (sqlite3 *db, Comprador comprador, int idProducto, int idCompra) {

    bool existe;
    //existe = existeCompra (db, idCompra);

    if (existe == false) {
        printf("¡Error! Esa compra no se ha hecho nunca. \n");
    } else {

        Compra compra =  obtenerCompra (db, idCompra, comprador, idProducto);
        int cantidad = compra->cantidad;

        eliminarCompra (db, idCompra, comprador->identificativo, idProducto);

        char tipo = obtenerTipoProducto (db, idProducto);
        // C -> calzado		M -> material	P -> prenda 	S -> suplemento

        if (tipo == 'C') {
            subirStockCalzado (db, idProducto, cantidad);
        } else if (tipo == 'M') {
            subirStockMD (db, idProducto, cantidad);
        } else if (tipo == 'P') {
            subirStockPrenda (db, idProducto, cantidad);
        } 
        cout << "Trámites de devolución completados. \n" << endl;
    }

}
