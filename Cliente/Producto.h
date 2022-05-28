#ifndef PRODUCTO_H_
#define PRODUCTO_H_

namespace productos {

    class Producto {
        protected:
            int identificativo;
            char* nombre;
            char* tipo;
            float precioBase;
            int stock;

        public:
            Producto(char* nombre, char* tipo, float precioBase, int stock);
            Producto(const Producto &p);
            virtual ~Producto();

            virtual float precioFinal();

            int getIdentificativo();
            char* getNombre();
            char* getTipo();
            float getPrecioBase();
            int getStock();
    };


    class Calzado : public Producto {
        private:
            char *color;
            int talla;
        
        public:
            Calzado(char* nombre, char* tipo, char* color, int talla, float precioBase, int stock);
            Calzado(const Calzado& c);
            virtual ~Calzado();

            virtual float precioFinal();
    
            char* getColor();
            int getTalla();
    };


    class MaterialDeportivo : public Producto {
        private:
            char *color;
            int talla;
            char *deporte;

        public:
            MaterialDeportivo(char* nombre, char* tipo, char* color, int talla, float precioBase, char* deporte, int stock);
            MaterialDeportivo(const MaterialDeportivo& md);
            virtual ~MaterialDeportivo();

            virtual float precioFinal();

            char* getColor();
            int getTalla();
            char* getDeporte();
    };


    class Prenda : public Producto {
        private:
            char *color;
            int talla;
            
        public:
            Prenda(char* nombre, char* tipo, char* color, int talla, float precioBase, int stock);
            Prenda(const Prenda& p);
            virtual ~Prenda();

            virtual float precioFinal();

            char* getColor();
            int getTalla();
    };


    class Suplemento : public Producto {
        private:
            int nivelEnergia;

        public:
            Suplemento(char* nombre, char* tipo, float precioBase, int stock, int nivelEnergia);
            Suplemento(const Suplemento& s);
            ~Suplemento();

            virtual float precioFinal();

            int getNivelEnergia();
   };

}

#endif