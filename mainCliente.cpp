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
#include "sqlite3.h"

#define PROGRAMADORES 5


int inicio () {

    int* respuesta;

    printf("¿Qué desea hacer? \n");
    printf("\n");
	printf("1. Iniciar sesión\n");
	printf("2. Registrarme como nuevo cliente\n");
	printf("3. Iniciar como invitado\n");       // ------------>    cliente -> NULL
	printf("Pulsar 0 para salir\n");
	printf("\n");

    do {
	    printf("Opción: ");
	    fflush(stdout);
        scanf("%i", respuesta);
    } while (!(*respuesta >= 0 && *respuesta <=4));

	return *respuesta;
}
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
//Funciones
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
Comprador registrar (sqlite3 *db) {

    // Reserva el espacio en memoria para cda uno de los aspectos a registrar
    char* nombre;
    nombre -> malloc(50*sizeof(char));
    int* telefono;
    telefono -> malloc(1*sizeof(int));
    char* correo;
    correo -> malloc(70*sizeof(char));
    char* direccion;
    direccion -> malloc(80*sizeof(char));
    char* contrasena1;
    contrasena1 -> malloc(25*sizeof(char));
    char* contrasena2;
    contrasena2 -> malloc(25*sizeof(char));

    printf("REGISTRAR \n");
    printf("---------------------------------\n");

    //Registra los aspectos que se piden y guarda las repuestas 
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

    //Comprueba si existe Un usario con el correo ya registrado 
    bool existe = existeComprador(db, correo);
    while (existe) {
        printf("El correo introducido ya existe. Por favor, introduzca otro. \n");
        printf("CORREO ELECTRÓNICO: \n");
        scanf("%c", correo);
        bool existe = existeComprador(db, correo);
    }

    //En caso de no escribir la misma contraseña en Contraseña y en repita contraseña pide que se vuelva a escribir
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

    //En caso de que el cliente ya este registrado guarda spacio en memoria para el correo y contraseña
    char* correo;
    correo -> malloc(100*sizeof(char));
    char* contrasena;
    contrasena -> malloc(50*sizeof(char));

    printf("INCIAR SESIÓN \n");
    printf("---------------------------------\n");

    //Se pide su correo y contraseña y los guarda
    printf("CORREO ELECTRÓNICO: \n");
    scanf("%c", correo);
	printf("CONTRASEÑA: \n");
    scanf("%c", contrasena);

    Comprador* persona;

    //En caso de que no encuentre la informacion introducida pide que se registre o reintente meter la informacion de usuario
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
                *persona = registrar (db);
                return persona;
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
                    *persona = obtenerComprador (db, correo);
                    char* correito = (*persona)->correo;
                    char* contra = (*persona)->contrasena;
                    while (contrasena != contra && correo == correito) {
                        printf("¡Vaya! Parece que ha habido un error. \n");
                        printf("Vuelve a meter los datos. \n");
                        printf("CORREO ELECTRÓNICO: \n");
                        scanf("%c", correo);
	                    printf("CONTRASEÑA: \n");
                        scanf("%c", contrasena);
                        *persona = obtenerComprador (db, correo);
                        char* correito = (persona)->Comprador::correo;
                        char* contra = (persona)->Comprador::contrasena;
                    }

                    return persona;
                }
            } 
        }

    } else {
        
        *persona = obtenerComprador (db, correo);
        char* correito = (*persona)->correo;
        char* contra = (*persona)->contrasena;
        while (contrasena != contra && correo == correito) {
            printf("¡Vaya! Parece que ha habido un error. \n");
            printf("Vuelve a meter los datos. \n");
            printf("CORREO ELECTRÓNICO: \n");
            scanf("%c", correo);
	        printf("CONTRASEÑA: \n");
            scanf("%c", contrasena);
            *persona = obtenerComprador (db, correo);
            char* correito = (*persona)->correo;
            char* contra = (*persona)->contrasena;
        }
        return persona;
    }
}

// Funcion para añadir al carrito el elemento deseado
void anadirACarrito (sqlite3 *db, int** arrayProductos, int sizeArray, int idProd, int cant) {

    arrayProductos[sizeArray][0] = idProd;
    arrayProductos[sizeArray][1] = cant;

}

