#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <iostream>
using namespace std;

#include "Administrador.h"
#include "Calzado.h"
#include "Carrito.h"
#include "Compra.h"
#include "Comprador.h"
#include "MaterialDeportivo.h"
#include "Prenda.h"
#include "Suplemento.h"
#include "bbdd.h"
#include "sqlite3.h"
#include "funcionesAdmin.h"

#define PROGRAMADORES 5


Administrador iniciarAdmin (sqlite3 *db) {

    // revisar los char*
    int identificativo;
    char* contrasena;
    int respuestaPregunta;
    // si realmente son administradores, sabrán la respuesta a una pregunta. siempre la misma.

    cout << "INCIAR SESIÓN \n" << endl;
    cout << "---------------------------------\n" << endl;

    // Recoge la informacion del administrador para asegurarse de que es un administrador del sistema
    cout << "IDENTIFICATIVO PROPIO: " << endl;
    cin >> identificativo;
	cout << "CONTRASEÑA: " << endl;
    cin >> *contrasena;
    cout << "¿CUÁNTOS PROGRAMADORES HAY EN 'DeustoSportKit'?: " << endl;
    cin >> respuestaPregunta;

    
    if (respuestaPregunta != PROGRAMADORES) {
        // Si no se sabe la respuesta a la pregunta, no será un administrador
        cout << "¡ERROR! Tú no eres un administrador." << endl;
        return NULL;            // si returnea null, se cierra el programa

    } else {
        // Hay que asegurarse de que el aministrador con el identificativo metida existe.
        bool existe;
        existe = existeAdmin(db, identificativo);
        if (existe == false) {
            // Si el identificativo no está en la base de datos, el administrador no existe.
            cout << "¡USTED NO ES UN ADMINISTRADOR! " << endl;
            return NULL;
        } else {
            // Si lo es, habrá que coger el administrador con dicho identificativo y comparar la informacion de este con la introducida
            Administrador administrador = obtenerAdmin(db, identificativo);

            if (strcmp(administrador.getContrasena(), contrasena) != 0) {
                // Si no coincide la contrasena, podra volver a introducirla una vez mas.
                cout << "Algo ha ido mal. Vuelva a introducir los datos." << endl;
                cout << "Recuerde que solo tiene una oportunidad más " << endl;
                cout << "CONTRASEÑA: " << endl;
                cin >> *contrasena;

                if (strcmp(administrador.getContrasena(), contrasena) != 0) {
                    // En caso de fallar la segunda vez, se devolvera null para que no siga adelante
                    cout << "¡ERROR!" << endl;
                    return NULL;
                } else {
                    // Si coincide,  se devulve el administrador
                    cout << "Bienvenido, " << administrador.getNombre() << endl;
                    return administrador;
                }

            } else {
                // Si coincide, se devuelve el administrador
                cout << "Bienvenido, " << administrador.getNombre() << endl;
                return administrador;
            }
        }
    }
}


