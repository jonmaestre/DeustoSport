#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Estructuras/Zapatillas.h"

#include "sqlite3.h"

#define PROGRAMADORES 5



int main (void) {

    // falta una bienvenida :)


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
void registrar () {

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

    while (&contrasena1 != &contrasena2) {
        printf("¡Vaya! Parece que ha habido un error. \n");
        printf("Vuelve a introducir la contraseña. \n");
        printf("CONTRASEÑA: \n");
        scanf("%c", contrasena1);
        printf("REPITA CONTRASEÑA: \n");
        scanf("%c", contrasena2);
    }

    

    // se necesita método de bd para coger el último cliente introducido y así conseguir su id

    // mirar si el correo que existe

    // crear cliente con la estructura

    // meter nuevo cliente a la base de datos

    // devolver cliente

}


// tiene que returnear un cliente
void iniciarCliente () {

    // revisar los char*
    char* correo;
    char* contrasena;

    printf("INCIAR SESIÓN \n");
    printf("---------------------------------\n");

    printf("CORREO ELECTRÓNICO: \n");
    scanf("%c", correo);
	printf("CONTRASEÑA: \n");
    scanf("%c", contrasena);

    // mirar si hay algún cliente con el correo  -> true or false
    bool existe;                // ********************************* CAMBIAR ************************
    if (existe == false) {
        int deNuevo;            // ********************************* CAMBIAR ************************
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
            } else {
                // ****************** revisar otra vez ****************
            }
        }
    } else {

        // ****************************************** REVISAR *****************************************

        // método bd para coger el cliente con correo
        char* correito;
        char* contra;
        while (contrasena != contra && correo == correito) {
            printf("¡Vaya! Parece que ha habido un error. \n");
            printf("Vuelve a meter los datos. \n");
            printf("CORREO ELECTRÓNICO: \n");
            scanf("%c", correo);
	        printf("CONTRASEÑA: \n");
            scanf("%c", contrasena);
        }

    }

    // devolver cliente

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
    scanf("%c", correo);
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

