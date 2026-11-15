// Autores: Juan Felipe Duran Chaparro  9035667, Carlos Eduardo Rojas Neme  9033707, Federico Galvez Gomez 9035583
#include <cstdio>
#include <string>

struct Nodo{
    int codigo = 0;
    std::string nombre = "";
    int cantidadDisponible = 0;
    Nodo* siguienteProducto = nullptr;
};

class Inventario{
    private:
        Nodo* frente;
        Nodo* final;
        int cantidadNodos;

        Nodo* buscarProducto(int codigoVerificar);


    public:
        Inventario();

        void agregarProducto(Nodo* nuevo);
        void eliminarProducto(int codigo);
        void consultarProducto(int codigo);
        void reponerProducto(int codigo, int cantidadAgregar);
        void listarProductos();

        ~Inventario(); //Destructor
};

Inventario::Inventario(){
    frente = nullptr;
    final = nullptr;
    cantidadNodos = 0;
}

bool comparacionPalabraOperacion(char operacionUsuario[21],const char operacionPrograma[21]){ //Sin el const char da error porque le esta llegando un valor ya especificado.
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

Nodo* crearProducto(int codigo, const std::string& nombre, int cantidadDisponible){
    Nodo* producto = new Nodo;
    producto->codigo = codigo;
    producto->nombre = nombre;
    producto->cantidadDisponible = cantidadDisponible;
    producto->siguienteProducto = nullptr;
    return producto;
}

Nodo* Inventario::buscarProducto(int codigoVerificar){
    Nodo* productoEncontrado = nullptr;
    Nodo* actual = frente;

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

void Inventario::agregarProducto(Nodo* nuevo){
    if(frente == nullptr){
        frente = nuevo;
        final = nuevo;
        cantidadNodos = cantidadNodos + 1;
        printf("ok\n");
    }
    else{
        if(buscarProducto(nuevo->codigo) == nullptr){
            final->siguienteProducto = nuevo;
            final = nuevo;
            cantidadNodos = cantidadNodos + 1;
            printf("ok\n");
        }
        else{
            delete nuevo;
            printf("repetido\n");
        }
    }
}

void Inventario::eliminarProducto(int codigo){

    Nodo* actual = buscarProducto(codigo);
    Nodo* anterior = nullptr;

    if(actual == nullptr){
        printf("no existe\n");
    }
    else{
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
        printf("ok\n");
    }
}

void Inventario::consultarProducto(int codigo){
    Nodo* actual = buscarProducto(codigo);

    if(actual == nullptr){
        printf("no existe\n");
    }
    else{
        printf("%d %s %d\n",actual->codigo,actual->nombre.c_str(),actual->cantidadDisponible);
    }
}

void Inventario::reponerProducto(int codigo, int cantidadAgregar){
    Nodo* actual = buscarProducto(codigo);

    if(actual != nullptr){
        actual->cantidadDisponible = actual->cantidadDisponible + cantidadAgregar;
        printf("ok\n");
    }
    else{
        printf("no existe\n");
    }
}

void Inventario::listarProductos(){
    Nodo* actual = frente;
    // printf("Hay %d productos\n", cantidadNodos); Info adicional que no esta en el enunciado
    while(actual != nullptr){
        printf("%d %s %d\n",actual->codigo,actual->nombre.c_str(),actual->cantidadDisponible);
        actual = actual->siguienteProducto;   // pasamos al siguiente nodo
    }
}

Inventario::~Inventario(){
    Nodo* actual = frente;
    Nodo* siguiente = nullptr;

    while(actual != nullptr){
        siguiente = actual->siguienteProducto;
        delete actual;
        actual = siguiente;
    }
}

int main() {
    int cantidadOrdenes = 0;
    scanf("%d",&cantidadOrdenes);
    Inventario inventario;
    for(int i = 0; i<cantidadOrdenes; i++){
        char operacion[21];
        scanf("%20s", operacion);
        //-------------------------"switch"----------------------------
        if (comparacionPalabraOperacion(operacion,"AGREGAR")){
            char nombre[201];
            int codigo = 0, cantidadDisponible = 0;

            scanf("%d %200s %d", &codigo, nombre, &cantidadDisponible);

            Nodo* producto = crearProducto(codigo,nombre,cantidadDisponible);
            inventario.agregarProducto(producto);
        }
        else if (comparacionPalabraOperacion(operacion,"ELIMINAR")){
			int codigo = 0;
			scanf("%d",&codigo);
			inventario.eliminarProducto(codigo);
        }
        else if (comparacionPalabraOperacion(operacion,"CONSULTAR")){
			int codigo = 0;
			scanf("%d",&codigo);
			inventario.consultarProducto(codigo);
        }
        else if (comparacionPalabraOperacion(operacion,"REPONER")){
			int codigo = 0;
            int cantidadAgregar = 0;
            scanf("%d %d", &codigo, &cantidadAgregar);
            inventario.reponerProducto(codigo, cantidadAgregar);
        }
        else if (comparacionPalabraOperacion(operacion,"LISTAR")){
			inventario.listarProductos();
        }

    }
    return 0;
}