// Esta funcion sera para que el administrador meta nuevos productos en la base de datos
void crearProductoAdmin (sqlite3 *db, Administrador administrador) {

    // Tendra que elegir el tipo de producto que insertar
    int tipo;
    cout << "¿Qué tipo de producto desea meter en la base de datos? " << endl;
    cout << "1. Prenda " << endl;
    cout << "2. Calzado " << endl;
    cout << "3. Material deportivo " << endl;
    cout << "4. Suplemento " << endl;

    // El programa seguira pidiendo el tipo hasta que meta entre 1 y 4
    do {
        cout << "TIPO: " << endl;
        cin >> tipo;
    } while (!(tipo >= 1 && tipo <= 4));

    char* typeProd;
    typeProd = new char[10+1];

    if (tipo == 1) {
        
        strcpy(typeProd, "Prenda");

        agregarProducto(db, typeProd);

        char *nombre, *tipoPren, *color;
        float *precio;
        int sexo, stock, talla;

        // Preguntara de uno en uno los datos del producto
        cout << "CREACIÓN DE PRENDA " << endl;
        cout << "------------------------- " << endl;

        cout << "NOMBRE: " << endl;
        nombre = new char[20];
        cin >> *nombre;

        cout << "TIPO: " << endl;
        tipoPren = new char[15];
        cin >> *tipoPren;

        cout << "COLOR: " << endl;
        color = new char[10];
        cin >> *color;

        cout << "TALLA: " << endl;
        cin >> talla;

        cout << "PRECIO: " << endl;
        cin >> precio;

        // De sexo solo hay dos opciones, asi que en caso de no introducir los datos correctamente, se seguira preguntando
        do {
            cout << "SEXO: " << endl;
            cout << "0. Hombre " << endl;
            cout << "1. Mujer " << endl;
            cin >> sexo;
        } while (sexo != 0 || sexo != 1);

        cout << "STOCK: " << endl;
        cin >> stock;

        // Se agrega el producto a la base de datos
        agregarPrenda(db, nombre, tipoPren, color, talla, precio, sexo, stock);

        // Se libera la memoria almacenada
        delete[] nombre;
        delete[] tipoPren;
        delete[] color;
    
    } else if (tipo == 2) {
        
        strcpy(typeProd, "Calzado");

        agregarProducto(db, typeProd);

        char *nombre, *tipoCal, *color;
        float precio, talla;
        int sexo, stock;


        cout << "CREACIÓN DE CALZADO " << endl;
        cout << "------------------------- " << endl;

        cout << "NOMBRE: " << endl;
        nombre = new char[20];
        cin >> *nombre;

        cout << "TIPO: " << endl;
        tipoCal = new char[15];
        cin >> *tipoCal;

        cout << "COLOR: " << endl;
        color = new char[10];
        cin >> *color;

        cout << "TALLA: " << endl;
        cin >> talla;

        cout << "PRECIO: " << endl;
        cin >> precio;

        do {
            cout << "SEXO: " << endl;
            cout << "0. Hombre " << endl;
            cout << "1. Mujer " << endl;
            cin >> sexo;
        } while (sexo != 0 || sexo != 1);

        cout << "STOCK: " << endl;
        cin >> stock;

        agregarCalzado(db, nombre, tipoCal, color, talla, precio, sexo, stock);

        delete[] nombre;
        delete[] tipoCal;
        delete[] color;
 
    
    } else if (tipo == 3) {
        
        strcpy(typeProd, "MaterDepor");

        agregarProducto(db, typeProd);

        char *nombre, *tipoMat, *color, *deporte;
        float precio;
        int stock, talla;


        cout << "CREACIÓN DE MATERIAL DEPORTIVO " << endl;
        cout << "------------------------- " << endl;

        cout << "NOMBRE: " << endl;
        nombre = new char[20];
        cin >> *nombre;

        cout << "TIPO: " << endl;
        tipoMat = new char[15];
        cin >> *tipoMat;

        cout << "COLOR: " << endl;
        color = new char[10];
        cin >> *color;

        cout << "TALLA: " << endl;
        cin >> talla;

        cout << "PRECIO: " << endl;
        cin >> precio;

        cout << "DEPORTE: " << endl;
        cin >> deporte;

        cout << "STOCK: " << endl;
        cin >> stock;

        agregarMD(db, nombre, tipoMat, color, talla, precio, deporte, stock);

        delete[] nombre;
        delete[] tipoMat;
        delete[] color;
        delete[] deporte;
    
    } else if (tipo == 4) {
        
        strcpy(typeProd, "Suplemento");

        agregarProducto(db, typeProd);

        char *nombre, *tipoSup;
        float precio;
        int stock;


        cout << "CREACIÓN DE SUPLEMENTO " << endl;
        cout << "------------------------- " << endl;

        cout << "NOMBRE: " << endl;
        nombre = new char[25];
        cin >> *nombre;

        cout << "TIPO: " << endl;
        tipoSup = new char[15];
        scin >> *tipoSup;

        cout << "PRECIO: " << endl;
        cin >> precio;

        cout << "STOCK: " << endl;
        cin >> stock;

        agregarSupl(db, nombre, tipoSup, stock, precio);

        delete[] nombre;
        delete[] tipoSup;
    }

} 

