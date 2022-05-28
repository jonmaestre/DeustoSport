#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Administrador.h"
#include "Producto.h"
#include "bbdd.h"
#include "sqlite3.h"

#define PROGRAMADORES 5


Administrador iniciarAdmin (sqlite3 *db) {

    // revisar los char*
    int identificativo;
    char* contrasena;
    contrasena = malloc(sizeof(char)*20);
    int respuestaPregunta;
    // si realmente son administradores, sabrán la respuesta a una pregunta. siempre la misma.

    printf("INCIAR SESIÓN \n");
    printf("---------------------------------\n");

    // Recoge la informacion del administrador para asegurarse de que es un administrador del sistema
    printf("IDENTIFICATIVO PROPIO: \n");
    scanf("%i", &identificativo);
	printf("CONTRASEÑA: \n");
    scanf("%s", contrasena);
    printf("¿CUÁNTOS PROGRAMADORES HAY EN 'DeustoSportKit'?: \n");
    scanf("%i", &respuestaPregunta);

    
    if (respuestaPregunta != PROGRAMADORES) {
        // Si no se sabe la respuesta a la pregunta, no será un administrador
        printf("¡ERROR! Tú no eres un administrador. \n");
        Administrador admin;
        strcpy(admin.nombre, "nada");
        admin.identificativo = -1;
        strcpy(admin.contrasena, "nada");
        strcpy(admin.funcion, "nada");
        return admin;            // administrador falso

    } else {
        // Hay que asegurarse de que el aministrador con el identificativo metida existe.
        bool existe;
        existe = existeAdmin(db, identificativo);
        if (existe == false) {
            // Si el identificativo no está en la base de datos, el administrador no existe.
            printf("¡USTED NO ES UN ADMINISTRADOR! \n");
            Administrador admin;
            strcpy(admin.nombre, "nada");
            admin.identificativo = -1;
            strcpy(admin.contrasena, "nada");
            strcpy(admin.funcion, "nada");
            return admin;            // administrador falso
        } else {
            // Si lo es, habrá que coger el administrador con dicho identificativo y comparar la informacion de este con la introducida
            Administrador administrador = obtenerAdmin(db, identificativo);

            if (strcmp(administrador.getContrasena(), contrasena) != 0) {
                // Si no coincide la contrasena, podra volver a introducirla una vez mas.
                printf("Algo ha ido mal. Vuelva a introducir los datos. \n");
                printf("Recuerde que solo tiene una oportunidad más \n");
                printf("CONTRASEÑA: \n");
                scanf("%s", contrasena);

                if (strcmp(administrador.getContrasena(), contrasena) != 0) {
                    // En caso de fallar la segunda vez, se devolvera null para que no siga adelante
                    printf("¡ERROR!\n");
                    Administrador admin;
                    strcpy(admin.nombre, "nada");
                    admin.identificativo = -1;
                    strcpy(admin.contrasena, "nada");
                    strcpy(admin.funcion, "nada");
                    return admin;            // administrador falso
                } else {
                    // Si coincide,  se devulve el administrador
                    printf("Bienvenido, %s", administrador.nombre);
                    return administrador;
                }

            } else {
                // Si coincide, se devuelve el administrador
                printf("Bienvenido, %s", administrador.nombre);
                return administrador;
            }
        }
    }

    free(contrasena);
    contrasena = NULL;
}


