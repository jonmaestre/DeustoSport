#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Administrador.h"
#include "Calzado.h"
#include "Carrito.h"
#include "Compra.h"
#include "Comprador.h"
#include "MaterialDeportivo.h"
#include "Prenda.h"
#include "Suplemento.h"
#include "bbdd.h"
#include "Fecha.h"
#include "sqlite3.h"

#define PROGRAMADORES 5


// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// COMIENZO PARTE INICIAR / REGISTRARSE
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------

int inicio () {

    int* respuesta;

    printf("¿Qué desea hacer? \n");
    printf("\n");
	printf("1. Iniciar sesión\n");
	printf("2. Registrarme como nuevo cliente\n");
	printf("3. Iniciar como invitado\n");       // ------------>    cliente -> NULL
    printf("4. Iniciar sesión como administrador\n");
	printf("Pulsar 0 para salir\n");
	printf("\n");

    do {
	    printf("Opción: ");
	    fflush(stdout);
        scanf("%i", respuesta);
    } while (!(*respuesta >= 0 && *respuesta <=4));

	return *respuesta;
}


Comprador registrar (sqlite3 *db) {

    char* nombre;
    nombre = malloc(50*sizeof(char));
    int* telefono;
    telefono = malloc(1*sizeof(int));
    char* correo;
    correo = malloc(70*sizeof(char));
    char* direccion;
    direccion = malloc(80*sizeof(char));
    char* contrasena1;
    contrasena1 = malloc(25*sizeof(char));
    char* contrasena2;
    contrasena2 = malloc(25*sizeof(char));

    printf("REGISTRAR \n");
    printf("---------------------------------\n");

    printf("NOMBRE: \n");
    scanf("%c", nombre);
    printf("TELEFONO: \n");
    scanf("%i", telefono);
	printf("CORREO ELECTRÓNICO: \n");
    scanf("%c", correo);
	printf("DIRECCION: \n");
    scanf("%c", direccion);
	printf("CONTRASEÑA: \n");
    scanf("%c", contrasena1);
    printf("REPITA CONTRASEÑA: \n");
    scanf("%c", contrasena2);

    bool existe = existeComprador(db, correo);
    while (existe) {
        printf("El correo introducido ya existe. Por favor, introduzca otro. \n");
        printf("CORREO ELECTRÓNICO: \n");
        scanf("%c", correo);
        bool existe = existeComprador(db, correo);
    }

    while (&contrasena1 != &contrasena2) {
        printf("¡Vaya! Parece que ha habido un error. \n");
        printf("Vuelve a introducir la contraseña. \n");
        printf("CONTRASEÑA: \n");
        scanf("%c", contrasena1);
        printf("REPITA CONTRASEÑA: \n");
        scanf("%c", contrasena2);
    }

    registrarComprador(db, nombre, telefono, correo, direccion, contrasena1);

    Comprador comprador = obtenerComprador(db, correo);

    return comprador;
}


Comprador iniciarCliente (sqlite3 *db) {

    char* correo;
    correo = malloc(100*sizeof(char));
    char* contrasena;
    contrasena = malloc(50*sizeof(char));

    printf("INCIAR SESIÓN \n");
    printf("---------------------------------\n");

    printf("CORREO ELECTRÓNICO: \n");
    scanf("%c", correo);
	printf("CONTRASEÑA: \n");
    scanf("%c", contrasena);

    Comprador persona;

    bool existe = existeComprador(db, correo);
    if (existe == false) {
        int deNuevo;
        while (existe == false) {
            printf("¡Vaya! Parece que ha habido un error. \n");
            printf("Creemos que no está registrado en DeustoSportKit. \n");
            printf("¿Quiere registrarse o reintentar iniciar sesión?");
            printf("1. Registrarme\n");
	        printf("2. Reintentar\n");
	        printf("\n");

            do {
	            printf("Opción: ");
	            fflush(stdout);
                scanf("%i", &deNuevo);
            } while (deNuevo != 1 || deNuevo != 2);

            if (deNuevo == 1) {
                registrar (db);
            } else if (deNuevo == 2) {
                printf("CORREO ELECTRÓNICO: \n");
                scanf("%c", correo);
	            printf("CONTRASEÑA: \n");
                scanf("%c", contrasena);

                bool existe = existeComprador(db, correo);

                if (existe == false) {
                    printf("¡Vaya! Parece que ha habido un error. \n");
                    return NULL;
                } else {
                    persona = obtenerComprador (db, correo);
                    char* correito = persona.correo;
                    char* contra = persona.contrasena;
                    while (contrasena != contra && correo == correito) {
                        printf("¡Vaya! Parece que ha habido un error. \n");
                        printf("Vuelve a meter los datos. \n");
                        printf("CORREO ELECTRÓNICO: \n");
                        scanf("%c", correo);
	                    printf("CONTRASEÑA: \n");
                        scanf("%c", contrasena);
                        Comprador persona = obtenerComprador (db, correo);
                        char* correito = persona.correo;
                        char* contra = persona.contrasena;
                    }

                    return persona;
                }
            } 
        }

    } else {

        persona = obtenerComprador (db, correo);
        char* correito = persona.correo;
        char* contra = persona.contrasena;
        while (contrasena != contra && correo == correito) {
            printf("¡Vaya! Parece que ha habido un error. \n");
            printf("Vuelve a meter los datos. \n");
            printf("CORREO ELECTRÓNICO: \n");
            scanf("%c", correo);
	        printf("CONTRASEÑA: \n");
            scanf("%c", contrasena);
            Comprador persona = obtenerComprador (db, correo);
            char* correito = persona.correo;
            char* contra = persona.contrasena;
        }
        return persona;
    }
}


