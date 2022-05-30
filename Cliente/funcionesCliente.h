#ifndef FUNCIONESCLIENTE_H_
#define FUNCIONESCLIENTE_H_


Cliente iniciarCliente (sqlite3 *db);

Cliente registrar (sqlite3 *db);

void anadirACarrito (sqlite3 *db, int** arrayProductos, int sizeArray, int idProd, int cant);

void comprarCarrito (sqlite3 *db, Comprador comprador, int** arrayProductos, int sizeArray);

void eliminarDeCarrito (sqlite3 *db, int** arrayProductos, int* sizeArray, int indice);

int* iniciarCarrito(sqlite3 *db, Comprador comprador, int* sizeArray, int** arrayProductos);

void devolverCompra (sqlite3 *db, Comprador comprador, int idProducto, int idCompra);


#endif