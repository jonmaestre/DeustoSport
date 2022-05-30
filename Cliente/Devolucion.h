#ifndef DEVOLUCION_H_
#define DEVOLUCION_H_

class Devolucion {

    private:
        int idCompra;
        int idComprador;
        int idProducto;
        char* explicacion;

    public:
        Devolucion(int idCompra, int idComprado, int idProducto, char* explicacion);
        Devolucion(const Devolucion& d);
        ~Devolucion();
	
};

#endif /* DEVOLUCION_H_ */