#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Administrador.h"

#include "Estructuras.h"
#include "Comprita.h"
#include "Cliente.h"

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
// INICIO PARTE GRAFICA DE ELECCIONES
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------



// Para inicio de la zapatillas mujer

void iniciarZapatillas(sqlite3 *db, Comprador comprador, int** arrayProductos, int sizeArray)
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
        int size=sizeCalzado(db);
        int i=0;
        Calzado* listaCalzadoM=showCalzado(db);
        do{
            printf("%i. %s %s Precio:%2f\n",(i+1),listaCalzado[i]->tipo,listaCalzado[i]->nombre,listaCalzado[i]->precio);
        }while (i<size);

        int *respuesta1;
        *respuesta1 -> malloc(sizeof(int));

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
                //comprador = *iniciarCliente (db);
            }

            //anadirACarrito (db, arrayProductos, sizeArray, zapatillaMuj, cant);
            sizeArray -= 1;

        }

        free(respuesta1);
        respuesta1 = NULL;
        free(listaCalzadoM);
        listaCalzadoM=NULL;
    }
    else if (*respuesta == 2)
    {
        //iniciarCarrito(db, comprador, &sizeArray, arrayProductos);
    }


    free(respuesta);
    respuesta = NULL;
}


// Para inicio de ropa hombre

void iniciarRopa(sqlite3 *db, Comprador comprador, int** arrayProductos, int sizeArray)
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
        int size=sizePrenda(db);
        int i=0;
        Prenda* listaPrendaH=showPrenda(db);
        do{
            printf("%i. %s %s Precio:%2f\n",(i+1),listaPrenda[i]->tipo,listaPrenda[i]->nombre,listaPrenda[i]->precio);
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
                //comprador = *iniciarCliente (db);
            }

            //anadirACarrito (db, arrayProductos, sizeArray, ropaHombre, cant);
            sizeArray -= 1;
        }

        free(listaPrendaH);
        listaPrendaH=NULL;
    }
    if (respuesta == 2)
    {
        //iniciarCarrito(db, comprador, &sizeArray, arrayProductos);
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
                //comprador = *iniciarCliente (db);
            }

            //anadirACarrito (db, arrayProductos, sizeArray, matDep, cant);
            sizeArray -= 1;
        }

        free(listaMD);
        listaMD=NULL;
    }
    else if (respuesta == 2)
    {
        //iniciarCarrito(db, comprador, &sizeArray, arrayProductos);
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
            iniciarZapatillas(db, comprador, arrayProductos, sizeArray);
        } else if (respuesta == 3)
        {
            iniciarRopa(db, comprador, arrayProductos, sizeArray);
        }  else if (respuesta == 6)
        {
            iniciarMaterialD(db, comprador, arrayProductos, sizeArray);
        } else if (respuesta == 7)
        {
            //iniciarCarrito(db, comprador, &sizeArray, arrayProductos);
        }  else if (respuesta == 8) 
        {
            if (&comprador == NULL) {
                //comprador = *iniciarCliente (db);
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