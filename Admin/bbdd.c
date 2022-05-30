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

	int iden, stock;
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
	stock = (int)sqlite3_column_int(stmt, 6);

	Calzado zapatilla = {iden, stock, nombre, *tipo, *color, talla, precio};

	sqlite3_finalize(stmt);

	return zapatilla;
}

void agregarCalzado(sqlite3 *db, char* nom, char* tipo, char* color, float talla, float precio, int cantidad){
    sqlite3_stmt *stmt;

	char sql[100];
	int maxId = maxIdProducto(db);

	sprintf(sql, "INSERT INTO Calzado VALUES (%i, %s, %s, %s, %f, %f, %i)", maxId+1, nom, tipo, color, talla, precio, cantidad);
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

int sizeCalzado(sqlite3 *db){
	sqlite3_stmt *stmt;
	char sql[100];
	sprintf(sql, "SELECT COUNT(*) FROM Calzado", 1);
	int size = sqlite3_step(stmt);

	sqlite3_finalize(stmt);
	return size;
}

Calzado* showCalzado(sqlite3 *db) {
	sqlite3_stmt *stmt;

	int size= sizeCalzadoH(db);
	Calzado* listaCalzado=(Calzado*)malloc(sizeof(Calzado)*size);

	char sql[] = "SELECT * FROM Calzado";

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

			
			newCalzado.nombre=nombreM;
			newCalzado.tipo=tipoM;
			
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

	int iden, stock;
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
	stock = (int)sqlite3_column_int(stmt, 6);

	Prenda prenda = {iden, nombre, tipo, precio, stock, color, talla};

	sqlite3_finalize(stmt);

	return prenda;
}

void agregarPrenda(sqlite3 *db, char* nom, char* tipo, char* color, char* talla, float precio, int cantidad){
    sqlite3_stmt *stmt;

	char sql[100];
	int maxId = maxIdProducto(db);

	sprintf(sql, "INSERT INTO Prenda VALUES (%i, %s, %s, %s, %s, %f, %i)", maxId+1, nom, tipo, color, talla, precio, cantidad);
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

int sizePrenda(sqlite3 *db){
	sqlite3_stmt *stmt;
	char sql[100];
	sprintf(sql, "SELECT COUNT(*) FROM Prenda", 1);
	int size = sqlite3_step(stmt);

	sqlite3_finalize(stmt);
	return size;
}

Prenda* showPrenda(sqlite3 *db) {
	sqlite3_stmt *stmt;

	int size= sizeCalzadoH(db);
	Prenda* listaPrenda=(Prenda*)malloc(sizeof(Prenda)*size);

	char sql[] = "SELECT * FROM Prenda";

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

	return listaPrenda;
}

// *************************** MATERIAL ***************************

MaterialDeportivo obtenerMaterial (sqlite3 *db, int id){
    sqlite3_stmt *stmt;
	char sql[100];

	int iden, stock, talla;
	char nombre[100], tipo[15], color[15], deporte[20];
	float precio;

	sprintf(sql, "SELECT * FROM Material_Deportivo WHERE idProducto = %i",id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	
	iden = (int)sqlite3_column_int(stmt, 0);
	strcpy(nombre, (char*)sqlite3_column_text(stmt, 1));
	strcpy(tipo, (char*)sqlite3_column_text(stmt, 2));
	strcpy(color, (char*)sqlite3_column_text(stmt, 3));
	strcpy(talla, (int)sqlite3_column_int(stmt, 4));
	precio = (float)sqlite3_column_double(stmt, 5);
	strcpy(deporte, (char*)sqlite3_column_text(stmt, 6));
	stock = (int)sqlite3_column_int(stmt, 7);
 
	MaterialDeportivo material = {iden, nombre, tipo, precio, stock, color, talla,deporte};

	sqlite3_finalize(stmt);

	return material;
}

void agregarMD(sqlite3 *db, char* nom, char* tipo, char* color, int talla, float precio, char* deporte, int cantidad){
    sqlite3_stmt *stmt;

	char sql[100];
	int maxId = maxIdProducto(db);

	sprintf(sql, "INSERT INTO Material_Deportivo VALUES (%i, %s, %s, %s, %i, %f, %s, %i)", maxId+1, nom, tipo, color, talla, precio, deporte, cantidad);
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

Administrador obtenerAdmin(sqlite3 *db, int id){
	sqlite3_stmt *stmt;
	char sql[100];
	char *nombre, *contrasena, *funcion;

	sprintf(sql, "SELECT * FROM Administrador WHERE Identificativo = %d", id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	strcpy(nombre, (char*)sqlite3_column_text(stmt, 0));
	strcpy(contrasena, (char*)sqlite3_column_text(stmt,2));
	strcpy(funcion, (char*)sqlite3_column_text(stmt,3));

	Administrador a1 = {nombre, id, contrasena, funcion};
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

int idMaxAdmin(sqlite3 *db) {
	sqlite3_stmt *stmt;
	char sql[100];

	bool respuesta;

	sprintf(sql, "SELECT MAX(Identificativo) FROM Administrador");
	int max = sqlite3_column_int(stmt, 0);

	sqlite3_finalize(stmt);

	return max;
}





// ------------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------------
// COMPRAS 

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
		//cant = sqlite3_column_int(stmt, 3);

		compra.identificativo;
		compra.idProducto;
		compra.idComprador;
		compra.cantidad;

		//compras[resul] = compra;
	}while(resul == SQLITE_ROW);
	
	sqlite3_finalize(stmt);

	//return compras;
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

int ultimaCompra(sqlite3 *db){
	sqlite3_stmt *stmt;
	char sql[100];

	sprintf(sql, "SELECT * FROM Compra WHERE MAX(ID_Compra)");
	sqlite3_step(stmt);
	int iden;
	iden = sqlite3_column_int(stmt, 0);
	return iden;
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

