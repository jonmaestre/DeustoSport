#ifndef CLIENTEVIP_H_
#define CLIENTEVIP_H_

#include "Cliente.h"

class ClienteVip: public Cliente {
        char* nivel;

        public:
            ClienteVip(char* nombre, int identificativo, int telefono, char* correo, char* direccion, char* contrasena, char* nivel);
            ClienteVip(const ClienteVip &CV);
            virtual ~ClienteVip();

            virtual int rebajaPrecio(int precio);

            char* getNivel();
};

#endif