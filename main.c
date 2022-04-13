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

    registrarComprador(db, nombre, *telefono, correo, direccion, contrasena1);

    Comprador comprador = obtenerComprador(db, correo);

    return comprador;
}


Comprador* iniciarCliente (sqlite3 *db) {

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

                    return &persona;
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
        return &persona;
    }
}


Admin* iniciarAdmin (sqlite3 *db) {

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
    scanf("%i", respuestaPregunta);

    if (*respuestaPregunta != PROGRAMADORES) {
        printf("¡ERROR! Tú no eres un administrador.");
        return NULL;            // si returnea null, se cierra el programa

    } else {
        bool existe;
        existe = existeAdmin(db, *identificativo);
        if (existe == false) {
            printf("¡USTED NO ES UN ADMINISTRADOR! \n");
            return NULL;
        } else {
            Admin administrador;
            administrador = obtenerAdmin(db, *identificativo);
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
                return &administrador;
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


int** añadirACarrito (sqlite3 *db, int** arrayProductos, int sizeArray, int idProd, int cant) {

    arrayProductos[sizeArray][0] = idProd;
    arrayProductos[sizeArray][1] = cant;

    return arrayProductos;
}


void comprarCarrito (sqlite3 *db, Comprador comprador, int** arrayProductos, int sizeArray) {
    
    int idCarrito = ultimoCarrito (db);
    int i = 0;
    while (i < sizeArray) {
        Compra compra = {idCarrito, arrayProductos[i][0], comprador.identificativo, arrayProductos[i][1]};
        void agregarCompra(db, compra);
    }

    Carrito carritoNuevo = crearCarrito(db, idCarrito, comprador.identificativo);
    void agregarCarrito(db, carrito);
}


void eliminarDeCarrito (sqlite3 *db, int** arrayProductos, int sizeArray, int indice) {

}


void iniciarCarrito(sqlite3 *db, Comprador comprador) {
    int* respuesta;

    // -------------------------------- INICIALIZARLOS
    int** arrayProductos;
    int sizeArray;

    int num = 0;
    while (num < sizeArray) {
        int idPr = arrayProductos[i][0];
        char type = obtenerTipoProducto (db, arrayProductos[i][0]);
        // C -> calzado		M -> material	P -> prenda 	S -> suplemento
        if (type == 'C') {
            Calzado calz = obtenerCalzado (db, arrayProductos[i][0]);
            printf("%i: %s. X%i \n", num+1, calz.nombre, arrayProductos[i][1]);
        } else if (type == 'M') {
            MaterialDeportivo matD =  obtenerMaterial (db, arrayProductos[i][0]);
            printf("%i: %s. X%i \n", num+1, matD.nombre, arrayProductos[i][1]);
        } else if (type == 'P') {
            Prenda pren = obtenerPrenda (db, arrayProductos[i][0]);
            printf("%i: %s. X%i \n", num+1, pren.nombre, arrayProductos[i][1]);
        } else if (type == 'S') {
            Suplemento supl = obtenerSuplemento(db, arrayProductos[i][0]);
            printf("%i: %s. X%i \n", num+1, supl.nombre, arrayProductos[i][1]);
        }
    }

    printf("¿Qué deseas hacer? \n");
    printf("1. Realizar la compra del carrito entero \n");
    printf("2. Borrar un producto del carrito");
    printf("Pulsa 0 para salir.");
    printf("\n");

    do {
        printf("ELECCION: ");
        fflush(stdout);
        scanf("%i", respuesta);
    } while (respuesta < 0 || respuesta > 2);
    

    if (*respuesta == 1)
    {
        comprarCarrito(db, comprador, arrayProductos, sizeArray);
    }
    else if (*respuesta == 2)
    {
        printf("¿Qué producto deseas eliminar? \n");

        int* indice;
        do {
            printf("ÍNDICE: ");
            fflush(stdout);
            scanf("%i", indice);
        } while (indice < 0 || indice > size);

        eliminarDeCarrito (db, arrayProductos, sizeArray, indice);
    }

    free(respuesta);
    respuesta = NULL;
}



// Para inicio de la Zapatillas hombre

void iniciarZapatillasH(sqlite3 *db)
{
    int *respuesta;
    printf("Estas son las zapatillas para hombre que tenemos en este momento: \n");
    printf("\n");
    printf("1. Ver zapatillas para hombre \n");
    printf("2. Ver carrito \n");
    printf("Pulsa 0 para salir. \n");

    do {
        printf("ELECCION: ");
        fflush(stdout);
        scanf("%i", respuesta);
    } while (respuesta < 0 || respuesta > 2);

    if (*respuesta == 1)
    {
        int size=sizeCalzadoH(db);
        int i=0;
        Calzado* listaCalzadoH=showCalzadoH(db);
        do{
            printf("%i. %s %s Precio:%2f\n",(i+1),listaCalzadoH[i].tipo,listaCalzadoH[i].nombre,listaCalzadoH[i].precio);
        }while (i<size);
        
        int *respuesta1;
        respuesta1 = malloc(sizeof(int));

        printf("¿Te interesa alguna? \n");
        printf("1. Comprar \n");
        printf("Pulsa 0 para salir.  \n"); 

        do {
            scanf("%i", respuesta1);
            printf("\n"); 
        } while (respuesta1 != 0 || respuesta1 != 1);

        if (respuesta1 == 1) {

            int* zapatillaHom;
            zapatillaHom = malloc(sizeof(int));

            printf ("¿Cuál? Por favor, indique su código. \n");
            scanf("%i"), zapatillaHom;

            // METODO COMPRAR
            free(zapatillaHom);
            zapatillaHom = NULL;
        }

        
        free(listaCalzadoH);
        listaCalzadoH=NULL;
    }
    else if (*respuesta == 2)
    {
        iniciarCarrito(db);
    }

    free(respuesta);
    respuesta = NULL;
}


// Para inicio de la zapatillas mujer

void iniciarZapatillasM(sqlite3 *db)
{
    int *respuesta;
    printf("Estas son las zapatillas para mujer que tenemos en este momento: \n");
    printf("\n");
    printf("1. Ver zapatillas para mujer \n");
    printf("2. Ver carrito \n");
    printf("Pulsa 0 para salir. \n");

    do {
        printf("ELECCION: ");
        fflush(stdout);
        scanf("%i", respuesta);
    } while (respuesta < 0 || respuesta > 2);

    if (*respuesta == 1)
    {
        int size=sizeCalzadoM(db);
        int i=0;
        Calzado* listaCalzadoM=showCalzadoM(db);
        do{
            printf("%i. %s %s Precio:%2f\n",(i+1),listaCalzadoM[i].tipo,listaCalzadoM[i].nombre,listaCalzadoM[i].precio);
        }while (i<size);

        int *respuesta1;
        respuesta1 = malloc(sizeof(int));

        printf("¿Te interesa alguna? \n");
        printf("1. Comprar \n");
        printf("Pulsa 0 para salir.  \n"); 

        do {
            scanf("%i", respuesta1);
            printf("\n"); 
        } while (respuesta1 != 0 || respuesta1 != 1);

        if (respuesta1 == 1) {

            int* zapatillaMuj;
            zapatillaMuj = malloc(sizeof(int));

            printf ("¿Cuál? Por favor, indique su código. \n");
            scanf("%i", zapatillaMuj);

            // METODO COMPRAR
        }

        free(respuesta1);
        respuesta1 = NULL;
        free(listaCalzadoM);
        listaCalzadoM=NULL;
    }
    else if (*respuesta == 2)
    {
        iniciarCarrito(db);
    }


    free(respuesta);
    respuesta = NULL;
}


// Para inicio de ropa hombre

void iniciarRopaH(sqlite3 *db)
{
    int* respuesta;
    printf("Esta es la ropa para hombre que tenemos en este momento: \n");
    printf("\n");
    printf("1. Ver ropa para hombre \n");
    printf("2. Ver carrito \n");
    printf("Pulsa 0 para salir. \n");

    do {
        printf("ELECCION: ");
        fflush(stdout);
        scanf("%i", respuesta);
    } while (respuesta < 0 || respuesta > 2);

    if (*respuesta == 1)
    {
        int size=sizePrendaH(db);
        int i=0;
        Prenda* listaPrendaH=showPrendaH(db);
        do{
            printf("%i. %s %s Precio:%2f\n",(i+1),listaPrendaH[i].tipo,listaPrendaH[i].nombre,listaPrendaH[i].precio);
        }while (i<size);


        int *respuesta1;
        respuesta1 = malloc(sizeof(int));

        printf("¿Te interesa alguna? \n");
        printf("1. Comprar \n");
        printf("Pulsa 0 para salir.  \n"); 

        do {
            scanf("%i", respuesta1);
            printf("\n"); 
        } while (respuesta1 != 0 || respuesta1 != 1);

        if (respuesta1 == 1) {

            int* ropaHombre;
            ropaHombre = malloc(sizeof(int));

            printf ("¿Cuál? Por favor, indique su código. \n");
            scanf("%i", ropaHombre);

            // METODO COMPRAR
        }

        free(respuesta1);
        respuesta1 = NULL;
        free(listaPrendaH);
        listaPrendaH=NULL;
    }
    if (*respuesta == 2)
    {
        iniciarCarrito(db);
    }


    free(respuesta);
    respuesta = NULL;
}


// Para inicio de ropa mujer

void iniciarRopaM(sqlite3 *db)
{
    int* respuesta;
    printf("Esta es la ropa para mujer que tenemos en este momento: \n");
    printf("\n");
    printf("1. Ver ropa para mujer \n");
    printf("2. Ver carrito \n");
    printf("Pulsa 0 para salir. \n");

    do {
        printf("ELECCION: ");
        fflush(stdout);
        scanf("%i", respuesta);
    } while (respuesta < 0 || respuesta > 2);
    

    if (*respuesta == 1)
    {

        
        int size=sizePrendaM(db);
        int i=0;
        Prenda* listaPrendaM=showPrendaM(db);
        do{
            printf("%i. %s %s Precio:%2f\n",(i+1),listaPrendaM[i].tipo,listaPrendaM[i].nombre,listaPrendaM[i].precio);
        }while (i<size);

        int *respuesta1;
        respuesta1 = malloc(sizeof(int));

        printf("¿Te interesa alguna? \n");
        printf("1. Comprar \n");
        printf("Pulsa 0 para salir.  \n"); 

        do {
            scanf("%i", respuesta1);
            printf("\n"); 
        } while (respuesta1 != 0 || respuesta1 != 1);

        if (respuesta1 == 1) {

            int* ropaMujer;
            ropaMujer = malloc(sizeof(int));

            printf ("¿Cuál? Por favor, indique su código. \n");
            scanf("%i", ropaMujer);

            // METODO COMPRAR
        }

        free(respuesta1);
        respuesta1 = NULL;
        free(listaPrendaM);
        listaPrendaM=NULL;

    }
    else if (*respuesta == 2)
    {
        iniciarCarrito(db);
    }

    free(respuesta);
    respuesta = NULL;
}


// Para inicio de suplementos

void iniciarSuplementos(sqlite3 *db)
{
    int* respuesta;
    printf("Estos son los suplementos deportivos que tenemos en este momento: \n");
    printf("\n");
    printf("1. Ver suplementos \n");
    printf("2. Ver carrito \n");
    printf("Pulsa 0 para salir. \n");

    do {
        printf("ELECCION: ");
        fflush(stdout);
        scanf("%i", respuesta);
    } while (respuesta < 0 || respuesta > 2);
    

    if (*respuesta == 1)
    {

        int size=sizeSupl(db);
        int i=0;
        Suplemento* listaSupl=showSupl(db);
        do{
            printf("%i. %s %s Precio:%2f\n",(i+1),listaSupl[i].tipo,listaSupl[i].nombre,listaSupl[i].precio);
        }while (i<size);

        int *respuesta1;
        respuesta1 = malloc(sizeof(int));

        printf("¿Te interesa alguna? \n");
        printf("1. Comprar \n");
        printf("Pulsa 0 para salir.  \n"); 

        do {
            scanf("%i", respuesta1);
            printf("\n"); 
        } while (respuesta1 != 0 || respuesta1 != 1);

        if (respuesta1 == 1) {

            int* suplem;
            suplem = malloc(sizeof(int));

            printf ("¿Cuál? Por favor, indique su código. \n");
            scanf("%i", suplem);

            // METODO COMPRAR
        }

        free(respuesta1);
        respuesta1 = NULL;
        free(listaSupl);
        listaSupl=NULL;
    }
    else if (*respuesta == 2)
    {
        iniciarCarrito(db);
    }

    free(respuesta);
    respuesta = NULL;
}

// Para inicio de material deportivo especifico

void iniciarMaterialD(sqlite3 *db)
{
    int* respuesta;
    printf("Estos son los materiales deportivos especificos que tenemos en este momento: \n");
    printf("\n");
    printf("1. Ver material deportivo \n");
    printf("2. Ver carrito \n");
    printf("Pulsa 0 para salir. \n");

    do {
        printf("ELECCION: ");
        fflush(stdout);
        scanf("%i", respuesta);
    } while (respuesta < 0 || respuesta > 2);
    

    if (*respuesta == 1)
    {
        int size=sizeMD(db);
        int i=0;
        MaterialDeportivo* listaMD=showMD(db);
        do{
            printf("%i. %s %s Precio:%2f\n",(i+1),listaMD[i].tipo,listaMD[i].nombre,listaMD[i].precio);
        }while (i<size);

        int *respuesta1;
        respuesta1 = malloc(sizeof(int));

        printf("¿Te interesa alguna? \n");
        printf("1. Comprar \n");
        printf("Pulsa 0 para salir.  \n"); 

        do {
            scanf("%i", respuesta1);
            printf("\n"); 
        } while (respuesta1 != 0 || respuesta1 != 1);

        if (respuesta1 == 1) {

            int* matDep;
            matDep = malloc(sizeof(int));

            printf ("¿Cuál? Por favor, indique su código. \n");
            scanf("%i", matDep);

            // METODO COMPRAR
        }

        free(respuesta1);
        respuesta1 = NULL;
        free(listaMD);
        listaMD=NULL;
    }
    else if (*respuesta == 2)
    {
        iniciarCarrito(db);
    }

    free(respuesta);
    respuesta = NULL;
}


void ventaPrincipal(sqlite3 *db, Comprador comprador)
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
    printf("Pulsa 0 para salir. \n");

    do {
        printf("ELECCION: ");
        fflush(stdout);
        scanf("%i", respuesta);
    } while (respuesta < 1 || respuesta > 7);
    
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
    } else if (*respuesta == 0) 
    {
        printf("¡Que pase un buen día!");
    }
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


void crearProductoAdmin (sqlite3 *db, Admin administrador) {

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
        } while (*sexo != 0 || *sexo != 1);

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
        scanf("%f", talla);

        printf("PRECIO: \n");
        precio = malloc(1*sizeof(float));
        scanf("%f", precio);

        do {
            printf("SEXO: \n");
            printf("0. Hombre \n");
            printf("1. Mujer \n");
            sexo = malloc(1*sizeof(int));
            scanf("%i", sexo);
        } while (*sexo != 0 || *sexo != 1);

        printf("STOCK: \n");
        stock = malloc(1*sizeof(int));
        scanf("%i", stock);

        agregarCalzado(db, nombre, tipoCal, color, *talla, *precio, *sexo, *stock);
    
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

void recargarProoductoAdmin (sqlite3 *db, Admin administrador) {

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
        subirStockCalzado (db, *iden, *cantidad);
    } else if (tipo == 'M') {
        subirStockMD (db, *iden, *cantidad);
    } else if (tipo == 'P') {
        subirStockCPrenda (db, *iden, *cantidad);
    } else if (tipo == 'S') {
        subirStockSupl (db, *iden, *cantidad);
    }
    
}


void eliminarProductoAdmin (sqlite3 *db, Admin administrador) {

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
        printf("El calzado %i es: %s. \n", *iden, cal.nombre);
        printf("¿Está seguro de que quiere eliminarlo?\n");
        printf("1. Sí \n");
        printf("2. No \n");
        scanf("%i", eleccion);

        if (*eleccion == 1) {
            eliminarCalzado(db, *iden);
            printf("Producto eliminado correctamente. \n");
        }

    } else if (tipo == 'M') {
        int* eleccion;

        MaterialDeportivo matD =  obtenerMaterial (db, *iden);
        printf("El material deportivo %i es: %s. \n", *iden, matD.nombre);
        printf("¿Está seguro de que quiere eliminarlo?\n");
        printf("1. Sí \n");
        printf("2. No \n");
        scanf("%i", eleccion);

        if (*eleccion == 1) {
            eliminarMD(db, *iden);
            printf("Producto eliminado correctamente. \n");
        }

    } else if (tipo == 'P') {
        int* eleccion;

        Prenda pren =  obtenerPrenda (db, *iden);
        printf("La prenda %i es: %s. \n", *iden, pren.nombre);
        printf("¿Está seguro de que quiere eliminarlo?\n");
        printf("1. Sí \n");
        printf("2. No \n");
        scanf("%i", eleccion);

        if (*eleccion == 1) {
            eliminarPrenda(db, *iden);
            printf("Producto eliminado correctamente. \n");
        }
    } else if (tipo == 'S') {
        int* eleccion;

        Suplemento sup =  obtenerSuplemento (db, *iden);
        printf("El suplemento %i es: %s. \n", *iden, sup.nombre);
        printf("¿Está seguro de que quiere eliminarlo?\n");
        printf("1. Sí \n");
        printf("2. No \n");
        scanf("%i", eleccion);

        if (*eleccion == 1) {
            eliminarSupl(db, *iden);
            printf("Producto eliminado correctamente. \n");
        }
    }

}


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
            printf("¿Qué desea hacer, %s? \n", administrador.nombre);
            scanf("%i", eleccion);
        } while (!(*eleccion>= 0 && *eleccion<=3));

        if (*eleccion == 0) {
            printf("¡Que pase un buen día!");
        } else if (*eleccion == 1) {
            crearProductoAdmin (db, administrador);
        } else if (*eleccion == 2) {
            recargarProoductoAdmin (db, administrador);
        } else if (*eleccion == 3) {
            eliminarProductoAdmin (db, administrador);
        }

    } while (*eleccion != 0);
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
            comprador = *iniciarCliente (db);
            ventaPrincipal(db, comprador);
        } else if (comienzo == 2) {
            comprador = *registrar (db);
            ventaPrincipal(db, comprador)
        } else {
            comprador = NULL;
            ventaPrincipal(db, comprador)
        }

    } else if (comienzo == 4) {

        Admin administrador;
        administrador = *iniciarAdmin (db);

        if (administrador != NULL) {
            ventanaAdmin (db, administrador);
        }

    }




}

