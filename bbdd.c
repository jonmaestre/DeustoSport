#include "Administrador.h"
#include "Calzado.h"
#include "Carrito.h"
#include "Compra.h"
#include "Comprador.h"
#include "MaterialDeportivo.h"
#include "Prenda.h"
#include "Suplemento.h"
#include "bbdd.h"
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

void agregarProducto(sqlite3 *db, char* tipo){
    sqlite3_stmt *stmt;

	char sql[100];

	int id = maxIdProducto(db);

	sprintf(sql, "INSERT INTO Producto VALUES (%i, %s)", (id+1), tipo);
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

int obtenerIdProducto (sqlite3 *db, char* nombre) {
	sqlite3_stmt *stmt;

	char sql[100];
	int id;

	sprintf(sql, "SELECT idProducto FROM Producto WHERE nombre = %s", nombre);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	
	id = (sqlite3_column_int(stmt, 0));

	sqlite3_finalize(stmt);

	return id;	
}

bool existeProducto1 (sqlite3 *db, int id) {
	sqlite3_stmt *stmt;

	char sql[100];
	int existe;

	sprintf(sql, "SELECT COUNT(*) FROM Producto WHERE idProducto = %i",id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	existe = sqlite3_step(stmt);

	sqlite3_finalize(stmt);

	bool respuesta;

	if (existe == 0) {
		respuesta = false;
	} else {
		respuesta = true;
	}

	return respuesta;	
}

bool existeProducto2 (sqlite3 *db, char* nombre) {
	sqlite3_stmt *stmt;

	char sql[100];
	int existe;

	sprintf(sql, "SELECT COUNT(*) FROM Producto WHERE nombre = %s", nombre);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	existe = sqlite3_step(stmt);

	sqlite3_finalize(stmt);

	bool respuesta;

	if (existe == 0) {
		respuesta = false;
	} else {
		respuesta = true;
	}

	return respuesta;	
}

// *************************** CALZADO ***************************

Calzado obtenerCalzado (sqlite3 *db, int id){
    sqlite3_stmt *stmt;
	char sql[100];

	int iden, sexo, stock;
	char *nombre, *tipo, *color, *talla;
	float  precio;

	nombre = malloc(100*sizeof(char));
	tipo = malloc(15*sizeof(char));
	color = malloc(15*sizeof(char));

	sprintf(sql, "SELECT * FROM Calzado WHERE idProducto = %i",id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	
	iden = (int)sqlite3_column_int(stmt, 0);
	strcpy(nombre, (char*)sqlite3_column_text(stmt, 1));
	strcpy(tipo, (char*)sqlite3_column_text(stmt, 2));
	strcpy(color, (char*)sqlite3_column_text(stmt, 3));
	strcpy(talla, (char*)sqlite3_column_text(stmt, 4));
	precio = (float)sqlite3_column_double(stmt, 5);
	sexo = (int)sqlite3_column_int(stmt, 6);
	stock = (int)sqlite3_column_int(stmt, 7);

	Calzado zapatilla = {iden, nombre, tipo, color, talla, precio, sexo, stock};

	sqlite3_finalize(stmt);

	return zapatilla;
}

void agregarCalzado(sqlite3 *db, char* nom, char* tipo, char* color, float talla, float precio, int sexo, int cantidad){
    sqlite3_stmt *stmt;

	char sql[100];
	int maxId = maxIdProducto(db);

	sprintf(sql, "INSERT INTO Calzado VALUES (%i, %s, %s, %s, %f, %f, %i, %i)", maxId+1, nom, tipo, color, talla, precio, sexo, cantidad);
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

void eliminarCalzado(sqlite3 *db, int id){
    sqlite3_stmt *stmt;
	char sql[100];

	sprintf(sql, "DELETE Calzado WHERE  ID_Calzado = %i", id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}



int sizeCalzadoH(sqlite3 *db){
	sqlite3_stmt *stmt;
	char sql[100];
	sprintf(sql, "SELECT COUNT(*) FROM Calzado WHERE Sexo_Calzado = %i", 0);
	int size = sqlite3_step(stmt);

	sqlite3_finalize(stmt);
	return size;
}

int sizeCalzadoM(sqlite3 *db){
	sqlite3_stmt *stmt;
	char sql[100];
	sprintf(sql, "SELECT COUNT(*) FROM Calzado WHERE Sexo_Calzado = %i", 1);
	int size = sqlite3_step(stmt);

	sqlite3_finalize(stmt);
	return size;
}

Calzado* showCalzadoH(sqlite3 *db) {
	sqlite3_stmt *stmt;

	int size= sizeCalzadoH(db);
	Calzado* listaCalzado=(Calzado*)malloc(sizeof(Calzado)*size);

	char sql[] = "SELECT * FROM Calzado WHERE Sexo_Calzado = 0";

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		
	}
	int i=0;
	Calzado newCalzado;
	int idM;
	char nombreM[100];
	char tipoM[100];
	char colorM[100];
	char tallaM[100];
	float precioM;
	int StockM;

	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			idM=sqlite3_column_int(stmt,0);
			strcpy(nombreM, (char *) sqlite3_column_text(stmt, 1));
			strcpy(tipoM, (char *) sqlite3_column_text(stmt, 2));
			strcpy(colorM, (char *) sqlite3_column_text(stmt, 3));
			strcpy(tallaM, (char *) sqlite3_column_text(stmt, 4));
			precioM = sqlite3_column_double(stmt,5);
			StockM=sqlite3_column_int(stmt,7);

			newCalzado.id=idM;
			newCalzado.nombre=nombreM;
			newCalzado.genero=0;
			newCalzado.tipo=tipoM;
			newCalzado.precio=precioM;
			newCalzado.talla=tallaM;
			newCalzado.color=colorM;
			newCalzado.stock=StockM;

			listaCalzado[i]=newCalzado;
			i++;
			
		}
	} while (i<size);
 
	printf("\n");
	printf("\n");

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		
	}

	return listaCalzado;
}

Calzado* showCalzadoM(sqlite3 *db) {
	sqlite3_stmt *stmt;

	int size= sizeCalzadoM(db);
	Calzado* listaCalzado=(Calzado*)malloc(sizeof(Calzado)*size);

	char sql[] = "SELECT * FROM Calzado WHERE Sexo_Calzado = 1";

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		
	}
	int i=0;
	Calzado newCalzado;
	int idM;
	char nombreM[100];
	char tipoM[100];
	char colorM[100];
	char tallaM[100];
	float precioM;
	int StockM;

	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			idM=sqlite3_column_int(stmt,0);
			strcpy(nombreM, (char *) sqlite3_column_text(stmt, 1));
			strcpy(tipoM, (char *) sqlite3_column_text(stmt, 2));
			strcpy(colorM, (char *) sqlite3_column_text(stmt, 3));
			strcpy(tallaM, (char *) sqlite3_column_text(stmt, 4));
			precioM = sqlite3_column_double(stmt,5);
			StockM=sqlite3_column_int(stmt,7);

			newCalzado.id=idM;
			newCalzado.nombre=nombreM;
			newCalzado.genero=1;
			newCalzado.tipo=tipoM;
			newCalzado.precio=precioM;
			newCalzado.talla=tallaM;
			newCalzado.color=colorM;
			newCalzado.stock=StockM;

			listaCalzado[i]=newCalzado;
			i++;
			
		}
	} while (i<size);
 
	printf("\n");
	printf("\n");

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		
	}

	return listaCalzado;
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

