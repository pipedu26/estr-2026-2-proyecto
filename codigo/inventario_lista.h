// Autores: Juan Felipe Duran Chaparro 9035667, Carlos Eduardo Rojas Neme 9033707, Federico Galvez Gomez 9035583
#ifndef INVENTARIO_LISTA_H
#define INVENTARIO_LISTA_H

#include <cstdio>
#include <string>

struct NodoLista{
    int codigo = 0;
    std::string nombre = "";
    int cantidadDisponible = 0;
    NodoLista* siguienteProducto = nullptr;
};

class InventarioLista{
    private:
        NodoLista* frente;
        NodoLista* final;
        int cantidadNodos;

        NodoLista* buscarProducto(int codigoVerificar);

    public:
        InventarioLista();

        bool agregar(int codigo, const std::string& nombre, int cantidad);
        bool eliminar(int codigo);
        bool consultar(int codigo, std::string& nombre, int& cantidad);
        bool reponer(int codigo, int cantidad);
        void listar(bool imprimir);

        ~InventarioLista(); //Destructor
};

InventarioLista::InventarioLista(){
    frente = nullptr;
    final = nullptr;
    cantidadNodos = 0;
}

NodoLista* InventarioLista::buscarProducto(int codigoVerificar){
    NodoLista* productoEncontrado = nullptr;
    NodoLista* actual = frente;

    while(actual != nullptr && productoEncontrado == nullptr){
        if(actual->codigo == codigoVerificar){
            productoEncontrado = actual;
        }
        else{
            actual = actual->siguienteProducto;
        }
    }

    return productoEncontrado;
}

bool InventarioLista::agregar(int codigo, const std::string& nombre, int cantidad){
    bool agregado = false;

    if(buscarProducto(codigo) == nullptr){
        NodoLista* nuevo = new NodoLista;
        nuevo->codigo = codigo;
        nuevo->nombre = nombre;
        nuevo->cantidadDisponible = cantidad;
        nuevo->siguienteProducto = nullptr;

        if(frente == nullptr){
            frente = nuevo;
        }
        else{
            final->siguienteProducto = nuevo;
        }
        final = nuevo;
        cantidadNodos = cantidadNodos + 1;
        agregado = true;
    }

    return agregado;
}

bool InventarioLista::eliminar(int codigo){
    bool eliminado = false;
    NodoLista* actual = buscarProducto(codigo);
    NodoLista* anterior = nullptr;

    if(actual != nullptr){
        if(actual != frente){
            anterior = frente;

            while(anterior->siguienteProducto != actual){
                anterior = anterior->siguienteProducto;
            }
            anterior->siguienteProducto = actual->siguienteProducto;
        }
        else{
            frente = actual->siguienteProducto;
        }

        if(actual == final){
            final = anterior;
        }

        delete actual;
        cantidadNodos = cantidadNodos - 1;
        eliminado = true;
    }

    return eliminado;
}

bool InventarioLista::consultar(int codigo, std::string& nombre, int& cantidad){
    bool encontrado = false;
    NodoLista* actual = buscarProducto(codigo);

    if(actual != nullptr){
        nombre = actual->nombre;
        cantidad = actual->cantidadDisponible;
        encontrado = true;
    }

    return encontrado;
}

bool InventarioLista::reponer(int codigo, int cantidad){
    bool repuesto = false;
    NodoLista* actual = buscarProducto(codigo);

    if(actual != nullptr){
        actual->cantidadDisponible = actual->cantidadDisponible + cantidad;
        repuesto = true;
    }

    return repuesto;
}

void InventarioLista::listar(bool imprimir){
    NodoLista* actual = frente;

    while(actual != nullptr){
        if(imprimir){
            printf("%d %s %d\n", actual->codigo, actual->nombre.c_str(), actual->cantidadDisponible);
        }
        actual = actual->siguienteProducto;
    }
}

InventarioLista::~InventarioLista(){
    NodoLista* actual = frente;
    NodoLista* siguiente = nullptr;

    while(actual != nullptr){
        siguiente = actual->siguienteProducto;
        delete actual;
        actual = siguiente;
    }
}

#endif
