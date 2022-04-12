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
#include <stdlib.h>


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
	tipo = malloc(10*sizeof(char));

	sprintf(sql, "SELECT Tipo FROM Producto WHERE idProducto = %i",id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	//tipo = sqlite3_step(stmt);
	strcpy(tipo, (char*)sqlite3_column_text(stmt, 0));

	sqlite3_finalize(stmt);

	return tipo[0];				// C -> calzado		M -> material	P -> prenda 	S -> suplemento
}

// *************************** CALZADO ***************************

Calzado obtenerCalzado (sqlite3 *db, int id){
    sqlite3_stmt *stmt;
	char sql[100];

	int iden, sexo, stock;
	char *nombre, *tipo, *color;
	float talla, precio;

	nombre = malloc(100*sizeof(char));
	tipo = malloc(15*sizeof(char));
	color = malloc(15*sizeof(char));

	sprintf(sql, "SELECT * FROM Calzado WHERE idProducto = %i",id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	
	iden = (int)sqlite3_column_int(stmt, 0);
	strcpy(nombre, (char*)sqlite3_column_text(stmt, 1));
	strcpy(tipo, (char*)sqlite3_column_text(stmt, 2));
	strcpy(color, (char*)sqlite3_column_text(stmt, 3));
	talla = (float)sqlite3_column_double(stmt, 4);
	precio = (float)sqlite3_column_double(stmt, 5);
	sexo = (int)sqlite3_column_int(stmt, 6);
	stock = (int)sqlite3_column_int(stmt, 7);

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

int showCalzadoH(sqlite3 *db) {
	sqlite3_stmt *stmt;

	char sql[] = "SELECT * FROM Calzado WHERE Sexo_Calzado = 0";

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}



	char nombre[100];
	char tipo[100];
	char color[100];
	char talla[100];
	float precio;

	printf("\n");
	printf("\n");
	printf("Ensenyando calzado para hombre:\n");
	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			strcpy(nombre, (char *) sqlite3_column_text(stmt, 1));
			strcpy(tipo, (char *) sqlite3_column_text(stmt, 2));
			strcpy(color, (char *) sqlite3_column_text(stmt, 3));
			strcpy(talla, (char *) sqlite3_column_text(stmt, 4));
			precio = sqlite3_column_double(stmt,5);
			printf("Nombre: %s  Tipo:%s  Color:%s  Talla:%s  Precio:%f", nombre,tipo,color,talla,precio);
		}
	} while (result == SQLITE_ROW);
 
	printf("\n");
	printf("\n");

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Prepared statement finalized (SELECT)\n");

	return SQLITE_OK;
}

int showCalzadoM(sqlite3 *db) {
	sqlite3_stmt *stmt;

	char sql[] = "SELECT * FROM Calzado WHERE Sexo_Calzado = 1";

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}



	char nombre[100];
	char tipo[100];
	char color[100];
	char talla[100];
	float precio;

	printf("\n");
	printf("\n");
	printf("Ensenyando calzado para hombre:\n");
	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			strcpy(nombre, (char *) sqlite3_column_text(stmt, 1));
			strcpy(tipo, (char *) sqlite3_column_text(stmt, 2));
			strcpy(color, (char *) sqlite3_column_text(stmt, 3));
			strcpy(talla, (char *) sqlite3_column_text(stmt, 4));
			precio = sqlite3_column_double(stmt,5);
			printf("Nombre: %s  Tipo:%s  Color:%s  Talla:%s  Precio:%f", nombre,tipo,color,talla,precio);
		}
	} while (result == SQLITE_ROW);
 
	printf("\n");
	printf("\n");

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Prepared statement finalized (SELECT)\n");

	return SQLITE_OK;
}

// *************************** PRENDA ***************************

Prenda obtenerPrenda (sqlite3 *db, int id){
    sqlite3_stmt *stmt;
	char sql[100];

	int iden, sexo, stock;
	char nombre[100], tipo[15], color[15], talla[3];
	float precio;

	sprintf(sql, "SELECT * FROM Prenda WHERE idProducto = %i",id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	
	iden = (int)sqlite3_column_int(stmt, 0);
	strcpy(nombre, (char*)sqlite3_column_text(stmt, 1));
	strcpy(tipo, (char*)sqlite3_column_text(stmt, 2));
	strcpy(color, (char*)sqlite3_column_text(stmt, 3));
	strcpy(talla, (char*)sqlite3_column_text(stmt, 4));
	precio = (float)sqlite3_column_double(stmt, 5);
	sexo = (int)sqlite3_column_int(stmt, 6);
	stock = (int)sqlite3_column_int(stmt, 7);

	Prenda prenda = {iden, nombre, tipo, color, talla, precio, sexo, stock};

	sqlite3_finalize(stmt);

	return prenda;
}

void agregarPrenda(sqlite3 *db, char* nom, char* tipo, char* color, char* talla, float precio, int sexo, int cantidad){
    sqlite3_stmt *stmt;

	char sql[100];
	int maxId = maxIdProducto(db);

	sprintf(sql, "INSERT INTO Prenda VALUES (%i, %s, %s, %s, %s, %f, %i, %i)", maxId+1, nom, tipo, color, talla, precio, sexo, cantidad);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);

	sqlite3_finalize(stmt);
}