Admin iniciarAdmin (sqlite3 *db) {

    // revisar los char*
    int* identificativo;
    identificativo = malloc(10*sizeof(int));
    char* contrasena;
    contrasena = malloc(30*sizeof(char*));
    int* respuestaPregunta;
    respuestaPregunta = malloc(1*sizeof(int));
    // si realmente son administradores, sabrán la respuesta a una pregunta. siempre la misma.

    printf("INCIAR SESIÓN \n");
    printf("---------------------------------\n");

    printf("IDENTIFICATIVO PROPIO: \n");
    scanf("%i", identificativo);
	printf("CONTRASEÑA: \n");
    scanf("%c", contrasena);
    printf("¿CUÁNTOS PROGRAMADORES HAY EN 'DeustoSportKit'?: \n");
    scanf("%i", &respuestaPregunta);

    if (respuestaPregunta != PROGRAMADORES) {
        printf("¡ERROR! Tú no eres un administrador.");
        return NULL;            // si returnea null, se cierra el programa

    } else {
        bool existe;
        existe = bool existeAdmin(db, identificativo);
        if (existe == false) {
            printf("¡USTED NO ES UN ADMINISTRADOR! \n");
            return NULL;
        } else {
            Admin administrador;
            administrador = obtenerAdmin(db, id);
            if (administrador.contrasena != contrasena) {
                printf("Algo ha ido mal. Vuelva a introducir los datos.\n");
                printf("Recuerde que solo tiene una oportunidad más \n");
                printf("\n");
                printf("CONTRASEÑA: \n");
                scanf("%c", contrasena);
                if (administrador.contrasena != contrasena) {
                    printf("¡ERROR!\n");
                    return NULL;
                }
            } else {
                printf("Bienvenido, %s", administrador.nombre);
                return administrador;
            }
        }
    }
}

// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// FIN PARTE INICIAR / REGISTRARSE
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
// INICIO PARTE GRAFICA DE ELECCIONES
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
// Para inicio de la Zapatillas hombre
int* iniciarZapatillasH(sqlite3 *db)
{
    int *respuesta;
    printf("Estas son las zapatillas para hombre que tenemos en este momento: \n");
    printf("\n");
    printf("0. Ver zapatillas para hombre \n")
    printf("1. Ver carrito \n");
    printf("2. Volver a la pagina de atras \n");

    fflush(stdout);
    scanf("%i", respuesta);

    if (*respuesta == 0) 
    {

        ////<<<<<<<<------------------------------------Intxausti simplemente printea desde la base de datos productos las Zapatillas para hombre que metas

        int *respuesta0;

        printf("¿Te interesa alguna? \n");
        printf("0. Comprar \n")
        printf("1. Volver a la ventana principal \n"); 
        scanf("%i", respuesta0); 
    } 
    else if (*respuesta == 1)
    {
        iniciarCarrito(db);
    }
    else if (*respuesta == 2)
    {
        ventaPrincipal(db);
    }

    return respuesta;
}


// Para inicio de la zapatillas mujer

