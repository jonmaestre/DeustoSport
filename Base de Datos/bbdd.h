#ifndef BBDD_H_
#define BBDD_H_
#include "sqlite3.h"

void eliminarProducto(sqlite3 *db, int id);
void agregarProducto(sqlite3 *db, int id, char *nom, float precio, int cantidad);
void modificarCantidad(sqlite3 *db, int id, int cant);
void bajarStock(sqlite3 *db, int id);

bool existeComprador (sqlite3 *db, char* correo);
Comprador obtenerComprador (sqlite3 *db, char* correo);

#endif 