void subirStockPrenda (sqlite3 *db, int id, int cant){
    sqlite3_stmt *stmt;
	char sql[100];

	sprintf(sql, "UPDATE Prenda SET Stock_Prenda = Stock_Prenda + %i WHERE  ID_Prenda = %i", cant, id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}

void bajarStockPrenda(sqlite3 *db, int id, int cant){
    sqlite3_stmt *stmt;
	char sql[100];

	sprintf(sql, "UPDATE Prenda SET Stock_Prenda = Stock_Prenda - %i WHERE  ID_Prenda = %i", cant, id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}

// *************************** MATERIAL ***************************

MaterialDeportivo obtenerMaterial (sqlite3 *db, int id){
    sqlite3_stmt *stmt;
	char sql[100];

	int iden, stock;
	char nombre[100], tipo[15], color[15], talla[3], deporte[20];
	float precio;

	sprintf(sql, "SELECT * FROM MaterialDeportivo WHERE idProducto = %i",id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	
	iden = (int)sqlite3_column_int(stmt, 0);
	strcpy(nombre, (char*)sqlite3_column_text(stmt, 1));
	strcpy(tipo, (char*)sqlite3_column_text(stmt, 2));
	strcpy(color, (char*)sqlite3_column_text(stmt, 3));
	strcpy(talla, (char*)sqlite3_column_text(stmt, 4));
	precio = (float)sqlite3_column_double(stmt, 5);
	strcpy(deporte, (char*)sqlite3_column_text(stmt, 6));
	stock = (int)sqlite3_column_int(stmt, 7);

	MaterialDeportivo material = {iden, nombre, tipo, color, talla, precio, deporte, stock};

	sqlite3_finalize(stmt);

	return material;
}

void agregarMD(sqlite3 *db, char* nom, char* tipo, char* color, char* talla, float precio, char* deporte, int cantidad){
    sqlite3_stmt *stmt;

	char sql[100];
	int maxId = maxIdProducto(db);

	sprintf(sql, "INSERT INTO Material_Deportivo VALUES (%i, %s, %s, %s, %s, %f, %s, %i)", maxId+1, nom, tipo, color, talla, precio, deporte, cantidad);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);

	sqlite3_finalize(stmt);
}

void subirStockMD (sqlite3 *db, int id, int cant){
    sqlite3_stmt *stmt;
	char sql[100];

	sprintf(sql, "UPDATE Material_Deportivo SET Stock_MD = Stock_MD + %i WHERE  ID_MD = %i", cant, id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}

void bajarStockMD(sqlite3 *db, int id, int cant){
    sqlite3_stmt *stmt;
	char sql[100];

	sprintf(sql, "UPDATE Material_Deportivo SET Stock_MD = Stock_MD + %i WHERE  ID_MD = %i", cant, id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}



// *************************** SUPLEMENTO ***************************

Suplemento obtenerSuplemento (sqlite3 *db, int id){
    sqlite3_stmt *stmt;
	char sql[100];

	int iden, stock;
	char nombre[100], tipo[15];

	sprintf(sql, "SELECT * FROM Suplemento WHERE idProducto = %i",id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	
	iden = (int)sqlite3_column_int(stmt, 0);
	strcpy(nombre, (char*)sqlite3_column_text(stmt, 1));
	strcpy(tipo, (char*)sqlite3_column_text(stmt, 2));
	stock = (int)sqlite3_column_int(stmt, 3);

	Suplemento suplemento = {iden, nombre, tipo, stock};

	sqlite3_finalize(stmt);

	return suplemento;
}

void agregarSupl(sqlite3 *db, char* nom, char* tipo, int cantidad, float precio){
    sqlite3_stmt *stmt;

	char sql[100];
	int maxId = maxIdProducto(db);

	sprintf(sql, "INSERT INTO Suplemento VALUES (%i, %s, %s, %i, %f)", maxId+1, nom, tipo, cantidad, precio);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);

	sqlite3_finalize(stmt);
}

void subirStockSupl (sqlite3 *db, int id, int cant){
    sqlite3_stmt *stmt;
	char sql[100];

	sprintf(sql, "UPDATE Suplemento SET Stock_Sup = Stock_Sup + %i WHERE  ID_Sup = %i", cant, id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}

void bajarStockSupl(sqlite3 *db, int id, int cant){
    sqlite3_stmt *stmt;
	char sql[100];

	sprintf(sql, "UPDATE Suplemento SET Stock_Sup = Stock_Sup + %i WHERE  ID_Sup = %i", cant, id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
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
	iden = sqlite3_column_int(stmt, 1);
	telf = sqlite3_column_int(stmt, 2);
	strcpy(correo, (char*)sqlite3_column_text(stmt, 3));
	strcpy(direccion, (char*)sqlite3_column_text(stmt, 4));
	strcpy(contrasena, (char*)sqlite3_column_text(stmt, 5));

	persona = {nombre, iden, telf, correo, direccion, contrasena};

	sqlite3_finalize(stmt);
	return persona;
}

void registrarComprador(sqlite3 *db, char* nom, int tlf, char* correo, char* dir, char* cont){
    sqlite3_stmt *stmt;
	char sql[100];

	sprintf(sql, "INSERT INTO Comprador (Nombre_Comprador, Telefono_Comprador, Correo_Comprador, Direccion_Comprador, Contrasena_Comprador) values(%c,%d,%c,%c,%c)", nom, tlf, correo, dir, cont);
	
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}

Admin obtenerAdmin(sqlite3 *db, int id){
	sqlite3_stmt *stmt;
	char sql[100];
	char *nombre, *contrasena, *funcion;

	sprintf(sql, "SELECT * FROM Administrador WHERE Identificativo = %d", id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	strcpy(nombre, (char*)sqlite3_column_text(stmt, 0));
	strcpy(contrasena, (char*)sqlite3_column_text(stmt,2));
	strcpy(funcion, (char*)sqlite3_column_text(stmt,3));

	Admin a1 = {nombre, id, contrasena, funcion};
	sqlite3_finalize(stmt);
	return a1;
}

bool existeAdmin(sqlite3 *db, int id){
	sqlite3_stmt *stmt;
	char sql[100];

	bool respuesta;

	sprintf(sql, "SELECT COUNT(*) FROM Administrador WHERE Identificativo = %d", id);
	int size = sqlite3_step(stmt);

	sqlite3_finalize(stmt);

	if (size == 0) {
		respuesta = false;
	} else {
		respuesta = true;
	}

	return respuesta;
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
	precioTotal = (float)sqlite3_column_double(stmt, 1);
	idComprador = (int)sqlite3_column_int(stmt, 2);
	fechaCompra = (Fecha)sqlite3_column_text(stmt, 3);

	Carrito carrito = {idCompra, idComprador, precioTotal, fechaCompra};

	sqlite3_finalize(stmt);

	return carrito;
}

Compra* comprasConId (sqlite3* db, int idCompra) {
	sqlite3_stmt *stmt;

	char sql[100];
	int iden, idProd, idCompr, cant;

	sprintf(sql, "SELECT COUNT(*) FROM Compra WHERE ID_Compra = %i", idCompra);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	int size = sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	Compra* compras;
	compras = (Compra*) malloc(sizeof(Compra) * size);

	int resul;

	sprintf(sql, "SELECT * FROM Compra WHERE ID_Compra = %i", idCompra);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	Compra compra;

	do{
		resul = sqlite3_step(stmt);

		iden = sqlite3_column_int(stmt, 0);
		idProd = sqlite3_column_int(stmt, 1);
		idCompr = sqlite3_column_int(stmt, 2);
		cant = sqlite3_column_int(stmt, 3);

		compra = {iden, idProd, idCompr, cant};
		compras[resul] = compra;
	}while(resul == SQLITE_ROW);
	
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
            Calzado calz = obtenerCalzado (db, compras[i].idProducto);
            printf("%i: %s. X%i \n", num, calz.nombre, compras[i].cantidad);
        } else if (type == 'M') {
            MaterialDeportivo matD =  obtenerMaterial (db, compras[i].idProducto);
            printf("%i: %s. X%i \n", num, matD.nombre, compras[i].cantidad);
        } else if (type == 'P') {
            Prenda pren = obtenerPrenda (db, compras[i].idProducto);
            printf("%i: %s. X%i \n", num, pren.nombre, compras[i].cantidad);
        } else if (type == 'S') {
            Suplemento supl = obtenerSuplemento(db, compras[i].idProducto);
            printf("%i: %s. X%i \n", num, supl.nombre, compras[i].cantidad);
        }
	}

	printf("TOTAL: %f \n", carrito.precioTotal);
}


