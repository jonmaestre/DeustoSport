#ifndef COMPRITA_H_
#define COMPRITA_H_

class Comprita
{
private:
   int identificativo;
   int idProducto;
   int idComprador;
   int cantidad;
public:
   Comprita(int idProducto, int idComprador, int cantidad);
   Comprita(const Comprita& c);
   ~Comprita();
   int getIdentificativo();
   int getIdProducto();
   int getIdComprador();
   int getCantidad();

};


#endif