void eliminarPrenda(sqlite3 *db, int id){
    sqlite3_stmt *stmt;
	char sql[100];

	sprintf(sql, "DELETE Prenda WHERE  ID_Prenda = %i", id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}

int sizePrendaH(sqlite3 *db){
	sqlite3_stmt *stmt;
	char sql[100];
	sprintf(sql, "SELECT COUNT(*) FROM Prenda WHERE Sexo_Prenda = %i", 0);
	int size = sqlite3_step(stmt);

	sqlite3_finalize(stmt);
	return size;
}

int sizePrendaM(sqlite3 *db){
	sqlite3_stmt *stmt;
	char sql[100];
	sprintf(sql, "SELECT COUNT(*) FROM Prenda WHERE Sexo_Prenda = %i", 1);
	int size = sqlite3_step(stmt);

	sqlite3_finalize(stmt);
	return size;
}

Prenda* showPrendaH(sqlite3 *db) {
	sqlite3_stmt *stmt;

	int size= sizeCalzadoH(db);
	Prenda* listaPrenda=(Prenda*)malloc(sizeof(Prenda)*size);

	char sql[] = "SELECT * FROM Prenda WHERE Sexo_Prenda = 0";

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		
	}
	int i=0;
	Prenda newPrenda;
	int idM;
	char nombreM[100];
	char tipoM[100];
	char colorM[100];
	char tallaM[100];
	float precioM;
	int StockM;

	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			idM=sqlite3_column_int(stmt,0);
			strcpy(nombreM, (char *) sqlite3_column_text(stmt, 1));
			strcpy(tipoM, (char *) sqlite3_column_text(stmt, 2));
			strcpy(colorM, (char *) sqlite3_column_text(stmt, 3));
			strcpy(tallaM, (char *) sqlite3_column_text(stmt, 4));
			precioM = sqlite3_column_double(stmt,6);
			StockM = sqlite3_column_int(stmt,7);

			newPrenda.identificativo=idM;
			newPrenda.nombre=nombreM;
			newPrenda.sexo=0;
			newPrenda.tipo=tipoM;
			newPrenda.precio=precioM;
			newPrenda.talla=tallaM;
			newPrenda.color=colorM;
			newPrenda.stock=StockM;

			listaPrenda[i]=newPrenda;
			i++;
			
		}
	} while (i<size);
 
	printf("\n");
	printf("\n");

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		
	}

	return listaPrenda;
}

