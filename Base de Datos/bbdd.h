#ifndef BBDD_H_
#define BBDD_H_
#include "sqlite3.h"

// PRODUCTOS
void eliminarProducto(sqlite3 *db, int id);
void agregarProducto(sqlite3 *db, int id, char *nom, float precio, int cantidad);
void modificarCantidad(sqlite3 *db, int id, int cant);
void bajarStock(sqlite3 *db, int id);
int ultimoCarrito (sqlite3 *db);
char obtenerTipoProducto (sqlite3 *db, int id);
Calzado obtenerCalzado (sqlite3 *db, int id);
Prenda obtenerPrenda (sqlite3 *db, int id);
Material obtenerMaterial (sqlite3 *db, int id);
Suplemento obtenerSuplemento (sqlite3 *db, int id);

// USUARIOS
bool existeComprador (sqlite3 *db, char* correo);
Comprador obtenerComprador (sqlite3 *db, char* correo);

#endif 