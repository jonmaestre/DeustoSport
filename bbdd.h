#ifndef BBDD_H_
#define BBDD_H_
#include "sqlite3.h"
#include <stdbool.h>


// PRODUCTOS
int maxIdProducto(sqlite3 *db);

void eliminarProducto(sqlite3 *db, int id);
void agregarProducto(sqlite3 *db, char* tipo);

char obtenerTipoProducto (sqlite3 *db, int id);
bool existeProducto (sqlite3 *db, int id);

Calzado obtenerCalzado (sqlite3 *db, int id);
void agregarCalzado(sqlite3 *db, char* nom, char* tipo, char* color, float talla, float precio, int sexo, int cantidad);
void subirStockCalzado (sqlite3 *db, int id, int cant);
void bajarStock(sqlite3 *db, int id, int cant);
void eliminarCalzado(sqlite3 *db, int id);
int sizeCalzadoH(sqlite3 *db);
int sizeCalzadoM(sqlite3 *db);
Calzado* showCalzadoH(sqlite3 *db);
Calzado* showCalzadoM(sqlite3 *db);

Prenda obtenerPrenda (sqlite3 *db, int id);
void agregarPrenda(sqlite3 *db, char* nom, char* tipo, char* color, char* talla, float precio, int sexo, int cantidad);
void subirStockCPrenda (sqlite3 *db, int id, int cant);
void bajarStockPrenda(sqlite3 *db, int id, int cant);
void eliminarPrenda(sqlite3 *db, int id);
int sizePrendaH(sqlite3 *db);
int sizePrendaM(sqlite3 *db);
Prenda* showPrendaH(sqlite3 *db);
Prenda* showPrendaM(sqlite3 *db);


MaterialDeportivo obtenerMaterial (sqlite3 *db, int id);
void agregarMD(sqlite3 *db, char* nom, char* tipo, char* color, char* talla, float precio, char* deporte, int cantidad);
void subirStockMD (sqlite3 *db, int id, int cant);
void bajarStockMD(sqlite3 *db, int id, int cant);
void eliminarMD(sqlite3 *db, int id);
int sizeMD(sqlite3 *db);
MaterialDeportivo* showMD(sqlite3 *db);

Suplemento obtenerSuplemento (sqlite3 *db, int id);
void agregarSupl(sqlite3 *db, char* nom, char* tipo, int cantidad, float precio);
void subirStockSupl (sqlite3 *db, int id, int cant);
void bajarStockSupl(sqlite3 *db, int id, int cant);
void eliminarSupl(sqlite3 *db, int id);
int sizeSupl(sqlite3 *db);
Suplemento* showSupl(sqlite3 *db);


// USUARIOS
bool existeComprador (sqlite3 *db, char* correo);
Comprador obtenerComprador (sqlite3 *db, char* correo);
void registrarComprador(sqlite3 *db, char* nom, int tlf, char* correo, char* dir, char* cont);
Admin obtenerAdmin(sqlite3 *db, int id);
bool existeAdmin(sqlite3 *db, int id);


// CARRITOS / COMPRAS
int ultimoCarrito (sqlite3 *db);
Compra* comprasConId (sqlite3* db, int idCompra);

#endif 