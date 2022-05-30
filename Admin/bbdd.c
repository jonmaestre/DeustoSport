#include "Administrador.h"
#include "Estructuras.h"
#include "sqlite3.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


// --------------------------------------------------------------------------------------------------
// PRODUCTOS

int maxIdProducto(sqlite3 *db){
    sqlite3_stmt *stmt;
	
	sqlite3_open("BasedeDatos.db", &db);
	char sql[100];
	sprintf(sql, "SELECT MAX(identificativo) FROM Producto");
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	int maximo = sqlite3_step(stmt);

	sqlite3_finalize(stmt);
	
	sqlite3_close(db);
	return maximo;
}


void eliminarProducto(sqlite3 *db, int id){
    sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos.db", &db);
	char sql[100];
	sprintf(sql, "DELETE FROM Producto WHERE identificativo = %d",id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

void agregarProducto(sqlite3 *db, char* tipo){
    sqlite3_stmt *stmt;

	sqlite3_open("BasedeDatos.db", &db);
	char sql[100];

	int id = maxIdProducto(db);

	sprintf(sql, "INSERT INTO Producto VALUES (%i, %s)", (id+1), tipo);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}


char obtenerTipoProducto (sqlite3 *db, int id){
    sqlite3_stmt *stmt;

	sqlite3_open("BasedeDatos.db", &db);
	char sql[100];
	char* tipo;
	tipo = malloc(10*sizeof(char));

	sprintf(sql, "SELECT tipo FROM Producto WHERE identificativo = %i",id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	//tipo = sqlite3_step(stmt);
	strcpy(tipo, (char*)sqlite3_column_text(stmt, 0));

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return tipo[0];				// C -> calzado		M -> material	P -> prenda 	S -> suplemento
}

bool existeProducto (sqlite3 *db, int id) {
	sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos.db", &db);

	char sql[100];
	int existe;

	sprintf(sql, "SELECT COUNT(*) FROM Producto WHERE identificativo = %i",id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	existe = sqlite3_step(stmt);

	sqlite3_finalize(stmt);

	bool respuesta;

	if (existe == 0) {
		respuesta = false;
	} else {
		respuesta = true;
	}
	sqlite3_close(db);

	return respuesta;	
}


// *************************** CALZADO ***************************

Calzado obtenerCalzado (sqlite3 *db, int id){
	sqlite3_open("BasedeDatos.db",&db);
    sqlite3_stmt *stmt;
	char sql[100];

	int iden, stock, talla;
	char *nombre, *tipo, *color;
	float  precio;

	nombre = malloc(100*sizeof(char));
	tipo = malloc(15*sizeof(char));
	color = malloc(15*sizeof(char));

	sprintf(sql, "SELECT * FROM Calzado WHERE identificativo = %i",id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	
	iden = (int)sqlite3_column_int(stmt, 0);
	strcpy(nombre, (char*)sqlite3_column_text(stmt, 1));
	strcpy(tipo, (char*)sqlite3_column_text(stmt, 2));
	strcpy(color, (char*)sqlite3_column_text(stmt, 3));
	talla = (int)sqlite3_column_int(stmt, 4);
	precio = (float)sqlite3_column_double(stmt, 5);
	stock = (int)sqlite3_column_int(stmt, 6);

	Calzado zapatilla = {iden, nombre, tipo, precio, stock, color, talla};

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return zapatilla;
}

void agregarCalzado(sqlite3 *db, char* nom, char* tipo, char* color, float talla, float precio, int cantidad){
    sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos.db",&db);

	char sql[100];
	int maxId = maxIdProducto(db);

	sprintf(sql, "INSERT INTO Calzado VALUES (%i, %s, %s, %f, %i, %s, %i)", maxId+1, nom, tipo, precio, cantidad, color, talla);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);

	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

void subirStockCalzado (sqlite3 *db, int id, int cant){
    sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos.db",&db);
	char sql[100];

	sprintf(sql, "UPDATE Calzado SET stock = stock + %i WHERE identificativo = %i", cant, id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

void bajarStockCalzado(sqlite3 *db, int id, int cant){
    sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos",&db);
	char sql[100];

	sprintf(sql, "UPDATE Calzado SET stock = stock - %i WHERE identificativo = %i", cant, id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

void eliminarCalzado(sqlite3 *db, int id){
    sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos.db",&db);
	char sql[100];

	sprintf(sql, "DELETE Calzado WHERE identificativo = %i", id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

int sizeCalzado(sqlite3 *db){
	sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos.db",&db);
	char sql[100];
	sprintf(sql, "SELECT COUNT(*) FROM Calzado", 1);
	int size = sqlite3_step(stmt);

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return size;
}

Calzado* showCalzado(sqlite3 *db) {
	sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos.db",&db);

	int size= sizeCalzado(db);
	Calzado* listaCalzado=(Calzado*)malloc(sizeof(Calzado)*size);

	char sql[] = "SELECT * FROM Calzado";

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		
	}
	int i=0;
	int idM;
	char nombreM[100];
	char tipoM[100];
	char colorM[100];
	int tallaM;
	float precioM;
	int StockM;

	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			idM=sqlite3_column_int(stmt,0);
			strcpy(nombreM, (char *) sqlite3_column_text(stmt, 1));
			strcpy(tipoM, (char *) sqlite3_column_text(stmt, 2));
			strcpy(colorM, (char *) sqlite3_column_text(stmt, 3));
			tallaM = sqlite3_column_int(stmt, 4);
			precioM = sqlite3_column_double(stmt,5);
			StockM=sqlite3_column_int(stmt,7);

			Calzado newCalzado={idM,nombreM,tipoM,precioM,StockM,colorM,tallaM};
			
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
	sqlite3_close(db);

	return listaCalzado;
}


// *************************** PRENDA ***************************

Prenda obtenerPrenda (sqlite3 *db, int id){
    sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos.db",&db);
	char sql[100];

	int iden, stock, talla;
	char nombre[100], tipo[15], color[15];
	float precio;

	sprintf(sql, "SELECT * FROM Prenda WHERE identificativo = %i",id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	
	iden = (int)sqlite3_column_int(stmt, 0);
	strcpy(nombre, (char*)sqlite3_column_text(stmt, 1));
	strcpy(tipo, (char*)sqlite3_column_text(stmt, 2));
	strcpy(color, (char*)sqlite3_column_text(stmt, 3));
	talla = (int)sqlite3_column_int(stmt, 4);
	precio = (float)sqlite3_column_double(stmt, 5);
	stock = (int)sqlite3_column_int(stmt, 6);

	Prenda prenda = {iden, nombre, tipo, precio, stock, color, talla};

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return prenda;
}

void agregarPrenda(sqlite3 *db, char* nom, char* tipo, char* color, char* talla, float precio, int cantidad){
    sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos.db",&db);

	char sql[100];
	int maxId = maxIdProducto(db);

	sprintf(sql, "INSERT INTO Prenda VALUES (%i, %s, %s, %f, %i, %s, %i)", maxId+1, nom, tipo, precio, cantidad, color, talla);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);

	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

void subirStockPrenda (sqlite3 *db, int id, int cant){
	sqlite3_open("BasedeDatos.db",&db);
    sqlite3_stmt *stmt;
	char sql[100];

	sprintf(sql, "UPDATE Prenda SET stock = stock + %i WHERE identificativo = %i", cant, id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

void bajarStockPrenda(sqlite3 *db, int id, int cant){
    sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos.db",&db);
	char sql[100];

	sprintf(sql, "UPDATE Prenda SET stock = stock - %i WHERE identificativo = %i", cant, id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

void eliminarPrenda(sqlite3 *db, int id){
    sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos.db",&db);
	char sql[100];

	sprintf(sql, "DELETE Prenda WHERE identificativo = %i", id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

int sizePrenda(sqlite3 *db){
	sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos.db",&db);
	char sql[100];
	sprintf(sql, "SELECT COUNT(*) FROM Prenda", 1);
	int size = sqlite3_step(stmt);

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return size;
}

Prenda* showPrenda(sqlite3 *db) {
	sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos.db", &db);

	int size= sizePrenda(db);
	Prenda* listaPrenda=(Prenda*)malloc(sizeof(Prenda)*size);

	char sql[] = "SELECT * FROM Prenda";

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		
	}
	int i=0;
	Prenda newPrenda;
	int idM, tallaM;
	char nombreM[100];
	char tipoM[100];
	char colorM[100];
	float precioM;
	int StockM;

	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			idM=sqlite3_column_int(stmt,0);
			strcpy(nombreM, (char *) sqlite3_column_text(stmt, 1));
			strcpy(tipoM, (char *) sqlite3_column_text(stmt, 2));
			strcpy(colorM, (char *) sqlite3_column_text(stmt, 3));
			tallaM = (int) sqlite3_column_int(stmt, 4);
			precioM = sqlite3_column_double(stmt,6);
			StockM = sqlite3_column_int(stmt,7);

			newPrenda.identificativo=idM;
			newPrenda.nombre=nombreM;
			newPrenda.tipo=tipoM;
			
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
	sqlite3_close(db);

	return listaPrenda;
}

// *************************** MATERIAL ***************************

MaterialDeportivo obtenerMaterial (sqlite3 *db, int id){
    sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos.db",&db);
	char sql[100];

	int iden, stock, talla;
	char nombre[100], tipo[15], color[15], deporte[20];
	float precio;

	sprintf(sql, "SELECT * FROM MaterialDeportivo WHERE identificativo = %i",id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	
	iden = (int)sqlite3_column_int(stmt, 0);
	strcpy(nombre, (char*)sqlite3_column_text(stmt, 1));
	strcpy(tipo, (char*)sqlite3_column_text(stmt, 2));
	strcpy(color, (char*)sqlite3_column_text(stmt, 3));
	talla= (int)sqlite3_column_int(stmt, 4);
	precio = (float)sqlite3_column_double(stmt, 5);
	strcpy(deporte, (char*)sqlite3_column_text(stmt, 6));
	stock = (int)sqlite3_column_int(stmt, 7);
 
	MaterialDeportivo material = {iden, nombre, tipo, precio, stock, color, talla,deporte};

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return material;
}

void agregarMD(sqlite3 *db, char* nom, char* tipo, char* color, int talla, float precio, char* deporte, int cantidad){
    sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos.db",&db);

	char sql[100];
	int maxId = maxIdProducto(db);

	sprintf(sql, "INSERT INTO MaterialDeportivo VALUES (%i, %s, %s, %f, %i, %s, %i, %s)", maxId+1, nom, tipo, precio, cantidad, color, talla, deporte);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);

	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

void subirStockMD (sqlite3 *db, int id, int cant){
    sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos.db",&db);
	char sql[100];

	sprintf(sql, "UPDATE MaterialDeportivo SET stock = stock + %i WHERE identificativo = %i", cant, id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

void bajarStockMD(sqlite3 *db, int id, int cant){
    sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos",&db);
	char sql[100];

	sprintf(sql, "UPDATE MaterialDeportivo SET stock = stock + %i WHERE identificativo = %i", cant, id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

void eliminarMD(sqlite3 *db, int id){
    sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos.db",&db);
	char sql[100];

	sprintf(sql, "DELETE MaterialDeportivo WHERE identificativo = %i", id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

int sizeMD(sqlite3 *db){
	sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos.db",&db);
	char sql[100];
	sprintf(sql, "SELECT COUNT(*) FROM MaterialDeportivo");
	int size = sqlite3_step(stmt);

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return size;
}

MaterialDeportivo* showMD(sqlite3 *db) {
	sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos.db",&db);

	int size= sizeMD(db);
	MaterialDeportivo* listaMD=(MaterialDeportivo*)malloc(sizeof(MaterialDeportivo)*size);

	char sql[] = "SELECT * FROM MaterialDeportivo";

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		
	}
	int i=0;
	MaterialDeportivo MD;
	int idM,tallaM;
	char deporteM[100];
	char nombreM[100];
	char tipoM[100];
	char colorM[100];
	float precioM;
	int StockM;

	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			idM=sqlite3_column_int(stmt,0);
			strcpy(nombreM, (char *) sqlite3_column_text(stmt, 1));
			strcpy(tipoM, (char *) sqlite3_column_text(stmt, 2));
			strcpy(colorM, (char *) sqlite3_column_text(stmt, 3));
			tallaM = (int) sqlite3_column_int(stmt, 4);
			precioM = sqlite3_column_double(stmt,5);
			strcpy(deporteM, (char *) sqlite3_column_text(stmt, 6));
			StockM=sqlite3_column_int(stmt,7);

			MD.identificativo=idM;
			MD.nombre=nombreM;
			MD.deporte=deporteM;
			MD.tipo=tipoM;
			
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
	sqlite3_close(db);

	return listaMD;
}




// ------------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------------
// USUARIOS

int maxIDComprador(sqlite3 *db){
		sqlite3_stmt *stmt;
	char sql[100];

	sprintf(sql, "SELECT MAX(identificativo) FROM Comprador");
	int max = sqlite3_column_int(stmt, 0);

	sqlite3_finalize(stmt);

	return max;
}

bool existeComprador (sqlite3 *db, char* correo) {
	sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos.db",&db);

	int* resultado;
	resultado = malloc(sizeof(int));
	bool respuesta;
	char sql[100];

	sprintf(sql, "SELECT COUNT(*) FROM Comprador WHERE correo = %s", correo);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	*resultado = sqlite3_step(stmt);

	if (resultado == NULL) {
		respuesta = false;
	} else {
		respuesta = true;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return respuesta;
}

bool compradorEsVip (sqlite3 *db, char* correo) {
	sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos.db",&db);

	int* resultado;
	resultado = malloc(sizeof(int));
	bool respuesta;
	char sql[100];

	sprintf(sql, "SELECT compradorVip FROM Comprador WHERE correo = %s", correo);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	*resultado = sqlite3_step(stmt);

	if (strcmp(resultado, "FALSE") == 0) {
		respuesta = false;
	} else {
		respuesta = true;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return respuesta;
}

Comprador obtenerComprador (sqlite3 *db, char* correo) {
	sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos.db",&db);

	Comprador persona;
	char sql[100];
	char *nombre, *direccion, *contrasena;
	nombre = malloc(15*sizeof(char));
	direccion = malloc(100*sizeof(char));
	contrasena = malloc(25*sizeof(char));
	int iden, telf;

	sprintf(sql, "SELECT * FROM Comprador WHERE correo = %s", correo);
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
	sqlite3_close(db);
	return persona;
}

CompradorVip obtenerCompradorVip (sqlite3 *db, char* correo) {
	sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos.db",&db);

	Comprador persona;
	char sql[100];
	char *nombre, *direccion, *contrasena, *nivel;
	nombre = malloc(15*sizeof(char));
	direccion = malloc(100*sizeof(char));
	contrasena = malloc(25*sizeof(char));
	nivel = malloc(10*sizeof(char));
	int iden, telf;

	sprintf(sql, "SELECT * FROM CompradorVip WHERE correo = %s", correo);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	strcpy(nombre, (char*)sqlite3_column_text(stmt, 0));
	iden = sqlite3_column_int(stmt, 1);
	telf = sqlite3_column_int(stmt, 2);
	strcpy(correo, (char*)sqlite3_column_text(stmt, 3));
	strcpy(direccion, (char*)sqlite3_column_text(stmt, 4));
	strcpy(contrasena, (char*)sqlite3_column_text(stmt, 5));
	strcpy(nivel, (char*)sqlite3_column_text(stmt, 6));

	persona.nombre=nombre;
	persona.identificativo=iden;
	persona.telefono=telf;
	persona.correo=correo;
	persona.direccion=direccion;
	persona.contrasena=contrasena;
	persona.nivel = nivel;

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return persona;
}

void registrarComprador(sqlite3 *db, char* nom, int tlf, char* correo, char* dir, char* cont, bool vip) {
    sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos.db",&db);
	char sql[100];
	int iden= maxIDComprador(db) + 1;

	if (vip) {
		sprintf(sql, "INSERT INTO Comprador (nombre, identificativo, telefono, correo, direccion, constrasena, compradorVip) values (%s, %i, %i, %s, %s, %s, TRUE)", nom, iden, tlf, correo, dir, cont);
	} else {
		sprintf(sql, "INSERT INTO Comprador (nombre, identificativo, telefono, correo, direccion, constrasena, compradorVip) values(%s,%i,%i,%s,%s,%s,FALSE)", nom, iden, tlf, correo, dir, cont);
	}

    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

void registrarCompradorVip(sqlite3 *db, char* nom, int tlf, char* correo, char* dir, char* cont, char* level) {
    sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos.db",&db);
	char sql[100];

	registrarComprador(db, nom, tlf, correo, dir, cont, TRUE);

	int iden= maxIDComprador(db);

	sprintf(sql, "INSERT INTO Comprador (nombre, identificativo, telefono, correo, direccion, constrasena, nivel) values (%s,%i,%i,%s,%s,%s,%s)", nom, iden, tlf, correo, dir, cont, level);

    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

Administrador obtenerAdmin(sqlite3 *db, int id){
	sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos.db",&db);
	char sql[100];
	char *nombre, *contrasena, *funcion;

	sprintf(sql, "SELECT * FROM Administrador WHERE identificativo = %d", id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	strcpy(nombre, (char*)sqlite3_column_text(stmt, 0));
	strcpy(contrasena, (char*)sqlite3_column_text(stmt,2));
	strcpy(funcion, (char*)sqlite3_column_text(stmt,3));

	Administrador a1 = {nombre, id, contrasena, funcion};
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return a1;
}

bool existeAdmin(sqlite3 *db, int id){
	sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos.db",&db);
	char sql[100];

	bool respuesta;

	sprintf(sql, "SELECT COUNT(*) FROM Administrador WHERE identificativo = %d", id);
	int size = sqlite3_step(stmt);

	sqlite3_finalize(stmt);

	if (size == 0) {
		respuesta = false;
	} else {
		respuesta = true;
	}
	sqlite3_close(db);

	return respuesta;
}

int idMaxAdmin(sqlite3 *db) {
	sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos.db",&db);
	char sql[100];

	sprintf(sql, "SELECT MAX(identificativo) FROM Administrador");
	int max = sqlite3_column_int(stmt, 0);

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return max;
}







// ------------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------------
// COMPRAS 

Compra comprasConId (sqlite3* db, int idCompra) {
	sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos.db",&db);
	int iden, idProd, idCompr, cant;

	int size;
	size=sizeComprasconId(db,idCompra);
	char sql[100];
	Compra* compras;
	compras = (Compra*) malloc(sizeof(Compra) * size);

	int resul;

	sprintf(sql, "SELECT * FROM Compra WHERE identificativo = %i", idCompra);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	Compra compra;

	resul = sqlite3_step(stmt);

	iden = sqlite3_column_int(stmt, 0);
	idProd = sqlite3_column_int(stmt, 1);
	idCompr = sqlite3_column_int(stmt, 2);
	cant = sqlite3_column_int(stmt, 3);

	compra.identificativo;
	compra.idProducto;
	compra.idComprador;
	compra.cantidad;

	
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return compra;
}


void agregarCompra(sqlite3 *db, Compra compra) {
	sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos.db",&db);

	char sql[100];

	sprintf(sql, "INSERT INTO Compra VALUES (%i, %i, %i, %i, %f)", compra.identificativo, compra.idProducto, compra.idComprador, compra.cantidad, compra.precio);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);

	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

bool existeCompra1 (sqlite3 *db, int idCompra, int idComprador, int idProducto) {
	sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos.db",&db);
	char sql[100];

	bool respuesta;

	sprintf(sql, "SELECT COUNT(*) FROM Compra WHERE identificativo = %i AND idProducto = %i AND idComprador = %i", idCompra, idProducto, idComprador);
	int size = sqlite3_step(stmt);

	sqlite3_finalize(stmt);

	if (size == 0) {
		respuesta = false;
	} else {
		respuesta = true;
	}
	sqlite3_close(db);

	return respuesta;
}

bool existeCompra2 (sqlite3 *db, int idCompra) {
	sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos.db",&db);
	char sql[100];

	bool respuesta;

	sprintf(sql, "SELECT COUNT(*) FROM Compra WHERE identificativo = %i", idCompra);
	int size = sqlite3_step(stmt);

	sqlite3_finalize(stmt);

	if (size == 0) {
		respuesta = false;
	} else {
		respuesta = true;
	}
	sqlite3_close(db);

	return respuesta;
}


void eliminarCompra (sqlite3 *db, int idCompra, int idComprador, int idProducto) {

	sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos.db",&db);
	char sql[100];

	Compra compra;
	compra = obtenerCompra (db, idCompra, idComprador, idProducto);

	char tipo = obtenerTipoProducto (db, idProducto);

	if (strcmp(&tipo, "C") == 0) {
		bajarStockCalzado(db, idProducto, compra.cantidad);
	} else if (strcmp(&tipo, "P") == 0) {
		bajarStockPrenda(db, idProducto, compra.cantidad);
	} else if (strcmp(&tipo, "M") == 0) {
		bajarStockMD(db, idProducto, compra.cantidad);
	} 
	
	sprintf(sql, "DELETE FROM Compra WHERE idenificativo = %i AND idProducto = %i AND idComprador = %i", idCompra, idProducto, idComprador);
	sqlite3_step(stmt);

	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

int ultimaCompra(sqlite3 *db){
	sqlite3_stmt *stmt;
	sqlite3_open("BasedeDatos.db",&db);
	char sql[100];

	sprintf(sql, "SELECT * FROM Compra WHERE MAX(identificativo)");
	sqlite3_step(stmt);
	int iden;
	iden = sqlite3_column_int(stmt, 0);
	sqlite3_close(db);
	return iden;
}