int* iniciarZapatillasM(sqlite3 *db)
{
    int *respuesta;
    printf("Estas son las zapatillas para mujer que tenemos en este momento: \n");
    printf("\n");

    printf("0. Ver carrito \n");
    if (*respuesta == 0)
    {
        iniciarCarrito(db);
    }

    printf("1. Volver a la pagina de atras \n");
    if (*respuesta == 1)
    {
        ventaPrincipal(db);
    }


    ////<<<<<<<<------------------------------------Intxausti simplemente printea desde la base de datos productos las Zapatillas para mujer que metas

    fflush(stdout);
    scanf("%i", respuesta);
	return respuesta;
}


// Para inicio de ropa hombre

int* iniciarRopaH(sqlite3 *db)
{
    int* respuesta;
    printf("Esta es la ropa para hombre que tenemos en este momento: \n");
    printf("\n");

    printf("0. Ver carrito \n");
    if (*respuesta == 0)
    {
        iniciarCarrito(db);
    }

    printf("1. Volver a la pagina de atras \n");
    if (*respuesta == 1)
    {
        ventaPrincipal(db);
    }


    ////<<<<<<<<------------------------------------Intxausti simplemente printea desde la base de datos productos ropa de hombre que metas

    fflush(stdout);
    scanf("%i", respuesta);
	return respuesta;
}


// Para inicio de ropa mujer

int* iniciarRopaM(sqlite3 *db)
{
    int* respuesta;
    printf("Esta es la ropa para mujer que tenemos en este momento: \n");
    printf("\n");

    printf("0. Ver carrito \n");
    if (*respuesta == 0)
    {
        iniciarCarrito(db);
    }

    printf("1. Volver a la pagina de atras \n");
    if (*respuesta == 1)
    {
        ventaPrincipal(db);
    }


    ////<<<<<<<<------------------------------------Intxausti simplemente printea desde la base de datos productos ropa de mujer que metas

    fflush(stdout);
    scanf("%i", respuesta);
	return respuesta;
}

// Para inicio de ropa mujer

int* iniciarSuplementos(sqlite3 *db)
{
    int* respuesta;
    printf("Estos son los suplementos deportivos que tenemos en este momento: \n");
    printf("\n");

    printf("0. Ver carrito \n");
    if (*respuesta == 0)
    {
        iniciarCarrito(db);
    }

    printf("1. Volver a la pagina de atras \n");
    if (*respuesta == 1)
    {
        ventaPrincipal(db);
    }

    ////<<<<<<<<------------------------------------Intxausti simplemente printea desde la base de datos los suplementos deportivos deportivos

    fflush(stdout);
    scanf("%i", respuesta);
	return respuesta;
}

// Para inicio de material deportivo especifico

int* iniciarMaterialD(sqlite3 *db)
{
    int* respuesta;
    printf("Estos son los materiales deportivos especificos que tenemos en este momento: \n");
    printf("\n");

    printf("0. Ver carrito \n");
    if (*respuesta == 0)
    {
        iniciarCarrito(db);
    }

    printf("1. Volver a la pagina de atras \n");
    if (*respuesta == 1)
    {
        ventaPrincipal(db);
    }

    ////<<<<<<<<------------------------------------Intxausti simplemente printea desde la base de datos los materiales especificos deportivos deportivos

    fflush(stdout);
    scanf("%i", respuesta);
	return respuesta;
}


int* iniciarCarrito(sqlite3 *db)
{
    int* respuesta;
    printf("Estos son los productos que tienes en el carrito en este instante: \n");
    printf("\n");



    ////<<<<<<<<------------------------------------ Se necesita funcion que almacene las compras para mostrarlas
    printf("0. Volver atras \n");

    if (*respuesta == 0)
    {
        ventaPrincipal();
    }

    printf("1. Comprar \n");

    if (*respuesta == 1)
    {
        //<<<<<<<<<<------------------------------Falta funcion de comprar en la que calcule el precio
    }

    printf("2. Borrar Producto \n");

    if (*respuesta == 2)
    {
        //<<<<<<<<<<------------------------------Falta funcion de seleccionar producto y borrarlo
    }


    fflush(stdout);
    scanf("%i", respuesta);
	return respuesta;
}


