// Autores: Juan Felipe Duran Chaparro 9035667, Carlos Eduardo Rojas Neme 9033707, Federico Galvez Gomez 9035583
#ifndef INVENTARIO_MAP_H
#define INVENTARIO_MAP_H

#include <cstdio>
#include <map>
#include <string>

struct DatosProducto{
    std::string nombre;
    int cantidadDisponible;
};

class InventarioMap{
    private:
        std::map<int, DatosProducto> productos;

    public:
        bool agregar(int codigo, const std::string& nombre, int cantidad);
        bool eliminar(int codigo);
        bool consultar(int codigo, std::string& nombre, int& cantidad);
        bool reponer(int codigo, int cantidad);
        void listar(bool imprimir);
};

inline bool InventarioMap::agregar(int codigo, const std::string& nombre, int cantidad){
    bool agregado = false;

    if(productos.find(codigo) == productos.end()){
        DatosProducto datos;
        datos.nombre = nombre;
        datos.cantidadDisponible = cantidad;
        productos[codigo] = datos;
        agregado = true;
    }

    return agregado;
}

inline bool InventarioMap::eliminar(int codigo){
    bool eliminado = false;

    if(productos.erase(codigo) > 0){
        eliminado = true;
    }

    return eliminado;
}

inline bool InventarioMap::consultar(int codigo, std::string& nombre, int& cantidad){
    bool encontrado = false;
    std::map<int, DatosProducto>::iterator it = productos.find(codigo);

    if(it != productos.end()){
        nombre = it->second.nombre;
        cantidad = it->second.cantidadDisponible;
        encontrado = true;
    }

    return encontrado;
}

inline bool InventarioMap::reponer(int codigo, int cantidad){
    bool repuesto = false;
    std::map<int, DatosProducto>::iterator it = productos.find(codigo);

    if(it != productos.end()){
        it->second.cantidadDisponible = it->second.cantidadDisponible + cantidad;
        repuesto = true;
    }

    return repuesto;
}

inline void InventarioMap::listar(bool imprimir){
    for(std::map<int, DatosProducto>::iterator it = productos.begin(); it != productos.end(); ++it){
        if(imprimir){
            printf("%d %s %d\n", it->first, it->second.nombre.c_str(), it->second.cantidadDisponible);
        }
    }
}

#endif
