#ifndef SUPLEMENTO_H_
#define SUPLEMENTO_H_


   class Suplemento
   {
   private:
      int identificativo;
      char* nombre;
      char* tipo;
      float precio;
      int stock;

   public:
      Suplemento(char* nombre, char* tipo, float precio, int stock);
      Suplemento(const Suplemento& s);
      ~Suplemento();
      int getidentificativo();
      char* getnombre();
      char* gettipo();
      float getprecio();
      int getstock();

   };


#endif