Prenda* showPrendaM(sqlite3 *db) {
	sqlite3_stmt *stmt;

	int size= sizeCalzadoM(db);
	Prenda* listaPrenda=(Prenda*)malloc(sizeof(Prenda)*size);

	char sql[] = "SELECT * FROM Prenda WHERE Sexo_Prenda = 1";

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		
	}
	int i=0;
	Prenda newPrenda;
	int idM;
	char nombreM[100];
	char tipoM[100];
	char colorM[100];
	char tallaM[100];
	float precioM;
	int StockM;

	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			idM=sqlite3_column_int(stmt,0);
			strcpy(nombreM, (char *) sqlite3_column_text(stmt, 1));
			strcpy(tipoM, (char *) sqlite3_column_text(stmt, 2));
			strcpy(colorM, (char *) sqlite3_column_text(stmt, 3));
			strcpy(tallaM, (char *) sqlite3_column_text(stmt, 4));
			precioM = sqlite3_column_double(stmt,6);
			StockM=sqlite3_column_int(stmt,7);

			newPrenda.identificativo=idM;
			newPrenda.nombre=nombreM;
			newPrenda.sexo=1;
			newPrenda.tipo=tipoM;
			newPrenda.precio=precioM;
			newPrenda.talla=tallaM;
			newPrenda.color=colorM;
			newPrenda.stock=StockM;

			listaPrenda[i]=newPrenda;
			i++;
			
		}
	} while (i<size);
 
	printf("\n");
	printf("\n");

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		
	}

	return listaPrenda;
}
// *************************** MATERIAL ***************************

