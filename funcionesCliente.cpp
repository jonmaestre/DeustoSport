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
