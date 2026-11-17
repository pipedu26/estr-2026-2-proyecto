// Autores: Juan Felipe Duran Chaparro 9035667, Carlos Eduardo Rojas Neme 9033707, Federico Galvez Gomez 9035583
#include <cstdio>
#include <string>
#if defined(USAR_HASH)
    #include "inventario_hash.h"
    #define CREAR_INVENTARIO InventarioHash inventario(50)
#elif defined(USAR_MAP)
    #include "inventario_map.h"
    #define CREAR_INVENTARIO InventarioMap inventario
#else
    #include "inventario_lista.h"
    #define CREAR_INVENTARIO InventarioLista inventario
#endif

bool comparacionPalabraOperacion(char operacionUsuario[21], const char operacionPrograma[21]){
    bool coinciden = false;
    int i = 0;
    while(operacionUsuario[i] == operacionPrograma[i] && operacionUsuario[i] != '\0'){
        i++;
    }
    if (operacionUsuario[i] == operacionPrograma[i]){
        coinciden = true;
    }
    return coinciden;
}

int main() {
    int cantidadOrdenes = 0;
    scanf("%d", &cantidadOrdenes);
    CREAR_INVENTARIO;

    for(int i = 0; i < cantidadOrdenes; i++){
        char operacion[21];
        scanf("%20s", operacion);

        if (comparacionPalabraOperacion(operacion, "AGREGAR")){
            char nombre[201];
            int codigo = 0, cantidad = 0;
            scanf("%d %200s %d", &codigo, nombre, &cantidad);

            if(inventario.agregar(codigo, nombre, cantidad)){
                printf("ok\n");
            }
            else{
                printf("repetido\n");
            }
        }
        else if (comparacionPalabraOperacion(operacion, "ELIMINAR")){
            int codigo = 0;
            scanf("%d", &codigo);

            if(inventario.eliminar(codigo)){
                printf("ok\n");
            }
            else{
                printf("no existe\n");
            }
        }
        else if (comparacionPalabraOperacion(operacion, "CONSULTAR")){
            int codigo = 0;
            int cantidad = 0;
            std::string nombre;
            scanf("%d", &codigo);

            if(inventario.consultar(codigo, nombre, cantidad)){
                printf("%d %s %d\n", codigo, nombre.c_str(), cantidad);
            }
            else{
                printf("no existe\n");
            }
        }
        else if (comparacionPalabraOperacion(operacion, "REPONER")){
            int codigo = 0;
            int cantidad = 0;
            scanf("%d %d", &codigo, &cantidad);

            if(inventario.reponer(codigo, cantidad)){
                printf("ok\n");
            }
            else{
                printf("no existe\n");
            }
        }
        else if (comparacionPalabraOperacion(operacion, "LISTAR")){
            inventario.listar(true);
        }
    }
    return 0;
}