MaterialDeportivo obtenerMaterial (sqlite3 *db, int id){
    sqlite3_stmt *stmt;
	char sql[100];

	int iden, stock;
	char nombre[100], tipo[15], color[15], talla[3], deporte[20];
	float precio;

	sprintf(sql, "SELECT * FROM Material_Deportivo WHERE idProducto = %i",id);
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

void eliminarMD(sqlite3 *db, int id){
    sqlite3_stmt *stmt;
	char sql[100];

	sprintf(sql, "DELETE Material_Deportivo WHERE ID_MD = %i", id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}

int sizeMD(sqlite3 *db){
	sqlite3_stmt *stmt;
	char sql[100];
	sprintf(sql, "SELECT COUNT(*) FROM Material_Deportivo");
	int size = sqlite3_step(stmt);

	sqlite3_finalize(stmt);
	return size;
}

MaterialDeportivo* showMD(sqlite3 *db) {
	sqlite3_stmt *stmt;

	int size= sizeMD(db);
	MaterialDeportivo* listaMD=(MaterialDeportivo*)malloc(sizeof(MaterialDeportivo)*size);

	char sql[] = "SELECT * FROM Material_Deportivo";

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		
	}
	int i=0;
	MaterialDeportivo MD;
	int idM;
	char deporteM[100];
	char nombreM[100];
	char tipoM[100];
	char colorM[100];
	char tallaM[100];
	float precioM;
	int StockM;

	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			idM=sqlite3_column_int(stmt,0);
			strcpy(nombreM, (char *) sqlite3_column_text(stmt, 1));
			strcpy(tipoM, (char *) sqlite3_column_text(stmt, 2));
			strcpy(colorM, (char *) sqlite3_column_text(stmt, 3));
			strcpy(tallaM, (char *) sqlite3_column_text(stmt, 4));
			precioM = sqlite3_column_double(stmt,5);
			strcpy(deporteM, (char *) sqlite3_column_text(stmt, 6));
			StockM=sqlite3_column_int(stmt,7);

			MD.identificativo=idM;
			MD.nombre=nombreM;
			MD.deporte=deporteM;
			MD.tipo=tipoM;
			MD.precio=precioM;
			MD.talla=tallaM;
			MD.color=colorM;
			MD.stock=StockM;

			listaMD[i]=MD;
			i++;
			
		}
	} while (i<size);
 
	printf("\n");
	printf("\n");

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		
	}

	return listaMD;
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

void eliminarSupl(sqlite3 *db, int id){
    sqlite3_stmt *stmt;
	char sql[100];

	sprintf(sql, "DELETE Suplemento WHERE ID_Sup = %i", id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}

int sizeSupl(sqlite3 *db){
	sqlite3_stmt *stmt;
	char sql[100];
	sprintf(sql, "SELECT COUNT(*) FROM Suplemento");
	int size = sqlite3_step(stmt);

	sqlite3_finalize(stmt);
	return size;
}

Suplemento* showSupl(sqlite3 *db) {
	sqlite3_stmt *stmt;

	int size= sizeSupl(db);
	Suplemento* listaSupl=(Suplemento*)malloc(sizeof(Suplemento)*size);

	char sql[] = "SELECT * FROM Suplemento";

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		
	}
	int i=0;
	Suplemento supl;
	int idM;
	char nombreM[100];
	char tipoM[100];
	float precioM;
	int StockM;

	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			idM=sqlite3_column_int(stmt,0);
			strcpy(nombreM, (char *) sqlite3_column_text(stmt, 1));
			strcpy(tipoM, (char *) sqlite3_column_text(stmt, 2));
			precioM = sqlite3_column_double(stmt,3);
			StockM = sqlite3_column_int(stmt,4);

			supl.identificativo=idM;
			supl.nombre=nombreM;
			supl.tipo=tipoM;
			supl.precio=precioM;
			supl.stock=StockM;
			

			listaSupl[i]=supl;
			i++;
			
		}
	} while (i<size);
 
	printf("\n");
	printf("\n");

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		
	}

	return listaSupl;
}

// ------------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------------
// USUARIOS

