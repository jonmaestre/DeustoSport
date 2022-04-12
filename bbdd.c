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
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


// --------------------------------------------------------------------------------------------------
// PRODUCTOS

int maxIdProducto(sqlite3 *db){
    sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT MAX(idProducto) FROM Producto");
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	int maximo = sqlite3_step(stmt);

	sqlite3_finalize(stmt);
	
	return maximo;
}

void eliminarProducto(sqlite3 *db, int id){
    sqlite3_stmt *stmt;
	char sql[100];
	sprintf(sql, "delete from producto where id = %d",id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}

void agregarProducto(sqlite3 *db, int id, char *nom, float precio, int cantidad){
    sqlite3_stmt *stmt;

	char sql[100];

	sprintf(sql, "insert into producto values(%d, %s, %f, %d)",id,nom, precio, cantidad);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}

void modificarCantidad(sqlite3 *db, int id, int cant){
    sqlite3_stmt *stmt;
	char sql[100];

	sprintf(sql, "update producto set cantidad=%d where id=%d", cant, id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}

void bajarStock(sqlite3 *db, int id){
    sqlite3_stmt *stmt;
	char sql[100];

	sprintf(sql, "update producto set cantidad=cantidad-1 where id =%d", id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}

char obtenerTipoProducto (sqlite3 *db, int id){
    sqlite3_stmt *stmt;

	char sql[100];
	char* tipo;

	sprintf(sql, "SELECT Tipo FROM Producto WHERE idProducto = %i",id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	tipo = sqlite3_step(stmt);

	sqlite3_finalize(stmt);

	return tipo[0];				// C -> calzado		M -> material	P -> prenda 	S -> suplemento
}

// *************************** CALZADO ***************************

Calzado obtenerCalzado (sqlite3 *db, int id){
    sqlite3_stmt *stmt;
	char sql[100];

	int iden, sexo, stock;
	char* nombre, tipo, color;
	nombre = malloc(100*sizeof(char));
	tipo = malloc(15*sizeof(char));
	color = malloc(15*sizeof(char));
	float talla, precio;

	sprintf(sql, "SELECT * FROM Calzado WHERE idProducto = %i",id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	
	iden = (int)sqlite3_column_text(stmt, 0);
	strcpy(nombre, (char*)sqlite3_column_text(stmt, 1));
	strcpy(tipo, (char*)sqlite3_column_text(stmt, 2));
	strcpy(color, (char*)sqlite3_column_text(stmt, 3));
	talla = (float)sqlite3_column_text(stmt, 4);
	precio = (float)sqlite3_column_text(stmt, 5);
	sexo = (int)sqlite3_column_text(stmt, 6);
	stock = (int)sqlite3_column_text(stmt, 7);

	Calzado zapatilla = {iden, nombre, tipo, color, talla, precio, sexo, stock};

	sqlite3_finalize(stmt);

	return zapatilla;
}

void agregarCalzado(sqlite3 *db, char* nom, char* tipo, char* color, char* talla, float precio, int sexo, int cantidad){
    sqlite3_stmt *stmt;

	char sql[100];
	int maxId = maxIdProducto(db);

	sprintf(sql, "INSERT INTO Calzado VALUES (%i, %s, %s, %s, %s, %f, %i, %i)", maxId+1, nom, tipo, color, talla, precio, sexo, cantidad);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);

	sqlite3_finalize(stmt);
}

void subirStockCalzado (sqlite3 *db, int id, int cant){
    sqlite3_stmt *stmt;
	char sql[100];

	sprintf(sql, "UPDATE Calzado SET Stock_Calzado = Stock_Calzado + %i WHERE  ID_Calzado = %i", cant, id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}

void bajarStockCalzado(sqlite3 *db, int id, int cant){
    sqlite3_stmt *stmt;
	char sql[100];

	sprintf(sql, "UPDATE Calzado SET Stock_Calzado = Stock_Calzado - %i WHERE  ID_Calzado = %i", cant, id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}

// *************************** PRENDA ***************************

Prenda obtenerPrenda (sqlite3 *db, int id){
    sqlite3_stmt *stmt;
	char sql[100];

	int iden, sexo, stock;
	char* nombre, tipo, color, talla;
	nombre = malloc(100*sizeof(char));
	tipo = malloc(15*sizeof(char));
	color = malloc(15*sizeof(char));
	talla = malloc(3*sizeof(char));
	float precio;

	sprintf(sql, "SELECT * FROM Prenda WHERE idProducto = %i",id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	
	iden = (int)sqlite3_column_text(stmt, 0);
	strcpy(nombre, (char*)sqlite3_column_text(stmt, 1));
	strcpy(tipo, (char*)sqlite3_column_text(stmt, 2));
	strcpy(color, (char*)sqlite3_column_text(stmt, 3));
	strcpy(talla, (char*)sqlite3_column_text(stmt, 4));
	precio = (float)sqlite3_column_text(stmt, 5);
	sexo = (int)sqlite3_column_text(stmt, 6);
	stock = (int)sqlite3_column_text(stmt, 7);

	Prenda prenda = {iden, nombre, tipo, color, talla, precio, sexo, stock};

	sqlite3_finalize(stmt);

	return prenda;
}

// *************************** MATERIAL ***************************

MaterialDeportivo obtenerMaterial (sqlite3 *db, int id){
    sqlite3_stmt *stmt;
	char sql[100];

	int iden, stock;
	char* nombre, tipo, color, talla, deporte;
	nombre = malloc(100*sizeof(char));
	tipo = malloc(15*sizeof(char));
	color = malloc(15*sizeof(char));
	talla = malloc(3*sizeof(char));
	deporte = malloc(20*sizeof(char));
	float precio;

	sprintf(sql, "SELECT * FROM MaterialDeportivo WHERE idProducto = %i",id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	
	iden = (int)sqlite3_column_text(stmt, 0);
	strcpy(nombre, (char*)sqlite3_column_text(stmt, 1));
	strcpy(tipo, (char*)sqlite3_column_text(stmt, 2));
	strcpy(color, (char*)sqlite3_column_text(stmt, 3));
	strcpy(talla, (char*)sqlite3_column_text(stmt, 4));
	precio = (float)sqlite3_column_text(stmt, 5);
	strcpy(deporte, (char*)sqlite3_column_text(stmt, 6));
	stock = (int)sqlite3_column_text(stmt, 7);

	MaterialDeportivo material = {iden, nombre, tipo, color, talla, precio, deporte, stock};

	sqlite3_finalize(stmt);

	return material;
}

// *************************** SUPLEMENTO ***************************

Suplemento obtenerSuplemento (sqlite3 *db, int id){
    sqlite3_stmt *stmt;
	char sql[100];

	int iden, stock;
	char* nombre, tipo;
	nombre = malloc(100*sizeof(char));
	tipo = malloc(15*sizeof(char));

	sprintf(sql, "SELECT * FROM Suplemento WHERE idProducto = %i",id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	
	iden = (int)sqlite3_column_text(stmt, 0);
	strcpy(nombre, (char*)sqlite3_column_text(stmt, 1));
	strcpy(tipo, (char*)sqlite3_column_text(stmt, 2));
	stock = (int)sqlite3_column_text(stmt, 3);

	Suplemento suplemento = {iden, nombre, tipo, stock};

	sqlite3_finalize(stmt);

	return suplemento;
}


// ------------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------------
// USUARIOS

bool existeComprador (sqlite3 *db, char* correo) {
	sqlite3_stmt *stmt;

	int resultado;
	bool respuesta;
	char sql[100];

	sprintf(sql, "SELECT * FROM Comprador WHERE Correo = %s", correo);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	resultado = sqlite3_step(stmt);

	if (resultado == NULL) {
		respuesta = false;
	} else {
		respuesta = true;
	}

	sqlite3_finalize(stmt);
	return respuesta;
}


Comprador obtenerComprador (sqlite3 *db, char* correo) {
	sqlite3_stmt *stmt;

	Comprador persona;
	char sql[100];
	char *nombre, *direccion, *contrasena;
	nombre = malloc(15*sizeof(char));
	direccion = malloc(100*sizeof(char));
	contrasena = malloc(25*sizeof(char));
	int iden, telf;

	sprintf(sql, "SELECT * FROM Comprador WHERE Correo = %s", correo);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	strcpy(nombre, (char*)sqlite3_column_text(stmt, 0));
	iden = sqlite3_column_text(stmt, 1);
	telf = sqlite3_column_text(stmt, 2);
	strcpy(correo, (char*)sqlite3_column_text(stmt, 3));
	strcpy(direccion, (char*)sqlite3_column_text(stmt, 4));
	strcpy(contrasena, (char*)sqlite3_column_text(stmt, 5));

	persona = {nombre, iden, telf, correo, direccion, contrasena};

	sqlite3_finalize(stmt);
	return persona;
}

void registrarComprador(sqlite3 *db, char nom, int id, int tlf, char correo, char dir, char cont){
    sqlite3_stmt *stmt;
	char sql[100];

	sprintf(sql, "insert into comprador values(%c,%d,%d,%c,%c,%c)", nom, id, tlf, correo, dir, cont);
	
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}





// ------------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------------
// COMPRAS Y CARRITOS

int ultimoCarrito (sqlite3 *db) {
	sqlite3_stmt *stmt;

	char sql[100];

	sprintf(sql, "SELECT MAX(identificativoCompra) FROM Carrito");
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	int maximo = sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	return maximo;
}

Carrito obtenerCarrito (sqlite3 *db, int idCompra){

    sqlite3_stmt *stmt;
	char sql[100];

	int idComprador;
	float precioTotal;
	Fecha fechaCompra;

	sprintf(sql, "SELECT * FROM Carrito WHERE ID = %i", idCompra);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	
	// REVISAR FECHA
	precioTotal = (float)sqlite3_column_text(stmt, 1);
	idComprador = (int)sqlite3_column_text(stmt, 2);
	fechaCompra = (Fecha)sqlite3_column_text(stmt, 3);

	Carrito carrito = {idCompra, idComprador, precioTotal, fechaCompra};

	sqlite3_finalize(stmt);

	return carrito;
}

Compra* comprasConId (sqlite3* db, int idCompra) {
	sqlite3_stmt *stmt;

	char sql[100];

	sprintf(sql, "SELECT COUNT(*) FROM Compra WHERE ID_Compra = %i", idCompra);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	int size = sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	Compra* compras;
	compras = (Compra*) malloc(sizeof(Compra) * size);

	sprintf(sql, "SELECT * FROM Compra WHERE ID_Compra = %i", idCompra);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	compras = sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	// para saber cuándo llega al final
	compras[size] = NULL;

	return compras;
}


void verTicket (sqlite3* db, int idCompra) {

	Compra* compras;
	compras = comprasConId(db, idCompra);

	Carrito carrito = obtenerCarrito(db, idCompra);

	printf("TICKET: %i \n", idCompra);
	printf("--------------------\n");

	int i = 0;
	while (compras[i] != NULL) {
		int num = i + 1;
		char type = obtenerTipoProducto (db, compras[i].idProducto);
        // C -> calzado		M -> material	P -> prenda 	S -> suplemento
        if (type == 'C') {
            Calzado calz = obtenerCalzado (db, int compras[i].idProducto);
            printf("%i: %s. X%i \n", num, calz.nombre, compras[i].cantidad);
        } else if (type == 'M') {
            MaterialDeportivo matD =  obtenerMaterial (db, int compras[i].idProducto);
            printf("%i: %s. X%i \n", num, matD.nombre, compras[i].cantidad);
        } else if (type == 'P') {
            Prenda pren = obtenerPrenda (db, int compras[i].idProducto);
            printf("%i: %s. X%i \n", num, pren.nombre, compras[i].cantidad);
        } else if (type == 'S') {
            Suplemento supl = obtenerSuplemento(db, int compras[i].idProducto);
            printf("%i: %s. X%i \n", num, supl.nombre, compras[i].cantidad);
        }
	}

	printf("TOTAL: %f \n", carrito.precioTotal);
}

