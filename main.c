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


int main (void) {

    // falta una bienvenida :)

    sqlite3 *db;
	int result = sqlite3_open("BaseDatos.db", &db);




}


// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------
// COMIENZO PARTE INICIAR / REGISTRARSE
// --------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------

int inicio () {
    int respuesta;

    printf("¿Qué desea hacer? \n");
    printf("\n");
	printf("1. Iniciar sesión\n");
	printf("2. Registrarme como nuevo cliente\n");
	printf("3. Iniciar como invitado\n");       // ------------>    cliente -> NULL
    printf("4. Iniciar sesión como administrador\n");
	printf("Pulsar 0 para salir\n");
	printf("\n");
	printf("Opción: ");
	fflush(stdout);
    scanf("%i", respuesta);
	return respuesta;
}


// tiene que returnear un cliente
void registrar (sqlite3 *db) {

    // revisar los char*
    char* nombre;
    int codigo;
    int telefono;
    char* correo;
    char* direccion;
    char* contrasena1;
    char* contrasena2;

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

    bool existe = existeComprador(*db, correo);
    while (existe) {
        printf("El correo introducido ya existe. Por favor, introduzca otro. \n");
        printf("CORREO ELECTRÓNICO: \n");
        scanf("%c", correo);
        bool existe = existeComprador(*db, correo);
    }

    while (&contrasena1 != &contrasena2) {
        printf("¡Vaya! Parece que ha habido un error. \n");
        printf("Vuelve a introducir la contraseña. \n");
        printf("CONTRASEÑA: \n");
        scanf("%c", contrasena1);
        printf("REPITA CONTRASEÑA: \n");
        scanf("%c", contrasena2);
    }

    

    // meter nuevo cliente a la base de datos

    // devolver cliente

}


// tiene que returnear un cliente
Comprador iniciarCliente () {

    // revisar los char*
    char* correo;
    char* contrasena;

    printf("INCIAR SESIÓN \n");
    printf("---------------------------------\n");

    printf("CORREO ELECTRÓNICO: \n");
    scanf("%c", correo);
	printf("CONTRASEÑA: \n");
    scanf("%c", contrasena);

    bool existe = existeComprador(*db, correo);
    if (existe == false) {
        int deNuevo;
        while (existe == false) {
            printf("¡Vaya! Parece que ha habido un error. \n");
            printf("Creemos que no está registrado en DeustoSportKit. \n");
            printf("¿Quiere registrarse o reintentar iniciar sesión?");
            printf("1. Registrarme\n");
	        printf("2. Reintentar\n");
	        printf("\n");
	        printf("Opción: ");
	        fflush(stdout);
            scanf("%i", deNuevo);
            if (deNuevo == 1) {
                registrar ();
            } if else (deNuevo == 2) {
                printf("CORREO ELECTRÓNICO: \n");
                scanf("%c", correo);
	            printf("CONTRASEÑA: \n");
                scanf("%c", contrasena);

                bool existe = existeComprador(*db, correo);
            } else {
                // next
            }
        }
    } else {

        Comprador persona = obtenerComprador (sqlite3 *db, char* correo);
        char* correito = persona.correo;
        char* contra = persona.contrasena;
        while (contrasena != contra && correo == correito) {
            printf("¡Vaya! Parece que ha habido un error. \n");
            printf("Vuelve a meter los datos. \n");
            printf("CORREO ELECTRÓNICO: \n");
            scanf("%c", correo);
	        printf("CONTRASEÑA: \n");
            scanf("%c", contrasena);
            Comprador persona = obtenerComprador (sqlite3 *db, char* correo);
            char* correito = persona.correo;
            char* contra = persona.contrasena;
        }

    }

    return persona;

}


