#ifndef FECHA_H_
#define FECHA_H_
 
typedef struct {
    int dia;
    int mes;
    int anio;
} Fecha;

int bisiesto(int anio);
int diasMes(Fecha* fecha);
int cuentaDias(Fecha* fecha1, Fecha* fecha2);

#endif