int* ventaPrincipal(sqlite3 *db)
{
    int* respuesta;

    printf("¿Qué Tipo de producto esta buscando? Eliga el numero del tipo de producto que busca \n");
    printf("\n");
    printf("1. Zapatillas (Hombre)\n");
    printf("2. Zapatillas (Mujer)\n");
    printf("3. Ropa (Hombre)\n");
    printf("4. Ropa (Mujer)\n");
    printf("5. Suplementos deportivos\n");
    printf("6. Material especifico para deportes \n");
    printf("7. Ver carrito \n");

    printf("Eleccion: ");
    fflush(stdout);
    scanf("%i", respuesta);
    if (*respuesta == 1)
    {
        iniciarZapatillasH(db);
    } else if (*respuesta == 2)
    {
        iniciarZapatillasM(db);
    } else if (*respuesta == 3)
    {
        iniciarRopaH(db);
    } else if (*respuesta == 4)
    {
        iniciarRopaM(db);
    } else if (*respuesta == 5)
    {
        iniciarSuplementos(db);
    } else if (*respuesta == 6)
    {
        iniciarMaterialD(db);
    } else if (*respuesta == 7)
    {
        iniciarCarrito(db);
    }
    return respuesta;
}


///////<<<<<<<<<<<<<-------------------------------------------------------------Creo que haria falta una funcion mas que lea el objeto que esta seleccionado pero hay que esperar a la base de datos productos para verlo

///// <<<<<----------- La funcion del producto te daria las opciones: AÑADIR AL CARRITO---VOLVER ATRAS----COMPRAR AHORA


//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
// FIN PARTE GRAFICA DE ELECCIONES
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
// COMIENZO MÉTODOS DE ADMINISTRADORES
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------


void ventanaAdmin (sqlite3 *db, Admin administrador) {
    
    int* eleccion;
    eleccion = malloc(1*sizeof(int));

    do {

        printf("1. Meter un producto nuevo \n");
        printf("2. Recargar un producto \n");
        printf("3. Eliminar un producto");
        printf("Pulsa 0 para salir");
        printf("\n");

        do {
            printf("¿Qué desea hacer, %i? \n", administrador);
            scanf("%i", eleccion);
        } while (!(*eleccion>= 0 && *eleccion<=3));

        if (*eleccion == 0) {
            printf("¡Que pase un buen día!");
        } else if (eleccion == 1) {
            crearProducto(db, administrador);
        } else if (eleccion == 2) {
            recargarProoducto (db, administrador);
        } else if (eleccion == 3) {
            eliminarProducto (db, administrador);
        }

    } while (*eleccion != 0);
}

