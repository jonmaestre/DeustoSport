#ifndef ADMINISTRADOR_H_
#define ADMINISTRADOR_H_


typedef struct {
	char* nombre;
    int identificativo;
    char* contrasena;
    char* funcion;
} Administrador;


Administrador iniciarAdmin (sqlite3 *db);

void crearProductoAdmin (sqlite3 *db, Administrador administrador);

void recargarProoductoAdmin (sqlite3 *db, Administrador administrador);

void eliminarProductoAdmin (sqlite3 *db, Administrador administrador);

void ventanaAdmin (sqlite3 *db, Administrador administrador);


#endif
