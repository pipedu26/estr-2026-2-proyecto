// Autores: Juan Felipe Duran Chaparro 9035667, Carlos Eduardo Rojas Neme 9033707, Federico Galvez Gomez 9035583
#include <cstdio>
#include <string>
#include <chrono>
#include "inventario_lista.h"
#include "inventario_hash.h"
#include "inventario_map.h"

// Carga n artículos con códigos paso, 2*paso, ..., n*paso.
// Funciona con cualquiera de las tres estructuras.
template <typename T>
void cargar(T& inv, int n, int paso){
    for(int i = 0; i < n; i++){
        inv.agregar((i + 1) * paso, "articulo", 1);
    }
}

// Crea un arreglo de numConsultas códigos: uno que existe, uno que no, uno que existe...
// Quien lo pide debe liberarlo con delete[].
int* generarCodigos(int n, int paso, int numConsultas){
    int* codigos = new int[numConsultas];

    for(int j = 0; j < numConsultas; j++){
        if(j % 2 == 0){
            codigos[j] = (((j / 2) % n) + 1) * paso;   // existe
        }
        else{
            codigos[j] = (n + 1 + (j / 2)) * paso;     // no existe
        }
    }
    return codigos;
}

// Devuelve los nanosegundos promedio por consulta.
// "encontrados" sale por referencia y evita que el compilador elimine el ciclo.
template <typename T>
double medirConsultas(T& inv, const int* codigos, int numConsultas, int& encontrados){
    std::string nombre;
    int cantidad = 0;
    encontrados = 0;

    std::chrono::steady_clock::time_point inicio = std::chrono::steady_clock::now();
    for(int j = 0; j < numConsultas; j++){
        if(inv.consultar(codigos[j], nombre, cantidad)){
            encontrados = encontrados + 1;
        }
    }
    std::chrono::steady_clock::time_point fin = std::chrono::steady_clock::now();

    std::chrono::duration<double, std::nano> total = fin - inicio;
    return total.count() / numConsultas;
}

// Mide numRepeticiones veces y devuelve la mediana (ns por consulta).
// Ordena con inserción, a mano, sin usar la STL.
template <typename T>
double medirMediana(T& inv, const int* codigos, int numConsultas, int numRepeticiones){
    double* tiempos = new double[numRepeticiones];
    int encontrados = 0;

    for(int r = 0; r < numRepeticiones; r++){
        tiempos[r] = medirConsultas(inv, codigos, numConsultas, encontrados);
    }

    for(int i = 1; i < numRepeticiones; i++){
        double actual = tiempos[i];
        int j = i - 1;
        while(j >= 0 && tiempos[j] > actual){
            tiempos[j + 1] = tiempos[j];
            j = j - 1;
        }
        tiempos[j + 1] = actual;
    }

    double mediana = tiempos[numRepeticiones / 2];
    delete[] tiempos;
    return mediana;
}

// Carga la estructura, genera los códigos, mide y escribe una línea CSV.
// "paso" es 1 normalmente, o M para el caso de todos en una cubeta.
template <typename T>
void reportar(const char* nombre, T& inv, int n, int paso, int numConsultas, int repeticiones){
    cargar(inv, n, paso);
    int* codigos = generarCodigos(n, paso, numConsultas);

    // Una pasada de calentamiento que además verifica la carga.
    int encontrados = 0;
    medirConsultas(inv, codigos, numConsultas, encontrados);
    if(encontrados != numConsultas / 2){
        fprintf(stderr, "AVISO: %s n=%d encontro %d y se esperaban %d\n",
                nombre, n, encontrados, numConsultas / 2);
    }

    double ns = medirMediana(inv, codigos, numConsultas, repeticiones);
    printf("%s,%d,%.1f\n", nombre, n, ns);

    delete[] codigos;
}

int main(){
    int numConsultas = 5000;
    int repeticiones = 7;
    int tamanos[6] = {1000, 2000, 4000, 8000, 16000, 32000};

    printf("estructura,n,ns_por_consulta\n");

    for(int t = 0; t < 6; t++){
        int n = tamanos[t];

        InventarioLista lista;
        reportar("lista", lista, n, 1, numConsultas, repeticiones);

        InventarioHash hashPequeno(11);
        reportar("hash_M11", hashPequeno, n, 1, numConsultas, repeticiones);

        InventarioHash hashIgualN(n);
        reportar("hash_M_igual_n", hashIgualN, n, 1, numConsultas, repeticiones);

        InventarioHash hashPrimo(100003);
        reportar("hash_M100003", hashPrimo, n, 1, numConsultas, repeticiones);

        InventarioHash hashUnaCubeta(1009);
        reportar("hash_una_cubeta", hashUnaCubeta, n, 1009, numConsultas, repeticiones);

        InventarioMap mapa;
        reportar("map", mapa, n, 1, numConsultas, repeticiones);
    }
    return 0;
}