// Esta funcion sera para que el administrador meta nuevos productos en la base de datos
void crearProductoAdmin (sqlite3 *db, Administrador administrador) {

    // Tendra que elegir el tipo de producto que insertar
    int tipo;
    printf("¿Qué tipo de producto desea meter en la base de datos? \n");
    printf("1. Prenda \n");
    printf("2. Calzado \n");
    printf("3. Material deportivo \n");
    printf("4. Suplemento \n");

    // El programa seguira pidiendo el tipo hasta que meta entre 1 y 4
    do {
        printf("TIPO: \n");
        scanf("%i", &tipo);
    } while (!(tipo >= 1 && tipo <= 4));

    char* typeProd;
    typeProd = malloc(sizeof(char)*11);

    if (tipo == 1) {
        
        strcpy(typeProd, "Prenda");

        agregarProducto(db, typeProd);

        char *nombre, *tipoPren, *color;
        float *precio;
        int stock, talla;

        // Preguntara de uno en uno los datos del producto
        printf("CREACIÓN DE PRENDA \n");
        printf("------------------------- \n");

        printf("NOMBRE: \n");
        nombre = malloc(sizeof(char)*20);
        scanf("%s", nombre);

        printf("TIPO: \n");
        tipoPren = malloc(sizeof(char)*20);
        scanf("%s", tipoPren);

        printf("COLOR: \n");
        color = malloc(sizeof(char)*10);
        scanf("%s", color);

        printf("TALLA: \n");
        scanf("%i", talla);

        scanf("PRECIO: \n");
        scanf("%i", precio);

        printf("STOCK: \n");
        scanf("%i", stock);

        // Se agrega el producto a la base de datos
        agregarPrenda(db, nombre, tipoPren, color, talla, precio, stock);

        // Se libera la memoria almacenada
        free(nombre);
        nombre = NULL;
        free(tipoPren);
        tipoPren = NULL;
        free(color);
        color = NULL;
    
    } else if (tipo == 2) {
        
        strcpy(typeProd, "Calzado");

        agregarProducto(db, typeProd);

        char *nombre, *tipoCal, *color;
        float precio, talla;


        printf("CREACIÓN DE CALZADO \n");
        printf("------------------------- \n");

        printf("NOMBRE: \n");
        nombre = malloc(sizeof(char)*20);
        scanf("%s", nombre);

        printf("TIPO: \n");
        tipoCal = malloc(sizeof(char)*20);
        scanf("%s", tipoCal);

        printf("COLOR: \n");
        color = malloc(sizeof(char)*10);
        scanf("%s", color);

        printf("TALLA: \n");
        scanf("%i", talla);

        scanf("PRECIO: \n");
        scanf("%i", precio);

        printf("STOCK: \n");
        scanf("%i", stock);


        agregarCalzado(db, nombre, tipoCal, color, talla, precio, stock);

        free(nombre);
        nombre = NULL;
        free(tipoCal);
        tipoCal = NULL;
        free(color);
        color = NULL;
 
    
    } else if (tipo == 3) {
        
        strcpy(typeProd, "MaterDepor");

        agregarProducto(db, typeProd);

        char *nombre, *tipoMat, *color, *deporte;
        float precio;
        int stock, talla;


        printf("CREACIÓN DE MATERIAL DEPORTIVO \n");
        printf("------------------------- \n");

        printf("NOMBRE: \n");
        nombre = malloc(sizeof(char)*20);
        scanf("%s", nombre);

        printf("TIPO: \n");
        tipoMat = malloc(sizeof(char)*20);
        scanf("%s", tipoMat);

        printf("COLOR: \n");
        color = malloc(sizeof(char)*10);
        scanf("%s", color);

        printf("TALLA: \n");
        scanf("%i", talla);

        scanf("PRECIO: \n");
        scanf("%i", precio);

        printf("DEPORTE: \n");
        deporte = malloc(sizeof(char)*15);
        scanf("%s", deporte);

        printf("STOCK: \n");
        scanf("%i", stock);

        agregarMD(db, nombre, tipoMat, color, talla, precio, deporte, stock);


        free(nombre);
        nombre = NULL;
        free(tipoMat);
        tipoMat = NULL;
        free(color);
        color = NULL;
        free(deporte);
        deporte = NULL;
    
    } else if (tipo == 4) {
        
        strcpy(typeProd, "Suplemento");

        agregarProducto(db, typeProd);

        char *nombre, *tipoSup;
        float precio;
        int stock;


        printf("CREACIÓN DE SUPLEMENTO \n");
        printf("------------------------- \n");

        printf("NOMBRE: \n");
        nombre = malloc(sizeof(char)*20);
        scanf("%s", nombre);

        printf("TIPO: \n");
        tipoSup = malloc(sizeof(char)*20);
        scanf("%s", tipoSup);

        scanf("PRECIO: \n");
        scanf("%i", precio);

        printf("STOCK: \n");
        scanf("%i", stock);

        agregarSupl(db, nombre, tipoSup, stock, precio);

        free(nombre);
        nombre = NULL;
        free(tipoSup);
        tipoSup = NULL;
    }

} 