// Lo que se añadidp al carrito se compra 
void comprarCarrito (sqlite3 *db, Comprador comprador, int** arrayProductos, int sizeArray) {
    
    int idCarrito = ultimoCarrito (db);
    int i = 0;
    while (i < sizeArray) {
        Compra compra = {idCarrito, arrayProductos[i][0], comprador->identificativo, arrayProductos[i][1]};
        agregarCompra(db, compra);
    }

    Carrito carritoNuevo = crearCarrito(db, idCarrito, comprador->identificativo);
    agregarCarrito(db, carritoNuevo);

    verTicket (db, idCarrito);
    printf("Necesitará la información del ticket en caso de devoluciones. ");
}


//Elimina lo que este añadido al carrito 
void eliminarDeCarrito (sqlite3 *db, int** arrayProductos, int* sizeArray, int indice) {

    indice = indice - 1;
    int i;
    for(i = indice; i<i-1; i++){
        arrayProductos[i][0]= arrayProductos[i+1][0];
        arrayProductos[i][1]= arrayProductos[i+1][1];
    }
    *sizeArray -= 1;

}

// 
int* iniciarCarrito(sqlite3 *db, Comprador comprador, int* sizeArray, int** arrayProductos) {
    int* respuesta;

    int num = 0;
    int i = 0;
    while (num < *sizeArray) {
        int idPr = arrayProductos[i][0];
        char type = obtenerTipoProducto (db, arrayProductos[i][0]);
        // C -> calzado		M -> material	P -> prenda 	S -> suplemento
        if (type == 'C') {
            Calzado calz = obtenerCalzado (db, arrayProductos[i][0]);
            printf("%i: %s. X%i \n", num+1, calz->nombre, arrayProductos[i][1]);
        } else if (type == 'M') {
            MaterialDeportivo matD =  obtenerMaterial (db, arrayProductos[i][0]);
            printf("%i: %s. X%i \n", num+1, matD->nombre, arrayProductos[i][1]);
        } else if (type == 'P') {
            Prenda pren = obtenerPrenda (db, arrayProductos[i][0]);
            printf("%i: %s. X%i \n", num+1, pren->nombre, arrayProductos[i][1]);
        } else if (type == 'S') {
            Suplemento supl = obtenerSuplemento(db, arrayProductos[i][0]);
            printf("%i: %s. X%i \n", num+1, supl->nombre, arrayProductos[i][1]);
        }
        i++;
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
    } while (*respuesta < 0 || *respuesta == 2);
    

    if (*respuesta == 1)
    {
        comprarCarrito(db, comprador, arrayProductos, *sizeArray);
    }
    else if (*respuesta == 2)
    {
        printf("¿Qué producto deseas eliminar? \n");

        int* indice;
        do {
            printf("ÍNDICE: ");
            fflush(stdout);
            scanf("%i", indice);
        } while (indice < 0 || indice > sizeArray);

        eliminarDeCarrito (db, arrayProductos, sizeArray, *indice);
    }

    return (respuesta);
}


void devolverCompra (sqlite3 *db, Comprador comprador, int idProducto, int idCompra) {

    bool existe;
    //existe = existeCompra (db, idCompra);

    if (existe == false) {
        printf("¡Error! Esa compra no se ha hecho nunca. \n");
    } else {

        Compra compra =  obtenerCompra (db, idCompra, comprador->identificativo, idProducto);
        int cantidad = compra->cantidad;

        eliminarCompra (db, idCompra, comprador->identificativo, idProducto);

        char tipo = obtenerTipoProducto (db, idProducto);
        // C -> calzado		M -> material	P -> prenda 	S -> suplemento

        if (tipo == 'C') {
            subirStockCalzado (db, idProducto, cantidad);
        } else if (tipo == 'M') {
            subirStockMD (db, idProducto, cantidad);
        } else if (tipo == 'P') {
            subirStockCPrenda (db, idProducto, cantidad);
        } else if (tipo == 'S') {
            subirStockSupl (db, idProducto, cantidad);
        }

        printf("Trámites de devolución completados. \n");
    }

}


//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
// INICIO PARTE GRAFICA DE ELECCIONES
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------


// Para inicio de la Zapatillas hombre

void iniciarZapatillasH(sqlite3 *db, Comprador comprador, int** arrayProductos, int sizeArray)
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
    } while ( *respuesta < 0 || *respuesta >=2);

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
        } while (*respuesta1 != 0 || *respuesta1 != 1);

        if (*respuesta1 == 1) {

            int zapatillaHom;

            printf ("¿Cuál? Por favor, indique su código. \n");
            scanf("%i", &zapatillaHom);

            int cant;

            printf ("¿Cuántas zapatillas desea? \n");
            scanf("%i", &cant);

            if (&comprador == NULL) {
                printf("Primero debes iniciar sesión. \n");
                comprador = *iniciarCliente (db);
            }

            anadirACarrito (db, arrayProductos, sizeArray, zapatillaHom, cant);
            sizeArray -= 1;
        }

        
        free(listaCalzadoH);
        listaCalzadoH=NULL;
    }
    else if (*respuesta == 2)
    {
        iniciarCarrito(db, comprador, &sizeArray, arrayProductos);
    }

    free(respuesta);
    respuesta = NULL;
}


