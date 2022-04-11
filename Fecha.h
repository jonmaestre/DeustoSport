#ifndef FECHA_H_
#define FECHA_H_
 
struct Fecha {
    int dia;
    int mes;
    int anio;
};

int bisiesto (int anio);
int dias_mes (struct Fecha fecha);
int cuenta_dias (struct Fecha fecha1, struct Fecha fecha2);
 
#endif