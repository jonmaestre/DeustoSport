#ifndef FUNCIONESADMIN_H_
#define FUNCIONESADMIN_H_

Administrador iniciarAdmin (sqlite3 *db);

void crearProductoAdmin (sqlite3 *db, Administrador administrador);
void recargarProoductoAdmin (sqlite3 *db, Administrador administrador);
void eliminarProductoAdmin (sqlite3 *db, Administrador administrador);
void ventanaAdmin (sqlite3 *db, Administrador administrador);

#endif