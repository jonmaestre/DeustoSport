#ifndef PRODUCTOS_H_
#define PRODUCTOS_H_

typedef struct {
    int identificativo;
    char* nombre;
    char* tipo;
    float precioBase;
    int stock;
    char *color;
    int talla;
} Calzado;

typedef struct {
    int identificativo;
    char* nombre;
    char* tipo;
    float precioBase;
    int stock;
    char *color;
    int talla;
    char *deporte;
} MaterialDeportivo;

typedef struct {
    int identificativo;
    char* nombre;
    char* tipo;
    float precioBase;
    int stock;
    char *color;
    int talla;
} Prenda;

typedef struct {
    int idCompra;
    int idComprador;
    float precioTotal;
} Carrito;

typedef struct {
    int identificativo;
    int idProducto;
    int idComprador;
    int cantidad;
    float precio;
} Compra;

typedef struct {
    char* nombre;
    int identificativo;
    int telefono;
    char* correo;
    char* direccion;
    char* contrasena;
} Comprador;

typedef struct {
    char* nombre;
    int identificativo;
    int telefono;
    char* correo;
    char* direccion;
    char* contrasena;
    char* nivel;
} CompradorVip;


#endif