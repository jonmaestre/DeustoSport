#ifndef COMPRADORVIP_H_
#define COMPRADORVIP_H_

#include "Comprador.h"

class CompradorVip: public Comprador {
        char* nivel;

        public:
            CompradorVip(char* nombre, int identificativo, int telefono, char* correo, char* direccion, char* contrasena, char* nivel);
            CompradorVip(const CompradorVip &CV);
            virtual ~CompradorVip();

            virtual void funcion();

            char* getNivel();
    };

#endif