// Para inicio de la zapatillas mujer

void iniciarZapatillasM(sqlite3 *db, Comprador comprador, int** arrayProductos, int sizeArray)
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
    } while (respuesta < 0 || *respuesta > 2);

    if (*respuesta == 1)
    {
        int size=sizeCalzadoM(db);
        int i=0;
        Calzado* listaCalzadoM=showCalzadoM(db);
        do{
            printf("%i. %s %s Precio:%2f\n",(i+1),listaCalzadoM[i]->tipo,listaCalzadoM[i]->nombre,listaCalzadoM[i]->precio);
        }while (i<size);

        int *respuesta1;
        respuesta1 -> malloc(sizeof(int));

        printf("¿Te interesa alguna? \n");
        printf("1. Comprar \n");
        printf("Pulsa 0 para salir.  \n"); 

        do {
            scanf("%i", respuesta1);
            printf("\n"); 
        } while (respuesta1 != 0 || *respuesta1 != 1);

        if (*respuesta1 == 1) {

            int zapatillaMuj;

            printf ("¿Cuál? Por favor, indique su código. \n");
            scanf("%i", &zapatillaMuj);

            int cant;

            printf ("¿Cuántas zapatillas desea? \n");
            scanf("%i", &cant);

            if (&comprador == NULL) {
                printf("Primero debes iniciar sesión. \n");
                comprador = *iniciarCliente (db);
            }

            anadirACarrito (db, arrayProductos, sizeArray, zapatillaMuj, cant);
            sizeArray -= 1;

        }

        free(respuesta1);
        respuesta1 = NULL;
        free(listaCalzadoM);
        listaCalzadoM=NULL;
    }
    else if (*respuesta == 2)
    {
        iniciarCarrito(db, comprador, &sizeArray, arrayProductos);
    }


    free(respuesta);
    respuesta = NULL;
}


// Para inicio de ropa hombre

void iniciarRopaH(sqlite3 *db, Comprador comprador, int** arrayProductos, int sizeArray)
{
    int respuesta;
    printf("Esta es la ropa para hombre que tenemos en este momento: \n");
    printf("\n");
    printf("1. Ver ropa para hombre \n");
    printf("2. Ver carrito \n");
    printf("Pulsa 0 para salir. \n");

    do {
        printf("ELECCION: ");
        fflush(stdout);
        scanf("%i", &respuesta);
    } while (respuesta < 0 || respuesta > 2);

    if (respuesta == 1)
    {
        int size=sizePrendaH(db);
        int i=0;
        Prenda* listaPrendaH=showPrendaH(db);
        do{
            printf("%i. %s %s Precio:%2f\n",(i+1),listaPrendaH[i]->tipo,listaPrendaH[i]->nombre,listaPrendaH[i]->precio);
        }while (i<size);


        int respuesta1;

        printf("¿Te interesa alguna? \n");
        printf("1. Comprar \n");
        printf("Pulsa 0 para salir.  \n"); 

        do {
            scanf("%i", &respuesta1);
            printf("\n"); 
        } while (respuesta1 != 0 || respuesta1 != 1);

        if (respuesta1 == 1) {

            int ropaHombre;

            printf ("¿Cuál? Por favor, indique su código. \n");
            scanf("%i", &ropaHombre);

            int cant;

            printf ("¿Cuántas desea comprar? \n");
            scanf("%i", &cant);


            if (&comprador == NULL) {
                printf("Primero debes iniciar sesión. \n");
                comprador = *iniciarCliente (db);
            }

            anadirACarrito (db, arrayProductos, sizeArray, ropaHombre, cant);
            sizeArray -= 1;
        }

        free(listaPrendaH);
        listaPrendaH=NULL;
    }
    if (respuesta == 2)
    {
        iniciarCarrito(db, comprador, &sizeArray, arrayProductos);
    }

}


// Para inicio de ropa mujer