void recargarProoductoAdmin (sqlite3 *db, Administrador administrador) {

    int iden;

    cout << "¿Qué producto quiere recargar? " << endl;
    cout << "Por favor, esciba el identificativo del producto." << endl;
    cout << "IDENTIFICATIVO: " << endl;
    cin >> iden;

    bool existe = existeProducto1 (db, iden);

    while (existe == false) {
        cout << "El producto indicado no existe. " << endl;
        cout << "Por favor, esciba el identificativo del producto." << endl;
        cout << "IDENTIFICATIVO: " << endl;
        cin >> iden;
    }

    char tipo = obtenerTipoProducto (db, iden);
    // C -> calzado		M -> material	P -> prenda 	S -> suplemento

    int cantidad;

    cout << "Cuántas unidades desea recargar?" << endl;
    cout << "CANTIDAD:" << endl;
    cin >> cantidad;

    if (tipo == 'C') {
        subirStockCalzado (db, iden, cantidad);
    } else if (tipo == 'M') {
        subirStockMD (db, iden, cantidad);
    } else if (tipo == 'P') {
        subirStockCPrenda (db, iden, cantidad);
    } else if (tipo == 'S') {
        subirStockSupl (db, iden, cantidad);
    }
    
}


void eliminarProductoAdmin (sqlite3 *db, Administrador administrador) {

    int iden;
    cout << "¿Qué producto quiere eliminar de DeustoSportKit? " << endl;
    cout << "Por favor, esciba el identificativo del producto." << endl;
    cout << "IDENTIFICATIVO:" << endl;
    cin >> iden;

    bool existe = existeProducto1 (db, iden);

    while (existe == false) {
        cout << "El producto indicado no existe." << endl;
        cout << "Por favor, esciba el identificativo del producto." << endl;
        cout << "IDENTIFICATIVO: " << endl;
        cin >> iden;
    }

    char tipo = obtenerTipoProducto (db, iden);
    // C -> calzado		M -> material	P -> prenda 	S -> suplemento

    int eleccion;

    if (tipo == 'C') {

        Calzado cal =  obtenerCalzado (db, iden);
        cout << "El calzado " << iden << " es: " << cal.getNombre() << endl;
        cout << "¿Está seguro de que quiere eliminarlo?\n" << endl;
        cout << "1. Sí " << endl;
        cout << "2. No " << endl;
        cin >> eleccion;

        if (eleccion == 1) {
            eliminarCalzado(db, iden);
            cout << "Producto eliminado correctamente. " << endl;
        }

    } else if (tipo == 'M') {

        MaterialDeportivo matD =  obtenerMaterial (db, iden);
        cout << "El material deportivo " << iden << " es: " << matD.getNombre() << endl; 
        cout << "¿Está seguro de que quiere eliminarlo?" << endl;
        cout << "1. Sí " << endl;
        cout << "2. No " << endl;
        cin >> eleccion;

        if (eleccion == 1) {
            eliminarMD(db, iden);
            cout << "Producto eliminado correctamente. " << endl;
        }

    } else if (tipo == 'P') {

        Prenda pren =  obtenerPrenda (db, iden);
        cout << "La prenda " << iden << " es: " zz pren.getNombre() << endl; 
        cout << "¿Está seguro de que quiere eliminarlo?" << endl;
        cout << "1. Sí " << endl;
        cout << "2. No " << endl;
        cin >> eleccion;

        if (eleccion == 1) {
            eliminarPrenda(db, iden);
            cout << "Producto eliminado correctamente. " << endl;
        }

    } else if (tipo == 'S') {

        Suplemento sup =  obtenerSuplemento (db, iden);
        cout << "El suplemento " << iden << " es: " << sup.getNombre() << endl; 
        cout << "¿Está seguro de que quiere eliminarlo?" << endl;
        cout << "1. Sí " << endl;
        cout << "2. No " << endl;
        cin >> eleccion;

        if (eleccion == 1) {
            eliminarSupl(db, iden);
            cout << "Producto eliminado correctamente. " << endl;
        }
    }

}


void ventanaAdmin (sqlite3 *db, Administrador administrador) {
    
    int eleccion;

    do {

        cout << "1. Meter un producto nuevo " << endl;
        cout << "2. Recargar un producto " << endl;
        cout << "3. Eliminar un producto" << endl;
        cout << "Pulsa 0 para salir" << endl;

        do {
            cout << "¿Qué desea hacer, " << administrador.getNombre() << "?" <<endl;
            cin >> eleccion;
        } while (!(eleccion>= 0 && eleccion<=3));

        if (eleccion == 0) {
            cout << "¡Que pase un buen día!" << endl;
        } else if (eleccion == 1) {
            crearProductoAdmin (db, administrador);
        } else if (eleccion == 2) {
            recargarProoductoAdmin (db, administrador);
        } else if (eleccion == 3) {
            eliminarProductoAdmin (db, administrador);
        }

    } while (eleccion != 0);
}

