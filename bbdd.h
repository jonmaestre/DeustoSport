#include "sqlite3.h"
#include "Estructuras.h"
#include "Administrador.h"

#ifndef BBDD_H_
#define BBDD_H_

// PRODUCTOS;
    int maxIdProducto(sqlite3 *db);

    void eliminarProducto(sqlite3 *db, int id);
    void agregarProducto(sqlite3 *db, char* tipo);

    char obtenerTipoProducto (sqlite3 *db, int id);
    int obtenerIdProducto (sqlite3 *db, char* nombre);
    bool existeProducto1 (sqlite3 *db, int id);
    bool existeProducto2 (sqlite3 *db, char* nombre);

    Calzado obtenerCalzado (sqlite3 *db, int id);
    void agregarCalzado(sqlite3 *db, char* nom, char* tipo, char* color, int talla, float precio, int sexo, int cantidad);
    void subirStockCalzado (sqlite3 *db, int id, int cant);
    void bajarStockCalzado(sqlite3 *db, int id, int cant);
    void eliminarCalzado(sqlite3 *db, int id);
    int sizeCalzado(sqlite3 *db);
    Calzado* showCalzado(sqlite3 *db);

    Prenda obtenerPrenda (sqlite3 *db, int id);
    void agregarPrenda(sqlite3 *db, char* nom, char* tipo, char* color, int talla, float precio, int sexo, int cantidad);
    void subirStockCPrenda (sqlite3 *db, int id, int cant);
    void bajarStockPrenda(sqlite3 *db, int id, int cant);
    void eliminarPrenda(sqlite3 *db, int id);
    int sizePrenda(sqlite3 *db);
    Prenda* showPrenda(sqlite3 *db);


    MaterialDeportivo obtenerMaterial (sqlite3 *db, int id);
    void agregarMD(sqlite3 *db, char* nom, char* tipo, char* color, int talla, float precio, char* deporte, int cantidad);
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
    Administrador obtenerAdmin(sqlite3 *db, int id);
    bool existeAdmin(sqlite3 *db, int id);
    int idMaxAdmin(sqlite3 *db);


    // CARRITOS / COMPRAS
    int ultimoCarrito (sqlite3 *db);
    Carrito obtenerCarrito (sqlite3 *db, int idCompra);
    int sizeComprasConId (sqlite3* db, int idCompra);
    Compra* comprasConId (sqlite3* db, int idCompra);
    void verTicket (sqlite3* db, int idCompra);
    void agregarCarrito(sqlite3 *db, Carrito carrito);
    void agregarCompra(sqlite3 *db, Compra compra);
    bool existeCompra1 (sqlite3 *db, int idCompra, int idComprador, int idProducto);
    bool existeCompra2 (sqlite3 *db, int idCompra);
    void eliminarCompra (sqlite3 *db, int idCompra, int idComprador, int idProducto);
    Compra obtenerCompra (sqlite3 *db, int idCompra, int idComprador, int idProducto);


    // DEVOLUCIONES
    void agregarDevolucion (sqlite3 *db, Compra compra, char* explicacion);


#endif 