#ifndef COMPRA_H_
#define COMPRA_H_

class Compra
{
private:
   int identificativo;
   int idProducto;
   int idComprador;
   int cantidad;
public:
   Compra(int idProducto, int idComprador, int cantidad);
   Compra(const Compra& c);
   ~Compra();
   int getIdentificativo();
   int getIdProducto();
   int getIdComprador();
   int getCantidad();

};


#endif