bool existeComprador (sqlite3 *db, char* correo) {
	sqlite3_stmt *stmt;

	int* resultado;
	resultado = malloc(sizeof(int));
	bool respuesta;
	char sql[100];

	sprintf(sql, "SELECT COUNT(*) FROM Comprador WHERE Correo = %s", correo);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	*resultado = sqlite3_step(stmt);

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

	persona.nombre=nombre;
	persona.identificativo=iden;
	persona.telefono=telf;
	persona.correo=correo;
	persona.direccion=direccion;
	persona.contrasena=contrasena;

	sqlite3_finalize(stmt);
	return persona;
}

void registrarComprador(sqlite3 *db, char* nom, int tlf, char* correo, char* dir, char* cont){
    sqlite3_stmt *stmt;
	char sql[100];

	sprintf(sql, "INSERT INTO Comprador (Nombre_Comprador, Telefono_Comprador, Correo_Comprador, Direccion_Comprador, Contrasena_Comprador) values(%s,%i,%s,%s,%s)", nom, tlf, correo, dir, cont);
	
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

	sprintf(sql, "SELECT * FROM Carrito WHERE ID = %i", idCompra);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	
	precioTotal = (float)sqlite3_column_double(stmt, 1);
	idComprador = (int)sqlite3_column_int(stmt, 2);

	Carrito carrito = {idCompra, idComprador, precioTotal};

	sqlite3_finalize(stmt);

	return carrito;
}

int sizeComprasconId(sqlite3* db, int idCompra){
	sqlite3_stmt *stmt;

	char sql[100];

	sprintf(sql, "SELECT COUNT(*) FROM Compra WHERE ID_Compra = %i", idCompra);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	int size = sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	return size;
}

Compra* comprasConId (sqlite3* db, int idCompra) {
	sqlite3_stmt *stmt;
	int iden, idProd, idCompr, cant;

	int size=sizeComprasConId(db,idCompra);
	char sql[100];
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

		compra.identificativo=iden;
		compra.idProducto=idProd;
		compra.idComprador=idCompr;
		compra.cantidad=cant;

		compras[resul] = compra;
	}while(resul == SQLITE_ROW);
	
	sqlite3_finalize(stmt);

	return compras;
}


void verTicket (sqlite3* db, int idCompra) {

	Compra* compras;
	compras = comprasConId(db, idCompra);

	Carrito carrito = obtenerCarrito(db, idCompra);

	printf("TICKET: %i \n", idCompra);
	printf("--------------------\n");

	int i = 0;
	while (&compras[i] != NULL) {
		int num = i + 1;
		char type = obtenerTipoProducto (db, compras[i].idProducto);
        // C -> calzado		M -> material	P -> prenda 	S -> suplemento
        if (type == 'C') {
            Calzado calz = obtenerCalzado (db, compras[i].idProducto);
            printf("%i: %s. X%i (ID: %i)\n", num, calz.nombre, compras[i].cantidad, calz.id);
        } else if (type == 'M') {
            MaterialDeportivo matD =  obtenerMaterial (db, compras[i].idProducto);
            printf("%i: %s. X%i (ID: %i)\n", num, matD.nombre, compras[i].cantidad, matD.identificativo);
        } else if (type == 'P') {
            Prenda pren = obtenerPrenda (db, compras[i].idProducto);
            printf("%i: %s. X%i (ID: %i)\n", num, pren.nombre, compras[i].cantidad, pren.identificativo);
        } else if (type == 'S') {
            Suplemento supl = obtenerSuplemento(db, compras[i].idProducto);
            printf("%i: %s. X%i (ID: %i)\n", num, supl.nombre, compras[i].cantidad, supl.identificativo);
        }
	}

	printf("TOTAL: %f \n", carrito.precioTotal);
}

void agregarCarrito(sqlite3 *db, Carrito carrito) {
	sqlite3_stmt *stmt;

	char sql[100];

	sprintf(sql, "INSERT INTO Carrito VALUES (%i, %i, %f)", carrito.idCompra, carrito.idComprador, carrito.precioTotal);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);

	sqlite3_finalize(stmt);
}

