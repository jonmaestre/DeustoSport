#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Administrador.h"
#include "Estructuras.h"
#include "bbdd.h"
#include "sqlite3.h"

#define PROGRAMADORES 5


Administrador iniciarAdmin (sqlite3 *db) {
    int result = sqlite3_open("BasedeDatos.db", &db);
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
    scanf("%s", &contrasena);
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

    } else if (respuestaPregunta == PROGRAMADORES) {
        // Hay que asegurarse de que el aministrador con el identificativo metida existe.
        int existe;
        existe = existeAdmin(db, identificativo);
        if (existe == 0) {
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
            Administrador admin2 = obtenerAdmin(db, identificativo);

            if (strcmp(admin2.contrasena, contrasena) != 0) {
                // Si no coincide la contrasena, podra volver a introducirla una vez mas.
                printf("Algo ha ido mal. Vuelva a introducir los datos. \n");
                printf("Recuerde que solo tiene una oportunidad más \n");
                printf("CONTRASEÑA: \n");
                scanf("%s", contrasena);

                if (strcmp(admin2.contrasena, contrasena) != 0) {
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
                    printf("Bienvenido, %s", admin2.nombre);
                    return admin2;
                }

            } else {
                // Si coincide, se devuelve el administrador
                printf("Bienvenido, %s", admin2.nombre);
                return admin2;
            }
        }
    }

    free(contrasena);
    contrasena = NULL;
    result = sqlite3_close(db);
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



        char *nombre, *tipoPren, *color;
        float precio;
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
        scanf("%i", &talla);

        printf("PRECIO: \n");
        scanf("%f", &precio);

        printf("STOCK: \n");
        scanf("%i", &stock);

        // Se agrega el producto a la base de datos
        agregarPrenda(db, nombre, tipoPren, color, talla, precio, stock);
        int id=obtenerIdProducto(db,nombre);
        Prenda p=obtenerPrenda(db,id);
        entradasNuevasPrenda(p,administrador);

        // Se libera la memoria almacenada
        free(nombre);
        nombre = NULL;
        free(tipoPren);
        tipoPren = NULL;
        free(color);
        color = NULL;
    
    } else if (tipo == 2) {
        
        strcpy(typeProd, "Calzado");


        char *nombre, *tipoCal, *color;
        float precio;
        int stock, talla;


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
        scanf("%i", &talla);

        printf("PRECIO: \n");
        scanf("%f", &precio);

        printf("STOCK: \n");
        scanf("%i", &stock);


        agregarCalzado(db, nombre, tipoCal, color, talla, precio, stock);
        int id=obtenerIdProducto(db,nombre);
        Calzado c=obtenerCalzado(db,id);
        entradasNuevasCalzado(c,administrador);

        free(nombre);
        nombre = NULL;
        free(tipoCal);
        tipoCal = NULL;
        free(color);
        color = NULL;
 
    
    } else if (tipo == 3) {
        
        strcpy(typeProd, "MaterDepor");

        

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
        scanf("%i", &talla);

        printf("PRECIO: \n");
        scanf("%f", &precio);

        printf("DEPORTE: \n");
        deporte = malloc(sizeof(char)*15);
        scanf("%s", deporte);

        printf("STOCK: \n");
        scanf("%i", &stock);

        agregarMD(db, nombre, tipoMat, color, talla, precio, deporte, stock);
        int id=obtenerIdProducto(db,nombre);
        MaterialDeportivo MD=obtenerMaterial(db,id);
        entradasNuevasMD(MD,administrador);


        free(nombre);
        nombre = NULL;
        free(tipoMat);
        tipoMat = NULL;
        free(color);
        color = NULL;
        free(deporte);
        deporte = NULL;
    
    }

} 

void recargarProoductoAdmin (sqlite3 *db, Administrador administrador) {

    int iden;

    printf("¿Qué producto quiere recargar? \n");
    printf("Por favor, esciba el identificativo del producto.\n");
    printf("IDENTIFICATIVO: \n");
    scanf("%i", &iden);

    bool existe = existeProducto (db, iden);

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
        subirStockPrenda (db, iden, cantidad);
    } 
    
}


void eliminarProductoAdmin (sqlite3 *db, Administrador administrador) {

    int iden;
    printf("¿Qué producto quiere eliminar de DeustoSportKit? \n");
    printf("Por favor, esciba el identificativo del producto.\n");
    printf("IDENTIFICATIVO:\n");
    scanf("%i", &iden);

    bool existe = existeProducto (db, iden);

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
        scanf("%i", &eleccion);

        if (eleccion == 1) {
            eliminarCalzado(db, iden);
            printf("Producto eliminado correctamente. \n");
        }

    } else if (tipo == 'M') {

        MaterialDeportivo matD =  obtenerMaterial (db, iden);
        printf("El material deportivo %s es: ", matD.nombre); 
        printf("¿Está seguro de que quiere eliminarlo?\n");
        printf("1. Sí \n");
        printf("2. No \n");
        scanf("%i", &eleccion);

        if (eleccion == 1) {
            eliminarMD(db, iden);
            printf("Producto eliminado correctamente. \n");
        }

    } else if (tipo == 'P') {

        Prenda pren =  obtenerPrenda (db, iden);
        printf("El material deportivo %s es: ", pren.nombre); 
        printf("¿Está seguro de que quiere eliminarlo?\n");
        printf("1. Sí \n");
        printf("2. No \n");
        scanf("%i", &eleccion);

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
            scanf("%i", &eleccion);
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

void entradasNuevasCalzado(Calzado cal, Administrador administrador){
        FILE* f;
        f=fopen("nuevosProductos.txt","w");
        fprintf(f,"Nuevo calzado añadido por %s",administrador.nombre);
        fprintf(f,"%s//%s//%s",cal.nombre,cal.color,cal.tipo);
        fclose(f);

}

void entradasNuevasMD(MaterialDeportivo MD, Administrador administrador){
        FILE* f;
        f=fopen("nuevosProductos.txt","w");
        fprintf(f,"Nuevo Material Deportivo añadido por %s",administrador.nombre);
        fprintf(f,"%s//%s//%s",MD.nombre,MD.color,MD.tipo);
        fclose(f);

}

void entradasNuevasPrenda(Prenda Prenda, Administrador administrador){
        FILE* f;
        f=fopen("nuevosProductos.txt","w");
        fprintf(f,"Nueva prenda añadido por %s",administrador.nombre);
        fprintf(f,"%s//%s//%s",Prenda.nombre,Prenda.color,Prenda.tipo);
        fclose(f);

}