void crearProducto (sqlite3 *db, Admin administrador) {

    int* tipo;
    tipo = malloc(10*sizeof(int));
    printf("¿Qué tipo de producto desea meter en la base de datos? \n");
    printf("1. Prenda \n");
    printf("2. Calzado \n");
    printf("3. Material deportivo \n");
    printf("4. Suplemento \n");

    do {
        printf("TIPO: \n");
        scanf("%i", tipo);
    } while (!(*tipo >= 1 && *tipo <= 4));

    char* typeProd;
    typeProd = (char*)malloc(10*sizeof(char));

    if (*tipo == 1) {
        
        typeProd[0] = 'P';
        typeProd[1] = 'r';
        typeProd[2] = 'e';
        typeProd[3] = 'n';
        typeProd[4] = 'd';
        typeProd[5] = 'a';

        agregarProducto(db, typeProd);

        char *nombre, *tipoPren, *color, *talla;
        float *precio;
        int *sexo, *stock;


        printf("CREACIÓN DE PRENDA \n");
        printf("------------------------- \n");

        printf("NOMBRE: \n");
        nombre = (char*)malloc(20*sizeof(char));
        scanf("%s", nombre);

        printf("TIPO: \n");
        tipoPren = (char*)malloc(15*sizeof(char));
        scanf("%s", tipoPren);

        printf("COLOR: \n");
        color = (char*)malloc(10*sizeof(char));
        scanf("%s", color);

        printf("TALLA: \n");
        talla = (char*)malloc(3*sizeof(char));
        scanf("%s", talla);

        printf("PRECIO: \n");
        precio = malloc(1*sizeof(float));
        scanf("%f", precio);

        do {
            printf("SEXO: \n");
            printf("0. Hombre \n");
            printf("1. Mujer \n");
            sexo = malloc(1*sizeof(int));
            scanf("%i", sexo);
        } while (sexo != 0 || sexo != 1);

        printf("STOCK: \n");
        stock = malloc(1*sizeof(int));
        scanf("%i", stock);

        agregarPrenda(db, nombre, tipoPren, color, talla, *precio, *sexo, *stock);
    
    } else if (*tipo == 2) {
        
        typeProd[0] = 'C';
        typeProd[1] = 'a';
        typeProd[2] = 'l';
        typeProd[3] = 'z';
        typeProd[4] = 'a';
        typeProd[5] = 'd';
        typeProd[6] = 'o';

        agregarProducto(db, typeProd);

        char *nombre, *tipoCal, *color;
        float *precio, *talla;
        int *sexo, *stock;


        printf("CREACIÓN DE CALZADO \n");
        printf("------------------------- \n");

        printf("NOMBRE: \n");
        nombre = (char*)malloc(20*sizeof(char));
        scanf("%s", nombre);

        printf("TIPO: \n");
        tipoCal = (char*)malloc(15*sizeof(char));
        scanf("%s", tipoCal);

        printf("COLOR: \n");
        color = (char*)malloc(10*sizeof(char));
        scanf("%s", color);

        printf("TALLA: \n");
        talla = malloc(1*sizeof(int));
        scanf("%s", talla);

        printf("PRECIO: \n");
        precio = malloc(1*sizeof(float));
        scanf("%f", precio);

        do {
            printf("SEXO: \n");
            printf("0. Hombre \n");
            printf("1. Mujer \n");
            sexo = malloc(1*sizeof(int));
            scanf("%i", sexo);
        } while (sexo != 0 || sexo != 1);

        printf("STOCK: \n");
        stock = malloc(1*sizeof(int));
        scanf("%i", stock);

        agregarCalzado(db, nombre, tipoCal, color, talla, *precio, *sexo, *stock);
    
    } else if (*tipo == 3) {
        
        typeProd[0] = 'M';
        typeProd[1] = 'a';
        typeProd[2] = 't';
        typeProd[3] = 'e';
        typeProd[4] = 'r';
        typeProd[5] = 'D';
        typeProd[6] = 'e';
        typeProd[7] = 'p';
        typeProd[8] = 'o';
        typeProd[9] = 'r';

        agregarProducto(db, typeProd);

        char *nombre, *tipoMat, *color, *talla, *deporte;
        float *precio;
        int *stock;


        printf("CREACIÓN DE MATERIAL DEPORTIVO \n");
        printf("------------------------- \n");

        printf("NOMBRE: \n");
        nombre = (char*)malloc(20*sizeof(char));
        scanf("%s", nombre);

        printf("TIPO: \n");
        tipoMat = (char*)malloc(15*sizeof(char));
        scanf("%s", tipoMat);

        printf("COLOR: \n");
        color = (char*)malloc(10*sizeof(char));
        scanf("%s", color);

        printf("TALLA: \n");
        talla = (char*)malloc(1*sizeof(char));
        scanf("%s", talla);

        printf("PRECIO: \n");
        precio = malloc(1*sizeof(float));
        scanf("%f", precio);

        printf("DEPORTE: \n");
        deporte = (char*)malloc(20*sizeof(char));
        scanf("%s", deporte);

        printf("STOCK: \n");
        stock = malloc(1*sizeof(int));
        scanf("%i", stock);

        agregarMD(db, nombre, tipoMat, color, talla, *precio, deporte, *stock);
    
    } else if (*tipo == 4) {
        
        typeProd[0] = 'S';
        typeProd[1] = 'u';
        typeProd[2] = 'p';
        typeProd[3] = 'l';
        typeProd[4] = 'e';
        typeProd[5] = 'm';
        typeProd[6] = 'e';
        typeProd[7] = 'n';
        typeProd[8] = 't';
        typeProd[9] = 'o';

        agregarProducto(db, typeProd);

        char *nombre, *tipoSup, *color;
        float *precio;
        int *stock;


        printf("CREACIÓN DE SUPLEMENTO \n");
        printf("------------------------- \n");

        printf("NOMBRE: \n");
        nombre = (char*)malloc(25*sizeof(char));
        scanf("%s", nombre);

        printf("TIPO: \n");
        tipoSup = (char*)malloc(15*sizeof(char));
        scanf("%s", tipoSup);

        printf("PRECIO: \n");
        precio = malloc(1*sizeof(float));
        scanf("%f", precio);

        printf("STOCK: \n");
        stock = malloc(1*sizeof(int));
        scanf("%i", stock);

        agregarSupl(db, nombre, tipoSup, *stock, *precio);
    }

} 