void agregarCompra(sqlite3 *db, Compra compra) {
	sqlite3_stmt *stmt;

	char sql[100];

	sprintf(sql, "INSERT INTO Compra VALUES (%i, %i, %i, %i)", compra.identificativo, compra.idProducto, compra.idComprador, compra.cantidad);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);

	sqlite3_finalize(stmt);
}

bool existeCompra1 (sqlite3 *db, int idCompra, int idComprador, int idProducto) {
	sqlite3_stmt *stmt;
	char sql[100];

	bool respuesta;

	sprintf(sql, "SELECT COUNT(*) FROM Compra WHERE ID_Compra = %i AND idProducto = %i AND idComprador = %i", idCompra, idProducto, idComprador);
	int size = sqlite3_step(stmt);

	sqlite3_finalize(stmt);

	if (size == 0) {
		respuesta = false;
	} else {
		respuesta = true;
	}

	return respuesta;
}

bool existeCompra2 (sqlite3 *db, int idCompra) {
	sqlite3_stmt *stmt;
	char sql[100];

	bool respuesta;

	sprintf(sql, "SELECT COUNT(*) FROM Compra WHERE ID_Compra = %i", idCompra);
	int size = sqlite3_step(stmt);

	sqlite3_finalize(stmt);

	if (size == 0) {
		respuesta = false;
	} else {
		respuesta = true;
	}

	return respuesta;
}

void eliminarCompra (sqlite3 *db, int idCompra, int idComprador, int idProducto) {

	sqlite3_stmt *stmt;
	char sql[100];

	Compra compra = obtenerCompra (db, idCompra, idComprador, idProducto);

	char tipo = obtenerTipoProducto (db, idProducto);

	if (strcmp(&tipo, "C") == 0) {
		bajarStockCalzado(db, idProducto, compra.cantidad);
	} else if (strcmp(&tipo, "P") == 0) {
		bajarStockPrenda(db, idProducto, compra.cantidad);
	} else if (strcmp(&tipo, "M") == 0) {
		bajarStockMD(db, idProducto, compra.cantidad);
	} else if (strcmp(&tipo, "S") == 0) {
		bajarStockSupl(db, idProducto, compra.cantidad);
	}
	
	sprintf(sql, "DELETE FROM Compra WHERE ID_Compra = %i AND idProducto = %i AND idComprador = %i", idCompra, idProducto, idComprador);
	sqlite3_step(stmt);

	sqlite3_finalize(stmt);
}


Compra obtenerCompra (sqlite3 *db, int idCompra, int idComprador, int idProducto) {

	sqlite3_stmt *stmt;
	char sql[100];

	sprintf(sql, "SELECT * FROM Compra WHERE ID_Compra = %i AND idProducto = %i AND idComprador = %i", idCompra, idProducto, idComprador);
	sqlite3_step(stmt);

	Compra compra;

	int iden;
	int idProd;
	int idCompr;
	int cant;


	iden = sqlite3_column_int(stmt, 0);
	idProd = sqlite3_column_int(stmt, 1);
	idCompr = sqlite3_column_int(stmt, 2);
	cant = sqlite3_column_int(stmt, 3);

	compra.identificativo=iden;
	compra.idProducto=idProd;
	compra.idComprador=idCompr;
	compra.cantidad=cant;


	sqlite3_finalize(stmt);

	return compra;
}



// DEVOLUCIONES

void agregarDevolucion (sqlite3 *db, Compra compra, char* explicacion) {

	eliminarCompra (db, compra.identificativo, compra.idComprador, compra.idProducto);

	sqlite3_stmt *stmt;

	char sql[100];

	sprintf(sql, "INSERT INTO Devolucion VALUES (%i, %i, %i, %s)", compra.identificativo, compra.idComprador, compra.idProducto, explicacion);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);

	sqlite3_finalize(stmt);

}

