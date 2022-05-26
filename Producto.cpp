#include "Producto.h"
#include "stdio.h"

namespace productos {


    Producto::Producto(char* nombre, char* tipo, float precioBase, int stock) {
        sqlite3 *db;
        this->identificativo = maxIdProducto(db);
        this->nombre = new char[strlen(nombre)+1];
        this->tipo = new char[strlen(tipo)+1];
        this->precioBase = precioBase;
        this->stock = stock;
    }

    Producto::Producto(const Producto &p) {
        sqlite3 *db;
        this->identificativo = maxIdProducto(db);
        this->nombre = new char[strlen(p.nombre)+1];;
        this->tipo = new char[strlen(p.tipo)+1];;
        this->precioBase = p.precioBase;
        this->stock = p.stock;
    }

    Producto::~Producto() {
        delete[] this->nombre;
        delete[] this->tipo;
    }

    float Producto::precioFinal(){}

    int Producto::getIdentificativo() {
        return this->identificativo;
    }

    char* Producto::getNombre() {
        return this->nombre;
    }

    char* Producto::getTipo() {
        return this->tipo;
    }

    float Producto::getPrecioBase() {
        return this->precioBase;
    }

    int Producto::getStock() {
        return this->stock;
    }



    Calzado::Calzado(char* nombre, char* tipo, char* color, int talla, float precioBase, int genero, int stock): Producto(nombre, tipo, precio, stock) {
        this->color = new char[strlen(color)+1];
        this->talla = talla;
        this->genero = genero;
    }

    Calzado::Calzado(const Calzado &c) : Producto(c) {
        this->color = new char[strlen(c.color)+1];
        this->talla = c.talla;
        this->genero = c.genero;
    }

    Calzado::~Calzado() {
        delete[] color;
    }

    float Calzado::precioFinal(){
        float precioF=0.0;
        precioF+=this->getPrecioBase();
        //tipo no se lo que hace si eso luego lo implemento
        int talla=this->getTalla();
        if(talla<=40){
            precioF=precioF*1.25;
        }else if (talla<=43)
        {
            precioF=precioF*1.75;
        }else{
            precioF=precioF*2;
        }
        
        return precioF;
    }

    char* Calzado::getColor() {
       return this->color;
    }

    int Calzado::getTalla() {
        return this->talla;
    }

    int Calzado::getGenero() {
        return this->genero;
    }



    MaterialDeportivo::MaterialDeportivo(char* nombre, char* tipo, char* color, int talla, float precioBase, char* deporte, int stock): Producto(nombre, tipo, precio, stock) {
        this->color = new char[strlen(color)+1];
        this->talla = talla;
        this->deporte=new char[strlen(deporte)+1];
    }

    MaterialDeportivo::MaterialDeportivo(const MaterialDeportivo &md) : Producto(md) {  
        this->color = new char[strlen(md.color)+1];
        this->talla = md.talla;
        this->deporte = new char[strlen(md.deporte)+1];
    }

    MaterialDeportivo::~MaterialDeportivo() {
        delete[] color;
        delete[] deporte;
    }

        float MaterialDeportivo::precioFinal(){
        float precioF=0.0;
        precioF+=this->getPrecioBase();
        //tipo no se lo que hace si eso luego lo implemento
        //este por hacer ya que no se que tallas se van a usar más o menos
        int talla=this->getTalla();
        if(talla<=40){
            precioF=precioF*1.25;
        }else if (talla<=43)
        {
            precioF=precioF*1.75;
        }else{
            precioF=precioF*2;
        }
        
        return precioF;
    }

    char* MaterialDeportivo::getColor() {
       return this->color;
    }

    int MaterialDeportivo::getTalla() {
        return this->talla;
    }

    char* MaterialDeportivo::getDeporte() {
        return this->deporte;
    }



    Prenda::Prenda(char* nombre, char* tipo, char* color, int talla, float precioBase, int sexo, int stock): Producto(nombre, tipo, precio, stock) {
    this->color = new char[strlen(color)+1];
    this->talla = talla;
    this->sexo=sexo;
    }

    Prenda::Prenda(const Prenda &p) : Producto(p) {  
        this->color = new char[strlen(p.color)+1];
        this->talla = p.talla;
        this->sexo = p.sexo;
    }

    Prenda::~Prenda() {
        delete[] color;
    }

        float Prenda::precioFinal(){
        float precioF=0.0;
        precioF+=this->getPrecioBase();
        //tipo no se lo que hace si eso luego lo implemento
        //tallas a ver ya que no se si éstas commo van a ir
        int talla=this->getTalla();
        if(talla<=40){
            precioF=precioF*1.25;
        }else if (talla<=43)
        {
            precioF=precioF*1.75;
        }else{
            precioF=precioF*2;
        }

        int sexo=this->sexo;
        if(sexo==0){
            precioF==precioF*1.5;
        }else{
            precioF==precioF*1.75;
        }
        
        return precioF;
    }

    char* Prenda::getColor() {
       return this->color;
    }

    int Prenda::getTalla() {
        return this->talla;
    }

    int Prenda::getSexo() {
        return this->sexo;
    }



    Suplemento::Suplemento(char* nombre, char* tipo, float precioBase, int stock, int nivelEnergia): Producto(nombre, tipo, precioBase, stock) {
        this->nivelEnergia = nivelEnergia;
    }

    Suplemento::Suplemento(const Suplemento& s): Producto(s) {
        this->nivelEnergia = nivelEnergia;
    }

    Suplemento::~Suplemento() {
    }

        float Suplemento::precioFinal(){
        float precioF=0.0;
        precioF+=this->getPrecioBase();
        //tipo no se lo que hace si eso luego lo implemento
        //niveles de energia a discutir
        int nivEn=this->getNivelEnergia();
        if(nivEn<=40){
            precioF=precioF*1.25;
        }else if (nivEn<=43)
        {
            precioF=precioF*1.75;
        }else{
            precioF=precioF*2;
        }
        
        return precioF;
    }

    int Suplemento::getNivelEnergia() {
        return this->nivelEnergia;
    }
    
}