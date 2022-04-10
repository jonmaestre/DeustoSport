#include "bbdd.h"
#include "/Estructuras/Administrador.h"
#include "/Estructuras/Calzado.h"
#include "/Estructuras/Carrito.h"
#include "/Estructuras/Compra.h"
#include "/Estructuras/Comprador.h"
#include "/Estructuras/MaterialDeportivo.h"
#include "/Estructuras/Prenda.h"
#include "/Estructuras/Suplemento.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// --------------------------------------------------------------------------------------------------
// PRODUCTOS

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

Calzado obtenerCalzado (sqlite3 *db, int id){
    sqlite3_stmt *stmt;
	char sql[100];

	int iden, sexo, stock;
	char* nombre, tipo, color;
	float talla, precio;

	sprintf(sql, "SELECT * FROM Calzado WHERE idProducto = %i",id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	
	strcpy(iden, (int)sqlite3_column_text(stmt, 0));
	strcpy(nombre, (char*)sqlite3_column_text(stmt, 1));
	strcpy(tipo, (char*)sqlite3_column_text(stmt, 2));
	strcpy(color, (char*)sqlite3_column_text(stmt, 3));
	strcpy(talla, (float)sqlite3_column_text(stmt, 4));
	strcpy(precio, (float)sqlite3_column_text(stmt, 5));
	strcpy(sexo, (int)sqlite3_column_text(stmt, 4));
	strcpy(stock, (int)sqlite3_column_text(stmt, 5));

	Calzado zapatilla = {iden, nombre, tipo, color, talla, precio, sexo, stock};

	sqlite3_finalize(stmt);

	return zapatilla;
}

Prenda obtenerPrenda (sqlite3 *db, int id){
    sqlite3_stmt *stmt;
	char sql[100];

	int iden, sexo, stock;
	char* nombre, tipo, color, talla;
	float precio;

	sprintf(sql, "SELECT * FROM Prenda WHERE idProducto = %i",id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	
	strcpy(iden, (int)sqlite3_column_text(stmt, 0));
	strcpy(nombre, (char*)sqlite3_column_text(stmt, 1));
	strcpy(tipo, (char*)sqlite3_column_text(stmt, 2));
	strcpy(color, (char*)sqlite3_column_text(stmt, 3));
	strcpy(talla, (char*)sqlite3_column_text(stmt, 4));
	strcpy(precio, (float)sqlite3_column_text(stmt, 5));
	strcpy(sexo, (int)sqlite3_column_text(stmt, 4));
	strcpy(stock, (int)sqlite3_column_text(stmt, 5));

	Prenda prenda = {iden, nombre, tipo, color, talla, precio, sexo, stock};

	sqlite3_finalize(stmt);

	return prenda;
}


Material obtenerMaterial (sqlite3 *db, int id){
    sqlite3_stmt *stmt;
	char sql[100];

	int iden, stock;
	char* nombre, tipo, color, talla, deporte;
	float precio;

	sprintf(sql, "SELECT * FROM MaterialDeportivo WHERE idProducto = %i",id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	
	strcpy(iden, (int)sqlite3_column_text(stmt, 0));
	strcpy(nombre, (char*)sqlite3_column_text(stmt, 1));
	strcpy(tipo, (char*)sqlite3_column_text(stmt, 2));
	strcpy(color, (char*)sqlite3_column_text(stmt, 3));
	strcpy(talla, (char*)sqlite3_column_text(stmt, 4));
	strcpy(precio, (float)sqlite3_column_text(stmt, 5));
	strcpy(deporte, (char*)sqlite3_column_text(stmt, 4));
	strcpy(stock, (int)sqlite3_column_text(stmt, 5));

	MaterialDeportivo material = {iden, nombre, tipo, color, talla, precio, deporte, stock};

	sqlite3_finalize(stmt);

	return material;
}


Suplemento obtenerSuplemento (sqlite3 *db, int id){
    sqlite3_stmt *stmt;
	char sql[100];

	int iden, stock;
	char* nombre, tipo;

	sprintf(sql, "SELECT * FROM Suplemento WHERE idProducto = %i",id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	
	strcpy(iden, (int)sqlite3_column_text(stmt, 0));
	strcpy(nombre, (char*)sqlite3_column_text(stmt, 1));
	strcpy(tipo, (char*)sqlite3_column_text(stmt, 2));
	strcpy(stock, (int)sqlite3_column_text(stmt, 3));

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
	char sql[100], *nombre, *direccion, *contrasena;
	int iden, telf;

	sprintf(sql, "SELECT * FROM Comprador WHERE Correo = %c", correo);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	strcpy(nombre, (char*)sqlite3_column_text(stmt, 0));
	strcpy(iden, (int)sqlite3_column_text(stmt, 1));
	strcpy(telf, (int)sqlite3_column_text(stmt, 2));
	strcpy(correo, (char*)sqlite3_column_text(stmt, 3));
	strcpy(direccion, (char*)sqlite3_column_text(stmt, 4));
	strcpy(contrasena, (char*)sqlite3_column_text(stmt, 5));

	persona = {nombre, iden, telf, correo, direccion, contrasena};

	sqlite3_finalize(stmt);
	return persona;
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

