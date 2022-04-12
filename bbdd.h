#ifndef BBDD_H_
#define BBDD_H_
#include "sqlite3.h"
#include <stdbool.h>


// PRODUCTOS
int maxIdProducto(sqlite3 *db);

void eliminarProducto(sqlite3 *db, int id);
void agregarProducto(sqlite3 *db, int id, char *nom, float precio, int cantidad);
void modificarCantidad(sqlite3 *db, int id, int cant);
void bajarStock(sqlite3 *db, int id);

char obtenerTipoProducto (sqlite3 *db, int id);

Calzado obtenerCalzado (sqlite3 *db, int id);
void agregarCalzado(sqlite3 *db, char* nom, char* tipo, char* color, char* talla, float precio, int sexo, int cantidad);
void subirStockCalzado (sqlite3 *db, int id, int cant);
void bajarStock(sqlite3 *db, int id);

Prenda obtenerPrenda (sqlite3 *db, int id);
void agregarPrenda(sqlite3 *db, char* nom, char* tipo, char* color, char* talla, float precio, int sexo, int cantidad);
void subirStockCPrenda (sqlite3 *db, int id, int cant);
void bajarPrenda(sqlite3 *db, int id);

MaterialDeportivo obtenerMaterial (sqlite3 *db, int id);
void agregarSupl(sqlite3 *db, char* nom, char* tipo, char* color, char* talla, float precio, char* deporte, int cantidad);
void subirStockSupl (sqlite3 *db, int id, int cant);
void bajarSupl(sqlite3 *db, int id);

Suplemento obtenerSuplemento (sqlite3 *db, int id);
void agregarMD(sqlite3 *db, char* nom, char* tipo,  int cantidad, float precio,);
void subirStockMD (sqlite3 *db, int id, int cant);
void bajarMD(sqlite3 *db, int id);

// USUARIOS
bool existeComprador (sqlite3 *db, char* correo);
Comprador obtenerComprador (sqlite3 *db, char* correo);


// CARRITOS / COMPRAS
int ultimoCarrito (sqlite3 *db);
Compra* comprasConId (sqlite3* db, int idCompra);

#endif 