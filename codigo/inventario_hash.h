// Autores: Juan Felipe Duran Chaparro 9035667, Carlos Eduardo Rojas Neme 9033707, Federico Galvez Gomez 9035583
#ifndef INVENTARIO_HASH_H
#define INVENTARIO_HASH_H

#include <cstdio>
#include <string>

struct NodoHash{
    int codigo = 0;
    std::string nombre = "";
    int cantidadDisponible = 0;
    NodoHash* siguienteProducto = nullptr;
};

class InventarioHash{
    private:
        NodoHash** tablaHash;
        int capacidadHash;
        int cantidadNodos;

        int funcionHash(int codigo);
        NodoHash* buscarProducto(int codigoVerificar);

    public:
        InventarioHash(int capacidad);

        bool agregar(int codigo, const std::string& nombre, int cantidad);
        bool eliminar(int codigo);
        bool consultar(int codigo, std::string& nombre, int& cantidad);
        bool reponer(int codigo, int cantidad);
        void listar(bool imprimir);

        ~InventarioHash(); //Destructor
};

inline InventarioHash::InventarioHash(int capacidad){
    if(capacidad < 1){ //Una tabla sin cubetas no sirve, se deja al menos una.
        capacidad = 1;
    }
    capacidadHash = capacidad;
    cantidadNodos = 0;

    tablaHash = new NodoHash*[capacidadHash];

    for(int i = 0; i < capacidadHash; i++){ //Todas las cubetas empiezan vacias.
        tablaHash[i] = nullptr;
    }
}

inline int InventarioHash::funcionHash(int codigo){
    int posicion = codigo % capacidadHash;
    if(posicion < 0){ //Por si llega un codigo negativo.
        posicion = posicion + capacidadHash;
    }
    return posicion;
}

inline NodoHash* InventarioHash::buscarProducto(int codigoVerificar){
    NodoHash* actual = tablaHash[funcionHash(codigoVerificar)];

    while(actual != nullptr && actual->codigo != codigoVerificar){
        actual = actual->siguienteProducto;
    }

    return actual; //Si no lo encuentra devuelve nullptr
}

inline bool InventarioHash::agregar(int codigo, const std::string& nombre, int cantidad){
    bool agregado = false;

    if(buscarProducto(codigo) == nullptr){
        int posicion = funcionHash(codigo);

        NodoHash* nuevo = new NodoHash;
        nuevo->codigo = codigo;
        nuevo->nombre = nombre;
        nuevo->cantidadDisponible = cantidad;
        nuevo->siguienteProducto = tablaHash[posicion]; //Apunta al que estaba al frente
        tablaHash[posicion] = nuevo;                    //Y queda de primero en la cubeta
        cantidadNodos = cantidadNodos + 1;
        agregado = true;
    }

    return agregado;
}

inline bool InventarioHash::eliminar(int codigo){
    bool eliminado = false;
    int posicion = funcionHash(codigo);
    NodoHash* actual = tablaHash[posicion];
    NodoHash* anterior = nullptr;

    while(actual != nullptr && actual->codigo != codigo){
        anterior = actual;
        actual = actual->siguienteProducto;
    }

    if(actual != nullptr){
        if(anterior == nullptr){ //Era el primero de la cubeta
            tablaHash[posicion] = actual->siguienteProducto;
        }
        else{
            anterior->siguienteProducto = actual->siguienteProducto;
        }
        delete actual;
        cantidadNodos = cantidadNodos - 1;
        eliminado = true;
    }

    return eliminado;
}

inline bool InventarioHash::consultar(int codigo, std::string& nombre, int& cantidad){
    bool encontrado = false;
    NodoHash* actual = buscarProducto(codigo);

    if(actual != nullptr){
        nombre = actual->nombre;
        cantidad = actual->cantidadDisponible;
        encontrado = true;
    }

    return encontrado;
}

inline bool InventarioHash::reponer(int codigo, int cantidad){
    bool repuesto = false;
    NodoHash* actual = buscarProducto(codigo);

    if(actual != nullptr){
        actual->cantidadDisponible = actual->cantidadDisponible + cantidad;
        repuesto = true;
    }

    return repuesto;
}

inline void InventarioHash::listar(bool imprimir){
    for(int i = 0; i < capacidadHash; i++){
        NodoHash* actual = tablaHash[i];
        while(actual != nullptr){
            if(imprimir){
                printf("%d %s %d\n", actual->codigo, actual->nombre.c_str(), actual->cantidadDisponible);
            }
            actual = actual->siguienteProducto;
        }
    }
}

inline InventarioHash::~InventarioHash(){
    for(int i = 0; i < capacidadHash; i++){
        while(tablaHash[i] != nullptr){
            NodoHash* temporal = tablaHash[i];
            tablaHash[i] = tablaHash[i]->siguienteProducto;
            delete temporal;
        }
    }
    delete[] tablaHash;
}

#endif
