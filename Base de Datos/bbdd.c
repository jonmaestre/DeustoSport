#include "bbdd.h"
#include <stdio.h>
#include <string.h>

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