void iniciarRopaM(sqlite3 *db, Comprador comprador, int** arrayProductos, int sizeArray)
{
    int respuesta;
    printf("Esta es la ropa para mujer que tenemos en este momento: \n");
    printf("\n");
    printf("1. Ver ropa para mujer \n");
    printf("2. Ver carrito \n");
    printf("Pulsa 0 para salir. \n");

    do {
        printf("ELECCION: ");
        fflush(stdout);
        scanf("%i", &respuesta);
    } while (respuesta < 0 || respuesta > 2);
    

    if (respuesta == 1)
    {

        
        int size=sizePrendaM(db);
        int i=0;
        Prenda* listaPrendaM=showPrendaM(db);
        do{
            printf("%i. %s %s Precio:%2f\n",(i+1),listaPrendaM[i]->tipo,listaPrendaM[i]->nombre,listaPrendaM[i]->precio);
        }while (i<size);

        int respuesta1;

        printf("¿Te interesa alguna? \n");
        printf("1. Comprar \n");
        printf("Pulsa 0 para salir.  \n"); 

        do {
            scanf("%i", &respuesta1);
            printf("\n"); 
        } while (respuesta1 != 0 || respuesta1 != 1);

        if (respuesta1 == 1) {

            int ropaMujer;

            printf ("¿Cuál? Por favor, indique su código. \n");
            scanf("%i", &ropaMujer);

            int cant;

            printf ("¿Cuántas desea comprar? \n");
            scanf("%i", &cant);

            if (&comprador == NULL) {
                printf("Primero debes iniciar sesión. \n");
                comprador = *iniciarCliente (db);
            }

            anadirACarrito (db, arrayProductos, sizeArray, ropaMujer, cant);
            sizeArray -= 1;
        }

        free(listaPrendaM);
        listaPrendaM=NULL;

    }
    else if (respuesta == 2)
    {
        iniciarCarrito(db, comprador, &sizeArray, arrayProductos);
    }
}


// Para inicio de suplementos

void iniciarSuplementos(sqlite3 *db, Comprador comprador, int** arrayProductos, int sizeArray)
{
    int respuesta;
    printf("Estos son los suplementos deportivos que tenemos en este momento: \n");
    printf("\n");
    printf("1. Ver suplementos \n");
    printf("2. Ver carrito \n");
    printf("Pulsa 0 para salir. \n");

    do {
        printf("ELECCION: ");
        fflush(stdout);
        scanf("%i", &respuesta);

    } while (respuesta < 0 || respuesta > 2);
    

    if (respuesta == 1)
    {

        int size=sizeSupl(db);
        int i=0;
        Suplemento* listaSupl=showSupl(db);
        do{
            printf("%i. %s %s Precio:%2f\n",(i+1),listaSupl[i]->tipo,listaSupl[i]->nombre,listaSupl[i]->precio);
        }while (i<size);

        int respuesta1;

        printf("¿Te interesa alguna? \n");
        printf("1. Comprar \n");
        printf("Pulsa 0 para salir.  \n"); 

        do {
            scanf("%i", &respuesta1);
            printf("\n"); 
        } while (respuesta1 != 0 || respuesta1 != 1);

        if (respuesta1 == 1) {

            int suplem;

            printf ("¿Cuál? Por favor, indique su código. \n");
            scanf("%i", &suplem);

            int cant;

            printf ("Indique la cantidad \n");
            scanf("%i", &cant);


            if (&comprador == NULL) {
                printf("Primero debes iniciar sesión. \n");
                comprador = *iniciarCliente (db);
            }

            anadirACarrito (db, arrayProductos, sizeArray, suplem, cant);
            sizeArray -= 1;
        }

        free(listaSupl);
        listaSupl=NULL;
    }
    else if (respuesta == 2)
    {
        iniciarCarrito(db, comprador, &sizeArray, arrayProductos);
    }
}


// Para inicio de material deportivo especifico

