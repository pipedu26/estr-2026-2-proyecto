// Autores: Juan Felipe Duran Chaparro  9035667, Carlos Eduardo Rojas Meme  9033707, Federico Galvez Gomez 9035583
#include <cstdio>

struct Nodo{
    int codigo = 0;
    char nombre [21];
    int cantidadDisponible = 0;
    Nodo* siguienteProducto = nullptr;
};

class Inventario{
    private:
        Nodo* frente;
        Nodo* final;
        int cantidadNodos;

        bool buscarExistencia(int codigoVerificar);


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

Nodo* crearProducto(int codigo, char nombre[21], int cantidadDisponible){
    Nodo* producto = new Nodo;
    producto->codigo = codigo;
    int i = 0;
    while (nombre[i] != '\0'){
        producto->nombre[i] = nombre[i];
        i++;
    }
    producto->nombre[i] = '\0';
    producto->cantidadDisponible = cantidadDisponible;
    producto->siguienteProducto = nullptr;
    return producto;
}

bool Inventario::buscarExistencia(int codigoVerificar){
    bool existe = false;
    Nodo* actual = frente;
    while(actual != nullptr && existe != true){
        int codigoFrente = actual->codigo;
        if(codigoFrente == codigoVerificar){
            existe = true;
        }
        else{
            actual = actual->siguienteProducto;
        }
    }
    return existe;
}

void Inventario::agregarProducto(Nodo* nuevo){
    if(frente == nullptr){
        frente = nuevo;
        final = nuevo;
        cantidadNodos = cantidadNodos + 1;
        printf("ok\n");
    }
    else{
        if(!buscarExistencia(nuevo->codigo)){
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
    Nodo* anterior = nullptr;
    Nodo* actual = frente;
    // recorremos hasta encontrar el codigo o llegar al final de la lista.

    while(actual != nullptr && actual->codigo != codigo){
        anterior = actual;
        actual = actual->siguienteProducto;
    }

    if(actual == nullptr){
        printf("no existe\n");
    }
    else{
        if(anterior == nullptr){
            // es el primer nodo. no hay nadie antes, asi que "frente" pasa al segundo.
            frente = actual->siguienteProducto;
        }
        else{
            // esta en el medio o al final. El de atras se salta a "actual" y apunta al que sigue.
            anterior->siguienteProducto = actual->siguienteProducto;
        }
        if(actual == final){
            // si la lista tenia un solo nodo, anterior es nullptr y la lista queda vacia.
            final = anterior;
        }
        delete actual;
        cantidadNodos = cantidadNodos - 1;
        printf("ok\n");
    }
}
void Inventario::consultarProducto(int codigo){
    Nodo* actual = frente;

    while(actual != nullptr && actual->codigo != codigo){
        actual = actual->siguienteProducto;
    }
    if(actual == nullptr){
        printf("no existe\n");
    }
    else{
        printf("%d %s %d\n",actual->codigo,actual->nombre,actual->cantidadDisponible);
    }
}

void Inventario::reponerProducto(int codigo, int cantidadAgregar){
    Nodo* actual = frente;
    bool encontrado = false;

    while(actual != nullptr && !encontrado){
        if(actual->codigo == codigo){
            actual->cantidadDisponible = actual->cantidadDisponible + cantidadAgregar;
            encontrado = true;
        }
        else{
            actual = actual->siguienteProducto;
        }
    }

    if(encontrado){
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
        printf("%d %s %d\n",actual->codigo,actual->nombre,actual->cantidadDisponible);
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
            char nombre[21];
            int codigo = 0, cantidadDisponible = 0;
            scanf("%d %20s %d",&codigo,nombre,&cantidadDisponible);
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
