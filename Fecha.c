#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Fecha.h"
 
//función que calcula si es bisiesto un año
int bisiesto( int anio ) {
    if ( anio % 400 == 0 || ( anio % 4 == 0 && anio % 100 != 0 ) ) return 1;
    else return 0;
}
 
//función que Calcula los días de un mes
int diasMes( Fecha* fecha ) {
    switch ( fecha->mes ) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;
            break;
            
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
            break;
            
        case 2:
            if ( bisiesto ( fecha->anio ) )
                return 29;
            else
                return 28;
    }
    
    return 0;
}
 
//informa los días que hay entre dos fechas.
int cuentaDias( Fecha* fecha1, Fecha* fecha2 ) {
    int acum = 0;
    
    while ( 1 ) {
        if ( fecha1->anio == fecha2->anio && fecha1->mes == fecha2->mes )
            break;
            
        acum = acum + ( diasMes ( fecha1 ) - fecha1->dia );
        
        if ( fecha1->mes == 12 ) {
            fecha1->mes = 1;
            fecha1->anio++;
        } else
            fecha1->mes++;
            
        fecha1->dia = 0;
    }
    
    acum = acum + ( fecha2->dia - fecha1->dia );
    return acum;
}