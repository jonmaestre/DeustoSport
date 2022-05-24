#ifndef COMPRA_H_
#define COMPRA_H_

typedef struct {
   int identificativo;
   int idProducto;
   int idComprador;
   int cantidad;
} Compra;


class Compra
{
private:
   int identificativo;
   int idProducto;
   int idComprador;
   int cantidad;
public:
   Compra(/* args */);
   ~Compra();
   int getidentificativo();
   int getidProducto();
   int getidComprador();
   int getcantidad();

};


#endif