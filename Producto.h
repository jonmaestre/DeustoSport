#ifndef PRODUCTO_H_
#define PRODUCTO_H_

namespace productos {

    class Producto {
        protected:
            int identificativo;
            char *nombre;
            char* tipo;
            float precio;
            int stock;

        public:
            Producto(char* nombre, char* tipo, float precio, int stock);
            Producto(const Producto &p);
            virtual ~Producto();

            int getIdentificativo();
            char* getNombre();
            char* getTipo();
            float getPrecio();
            int getStock();
    };


    class Calzado : public Producto {
        private:
            char *color;
            int talla;
            int genero;
        
        public:
            Calzado(char* nombre, char* tipo, char* color, int talla, float precio, int genero, int stock);
            Calzado(const Calzado& c);
            virtual ~Calzado();
    
            char* getColor();
            int getTalla();
            int getGenero();
    };


    class MaterialDeportivo : public Producto {
        private:
            char *color;
            int talla;
            char *deporte;

        public:
            MaterialDeportivo(char* nombre, char* tipo, char* color, int talla, float precio, char* deporte, int stock);
            MaterialDeportivo(const MaterialDeportivo& md);
            virtual ~MaterialDeportivo();
    
            char* getColor();
            int getTalla();
            char* getDeporte();
    };


    class Prenda : public Producto {
        private:
            char *color;
            int talla;
            int sexo;
            
        public:
            Prenda(char* nombre, char* tipo, char* color, int talla, float precio, int sexo, int stock);
            Prenda(const Prenda& p);
            virtual ~Prenda();
    
            char* getColor();
            int getTalla();
            int getSexo();
    };


    class Suplemento : public Producto {
        private:
            int nivelEnergia;

        public:
            Suplemento(char* nombre, char* tipo, float precio, int stock, int nivelEnergia);
            Suplemento(const Suplemento& s);
            ~Suplemento();
            int getNivelEnergia();
   };

}

#endif