void recargarProoductoAdmin (sqlite3 *db, Administrador administrador) {

    int iden;

    printf("¿Qué producto quiere recargar? \n");
    printf("Por favor, esciba el identificativo del producto.\n");
    printf("IDENTIFICATIVO: \n");
    scanf("%i", &iden);

    bool existe = existeProducto1 (db, iden);

    while (existe == false) {
        printf("El producto indicado no existe. \n");
        printf("Por favor, esciba el identificativo del producto.\n");
        printf("IDENTIFICATIVO: \n");
        scanf("%i", &iden);
    }

    char tipo = obtenerTipoProducto (db, iden);
    // C -> calzado		M -> material	P -> prenda 	S -> suplemento

    int cantidad;

    printf("Cuántas unidades desea recargar?\n");
    printf("CANTIDAD:\n");
    scanf("%i", &cantidad);

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
    printf("¿Qué producto quiere eliminar de DeustoSportKit? \n");
    printf("Por favor, esciba el identificativo del producto.\n");
    printf("IDENTIFICATIVO:\n");
    scanf("%i", &iden);

    bool existe = existeProducto1 (db, iden);

    while (existe == false) {
        printf("El producto indicado no existe.\n");
        printf("Por favor, esciba el identificativo del producto.\n");
        printf("IDENTIFICATIVO: \n");
        scanf("%i", &iden);
    }

    char tipo = obtenerTipoProducto (db, iden);
    // C -> calzado		M -> material	P -> prenda 	S -> suplemento

    int eleccion;

    if (tipo == 'C') {

        Calzado cal =  obtenerCalzado (db, iden);
        printf("El calzado %s es: \n", cal.nombre);
        printf("¿Está seguro de que quiere eliminarlo?\n");
        printf("1. Sí \n");
        printf("2. No \n");
        scanf("%i", eleccion);

        if (eleccion == 1) {
            eliminarCalzado(db, iden);
            printf("Producto eliminado correctamente. \n");
        }

    } else if (tipo == 'M') {

        MaterialDeportivo matD =  obtenerMaterial (db, iden);
        printf("El material deportivo %i es: ", matD.nombre); 
        printf("¿Está seguro de que quiere eliminarlo?\n");
        printf("1. Sí \n");
        printf("2. No \n");
        scanf("%i", eleccion);

        if (eleccion == 1) {
            eliminarMD(db, iden);
            printf("Producto eliminado correctamente. \n");
        }

    } else if (tipo == 'P') {

        Prenda pren =  obtenerPrenda (db, iden);
        printf("El material deportivo %i es: ", pren.nombre); 
        printf("¿Está seguro de que quiere eliminarlo?\n");
        printf("1. Sí \n");
        printf("2. No \n");
        scanf("%i", eleccion);

        if (eleccion == 1) {
            eliminarMD(db, iden);
            printf("Producto eliminado correctamente. \n");
        }

    } else if (tipo == 'S') {

        Suplemento sup =  obtenerSuplemento (db, iden);
        printf("El material deportivo %i es: ", sup.nombre); 
        printf("¿Está seguro de que quiere eliminarlo?\n");
        printf("1. Sí \n");
        printf("2. No \n");
        scanf("%i", eleccion);

        if (eleccion == 1) {
            eliminarMD(db, iden);
            printf("Producto eliminado correctamente. \n");
        }
    }

}


void ventanaAdmin (sqlite3 *db, Administrador administrador) {
    
    int eleccion;

    do {

        printf("1. Meter un producto nuevo \n");
        printf("2. Recargar un producto \n");
        printf("3. Eliminar un producto \n");
        printf("Pulsa 0 para salir \n");

        do {
            printf("¿Qué desea hacer, %s?", administrador.nombre);
            scanf("%i", eleccion)
        } while (!(eleccion>= 0 && eleccion<=3));

        if (eleccion == 0) {
            printf("¡Que pase un buen día!\n");
        } else if (eleccion == 1) {
            crearProductoAdmin (db, administrador);
        } else if (eleccion == 2) {
            recargarProoductoAdmin (db, administrador);
        } else if (eleccion == 3) {
            eliminarProductoAdmin (db, administrador);
        }

    } while (eleccion != 0);
}