void iniciarMaterialD(sqlite3 *db, Comprador comprador, int** arrayProductos, int sizeArray)
{
    int respuesta;
    printf("Estos son los materiales deportivos especificos que tenemos en este momento: \n");
    printf("\n");
    printf("1. Ver material deportivo \n");
    printf("2. Ver carrito \n");
    printf("Pulsa 0 para salir. \n");

    do {
        printf("ELECCION: ");
        fflush(stdout);
        scanf("%i", &respuesta);
    } while (respuesta < 0 || respuesta > 2);
    

    if (respuesta == 1)
    {
        int size=sizeMD(db);
        int i=0;
        MaterialDeportivo* listaMD=showMD(db);
        do{
            printf("%i. %s %s Precio:%2f\n",(i+1),listaMD[i]->tipo,listaMD[i]->nombre,listaMD[i]->precio);
        }while (i<size);

        int respuesta1;

        printf("¿Te interesa alguna? \n");
        printf("1. Comprar \n");
        printf("Pulsa 0 para salir.  \n"); 

        do {
            scanf("%i", &respuesta1);
            printf("\n"); 
        } while (respuesta1 != 0 || respuesta1 != 1);

        if (respuesta1 == 1) {

            int matDep;

            printf ("¿Cuál? Por favor, indique su código. \n");
            scanf("%i", &matDep);

            int cant;

            printf ("Indique la cantidad \n");
            scanf("%i", &cant);


            if (&comprador == NULL) {
                printf("Primero debes iniciar sesión. \n");
                comprador = *iniciarCliente (db);
            }

            anadirACarrito (db, arrayProductos, sizeArray, matDep, cant);
            sizeArray -= 1;
        }

        free(listaMD);
        listaMD=NULL;
    }
    else if (respuesta == 2)
    {
        iniciarCarrito(db, comprador, &sizeArray, arrayProductos);
    }
}


void ventaPrincipal(sqlite3 *db, Comprador comprador, int** arrayProductos, int sizeArray)
{
    int respuesta;

    printf("¿Qué Tipo de producto esta buscando? Eliga el numero del tipo de producto que busca o lo que quiera hacer \n");
    printf("\n");
    printf("1. Zapatillas (Hombre)\n");
    printf("2. Zapatillas (Mujer)\n");
    printf("3. Ropa (Hombre)\n");
    printf("4. Ropa (Mujer)\n");
    printf("5. Suplementos deportivos\n");
    printf("6. Material especifico para deportes \n");
    printf("7. Ver carrito \n");
    printf("8. Devolver producto");
    printf("Pulsa 0 para salir. \n");

    do {
        printf("ELECCION: ");
        fflush(stdout);
        scanf("%i", &respuesta);

    } while (respuesta < 1 || respuesta > 8);
    
    while (respuesta != 0) {
        if (respuesta == 1)
        {
            iniciarZapatillasH(db, comprador, arrayProductos, sizeArray);
        } else if (respuesta == 2)
        {
            iniciarZapatillasM(db, comprador, arrayProductos, sizeArray);
        } else if (respuesta == 3)
        {
            iniciarRopaH(db, comprador, arrayProductos, sizeArray);
        } else if (respuesta == 4)
        {
            iniciarRopaM(db, comprador, arrayProductos, sizeArray);
        } else if (respuesta == 5)
        {
            iniciarSuplementos(db, comprador, arrayProductos, sizeArray);
        } else if (respuesta == 6)
        {
            iniciarMaterialD(db, comprador, arrayProductos, sizeArray);
        } else if (respuesta == 7)
        {
            iniciarCarrito(db, comprador, &sizeArray, arrayProductos);
        }  else if (respuesta == 8) 
        {
            if (&comprador == NULL) {
                comprador = *iniciarCliente (db);
            }
            int* idCompra;
            idCompra = malloc(sizeof(int));
            printf("IDENTIFICATIVO DE LA COMPRA: \n");
            scanf("%i", idCompra);
            int* idProducto;
            idProducto = malloc(sizeof(int));
            printf("IDENTIFICATIVO DEL PRODUCTO: \n");
            scanf("%i", idProducto);
            devolverCompra (db, comprador, *idProducto, *idCompra);
        }
    }

    printf("¡Que pase un buen día!");
}

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
// FIN PARTE GRAFICA DE ELECCIONES
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

    printf("BIENVENIDX A DEUSTOSPORTKIT CLIENTE :) \n");

    int comienzo;
    comienzo = inicio();

    if (comienzo == 0) {

        printf("¡Pasa un buen día!");

    } else if (comienzo == 1 || comienzo == 2 || comienzo == 3) {

        Comprador comprador;

        if (comienzo == 1) {
            comprador = *iniciarCliente (db);
            int** arrayProductos;
            int sizeArray = 0;
            ventaPrincipal(db, comprador, arrayProductos, sizeArray);
        } else if (comienzo == 2) {
            comprador = registrar (db);
            int** arrayProductos;
            int sizeArray = 0;
            ventaPrincipal(db, comprador, arrayProductos, sizeArray);
            } else {
//            comprador = NULL;
            ventaPrincipal(db, comprador, NULL, 0);
        }

    }

}