// tiene que returnear un admin
void iniciarAdmin () {

    // revisar los char*
    char* identificativo;
    char* contrasena;
    int respuestaPregunta;
    // si realmente son administradores, sabrán la respuesta a una pregunta. siempre la misma.

    printf("INCIAR SESIÓN \n");
    printf("---------------------------------\n");

    printf("IDENTIFICATIVO PROPIO: \n");
    scanf("%c", identificativo);
	printf("CONTRASEÑA: \n");
    scanf("%c", contrasena);
    printf("¿CUÁNTOS PROGRAMADORES HAY EN 'DeustoSportKit'?: \n");
    scanf("%i", respuestaPregunta);

    if (respuestaPregunta != PROGRAMADORES) {
        printf("¡ERROR! Tú no eres un administrador.");
        return NULL;            // si returnea null, se cierra el programa
    } else {

        // método bd para coger el administrador con el identificativo introducido

        // mirar si hay algún admin con el iden  -> true or false
        bool existe;                // ********************************* CAMBIAR ************************
        if (existe == false) {
            int deNuevo;            // ********************************* CAMBIAR ************************
            while (existe == false) {
                printf("¡Vaya! Parece que ha habido un error. \n");
                printf("¿Quiere intentarlo de nuevo?");
                printf("1. Reintentar\n");
	            printf("2. Salir\n");
    	        printf("\n");
	            printf("Opción: ");
                scanf("%i", deNuevo);
                if (deNuevo == 1) {
                    // ************************++  REVISAR **************************
                } else {
                    return NULL;
                }
            }
        }

    }

    // devolver admin

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

int ventaPrincipal()
{
    int respuesta;

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
    if (respuesta = 1)
    {
        iniciarZapatillasH();
    }
    if (respuesta = 2)
    {
        iniciarZapatillasM();
    }
    if (respuesta = 3);
    {
        iniciarRopaH();
    }
    if (respuesta = 4)
    {
        iniciarRopaM();
    }
    if (respuesta = 5)
    {
        iniciarSuplementos();
    }
    if (respuesta = 6)
    {
        iniciarMaterialD();
    }
    if (respuesta = 7)
    {
        iniciarCarrito();
    }
    return respuesta;

}

// Para inicio de la Zapatillas hombre
int iniciarZapatillasH()
{
    int respuesta;
    printf("Estas son las zapatillas para hombre que tenemos en este momento: \n");
    printf("\n");

    printf("0. Ver carrito \n");
    if (respuesta = 0)
    {
        iniciarCarrito();
    }

    printf("1. Volver a la pagina de atras \n");
    if (respuesta = 1)
    {
        ventaPrincipal();
    }
     

    ////<<<<<<<<------------------------------------Intxausti simplemente printea desde la base de datos productos las Zapatillas para hombre que metas

    
    return respuesta;


}


// Para inicio de la zapatillas mujer

int iniciarZapatillasM()
{
    int respuesta;
    printf("Estas son las zapatillas para mujer que tenemos en este momento: \n");
    printf("\n");

    printf("0. Ver carrito \n");
    if (respuesta = 0)
    {
        iniciarCarrito();
    }

    printf("1. Volver a la pagina de atras \n");
    if (respuesta = 1)
    {
        ventaPrincipal();
    }
     

    ////<<<<<<<<------------------------------------Intxausti simplemente printea desde la base de datos productos las Zapatillas para mujer que metas

    
    return respuesta;


}


// Para inicio de ropa hombre

int iniciarRopaH()
{
    int respuesta;
    printf("Esta es la ropa para hombre que tenemos en este momento: \n");
    printf("\n");

    printf("0. Ver carrito \n");
    if (respuesta = 0)
    {
        iniciarCarrito();
    }

    printf("1. Volver a la pagina de atras \n");
    if (respuesta = 1)
    {
        ventaPrincipal();
    }
     

    ////<<<<<<<<------------------------------------Intxausti simplemente printea desde la base de datos productos ropa de hombre que metas

    
    return respuesta;


}


// Para inicio de ropa mujer

int iniciarRopaM()
{
    int respuesta;
    printf("Esta es la ropa para mujer que tenemos en este momento: \n");
    printf("\n");

    printf("0. Ver carrito \n");
    if (respuesta = 0)
    {
        iniciarCarrito();
    }

    printf("1. Volver a la pagina de atras \n");
    if (respuesta = 1)
    {
        ventaPrincipal();
    }
     

    ////<<<<<<<<------------------------------------Intxausti simplemente printea desde la base de datos productos ropa de mujer que metas

    
    return respuesta;


}

// Para inicio de ropa mujer

int iniciarSuplementos()
{
    int respuesta;
    printf("Estos son los suplementos deportivos que tenemos en este momento: \n");
    printf("\n");

    printf("0. Ver carrito \n");
    if (respuesta = 0)
    {
        iniciarCarrito();
    }
    
    printf("1. Volver a la pagina de atras \n");
    if (respuesta = 1)
    {
        ventaPrincipal();
    }

    ////<<<<<<<<------------------------------------Intxausti simplemente printea desde la base de datos los suplementos deportivos deportivos

    
    return respuesta;


}

// Para inicio de material deportivo especifico

int iniciarMaterialD()
{
    int respuesta;
    printf("Estos son los materiales deportivos especificos que tenemos en este momento: \n");
    printf("\n");

    printf("0. Ver carrito \n");
    if (respuesta = 0)
    {
        iniciarCarrito();
    }

    printf("1. Volver a la pagina de atras \n");
    if (respuesta = 1)
    {
        ventaPrincipal();
    }

    ////<<<<<<<<------------------------------------Intxausti simplemente printea desde la base de datos los materiales especificos deportivos deportivos

    
    return respuesta;


}


int iniciarCarrito()
{
    int respuesta;
    printf("Estos son los productos que tienes en el carrito en este instante: \n");
    printf("\n");

    
     

    ////<<<<<<<<------------------------------------ Se necesita funcion que almacene las compras para mostrarlas
    printf("0. Volver atras \n");

    if (respuesta = 0)
    {
        ventaPrincipal();
    }

    printf("1. Comprar \n");

    if (respuesta = 1)
    {
        //<<<<<<<<<<------------------------------Falta funcion de comprar en la que calcule el precio
    }

    printf("2. Borrar Producto \n");

    if (respuesta = 2)
    {
        //<<<<<<<<<<------------------------------Falta funcion de seleccionar producto y borrarlo
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