void recargarProoducto (sqlite3 *db, Admin administrador) {

    int* iden;
    iden = malloc(1*sizeof(int));

    printf("¿Qué producto quiere recargar? \n");
    printf("Por favor, esciba el identificativo del producto.\n");
    printf("IDENTIFICATIVO: \n");
    scanf("%i", iden);

    bool existe = existeProducto (db, *iden);

    while (existe == false) {
        printf("El producto indicado no existe. \n");
        printf("Por favor, esciba el identificativo del producto.\n");
        printf("IDENTIFICATIVO: \n");
        scanf("%i", iden);
    }

    char tipo = obtenerTipoProducto (db, *iden);
    // C -> calzado		M -> material	P -> prenda 	S -> suplemento

    int* cantidad;
    cantidad = malloc(1*sizeof(int));

    printf("Cuántas unidades desea recargar? \n");
    printf("CANTIDAD: \n");
    scanf("%i", cantidad);

    if (tipo == 'C') {
        subirStockCalzado (db, *id, *cant);
    } else if (tipo == 'M') {
        subirStockMD (db, *id, *cant);
    } else if (tipo == 'P') {
        subirStockCPrenda (db, *id, *cant);
    } else if (tipo == 'S') {
        subirStockSupl (db, *id, *cant);
    }
    
}


void eliminarProducto (sqlite3 *db, Admin administrador) {

    int* iden;
    printf("¿Qué producto quiere eliminar de DeustoSportKit? \n");
    printf("Por favor, esciba el identificativo del producto.\n");
    printf("IDENTIFICATIVO: \n");
    scanf("%i", iden);

    bool existe = existeProducto (db, *iden);

    while (existe == false) {
        printf("El producto indicado no existe. \n");
        printf("Por favor, esciba el identificativo del producto.\n");
        printf("IDENTIFICATIVO: \n");
        scanf("%i", iden);
    }

    char tipo = obtenerTipoProducto (db, *iden);
    // C -> calzado		M -> material	P -> prenda 	S -> suplemento

    if (tipo == 'C') {
        int* eleccion;

        Calzado cal =  obtenerCalzado (db, *iden);
        printf("El calzado %i es: %s. \n", iden, cal.nombre);
        printf("¿Está seguro de que quiere eliminarlo?\n");
        printf("1. Sí \n");
        printf("2. No \n");
        scanf("%i", eleccion);

        if (*eleccion == 1) {
            eliminarCalzado(db, iden);
            printf("Producto eliminado correctamente. \n");
        }

    } else if (tipo == 'M') {
        int* eleccion;

        MaterialDeportivo matD =  obtenerMaterial (db, *iden);
        printf("El material deportivo %i es: %s. \n", iden, matD.nombre);
        printf("¿Está seguro de que quiere eliminarlo?\n");
        printf("1. Sí \n");
        printf("2. No \n");
        scanf("%i", eleccion);

        if (*eleccion == 1) {
            eliminarMD(db, iden);
            printf("Producto eliminado correctamente. \n");
        }

    } else if (tipo == 'P') {
        int* eleccion;

        Prenda pren =  obtenerPrenda (db, *iden);
        printf("La prenda %i es: %s. \n", iden, pren.nombre);
        printf("¿Está seguro de que quiere eliminarlo?\n");
        printf("1. Sí \n");
        printf("2. No \n");
        scanf("%i", eleccion);

        if (*eleccion == 1) {
            eliminarPrenda(db, iden);
            printf("Producto eliminado correctamente. \n");
        }
    } else if (tipo == 'S') {
        int* eleccion;

        Suplemento sup =  obtenerSuplemento (db, *iden);
        printf("El suplemento %i es: %s. \n", iden, sup.nombre);
        printf("¿Está seguro de que quiere eliminarlo?\n");
        printf("1. Sí \n");
        printf("2. No \n");
        scanf("%i", eleccion);

        if (*eleccion == 1) {
            eliminarSupl(db, iden);
            printf("Producto eliminado correctamente. \n");
        }
    }

}



//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
// FIN PARTE MÉTODOS DE ADMINISTRADORES
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------




//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
// MAIN
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------



int main (void) {

    sqlite3 *db;
	int result = sqlite3_open("BaseDatos.db", &db);

    printf("BIENVENIDX A DEUSTOSPORTKIT :) \n");

    int comienzo;
    comienzo = inicio();

    if (comienzo == 0) {

        printf("¡Pasa un buen día!");

    } else if (comienzo == 1 || comienzo == 2 || comienzo == 3) {

        Comprador comprador;

        if (comienzo == 1) {
            comprador = iniciarCliente (db);
        } else if (comienzo == 2) {
            comprador = registrar (db);
        } else {
            comprador = NULL;
        }

    } else if (comienzo == 4) {

        Admin administrador;
        administrador = iniciarAdmin (db);

        if (administrador != NULL) {
            ventanaAdmin (db, administrador);
        }

    }




}

