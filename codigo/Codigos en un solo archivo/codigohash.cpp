// Autores: Juan Felipe Duran Chaparro 9035667, Carlos Eduardo Rojas Neme 9033707, Federico Galvez Gomez 9035583
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
        Nodo** tablaHash;
        int capacidadHash;
        int cantidadNodos;
        int funcionHash(int codigo);
        Nodo* buscarProductoHash(int codigoVerificar);


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
    capacidadHash = 50; //Dependiendo del tamaño que se quiera medir.
    cantidadNodos = 0;

    tablaHash = new Nodo*[capacidadHash]; //Se reserva el espacio para la cantidad que se declaro.

    for(int i = 0; i<capacidadHash; i++){ //Se ponen los apuntadores de cada casilla en nullptr para no tener valores indeterminados.
        tablaHash[i] = nullptr;
    }
}

int Inventario::funcionHash(int codigo){
    int posicion = codigo % capacidadHash;
    if(posicion < 0){ // Aunque se ingrese un codigo negativo, aseguramos que se pueda guardar sin que el programa explote.
        posicion = posicion + capacidadHash;
    }
    return posicion;
}

Nodo* Inventario::buscarProductoHash(int codigoVerificar){
    int posicion = funcionHash(codigoVerificar);
    Nodo* actual = tablaHash[posicion];

    while(actual != nullptr && actual->codigo != codigoVerificar){
        actual = actual->siguienteProducto;
    }
    return actual; //Si encuentra el nodo, lo devuelve, pero si no devuelve nullptr
}

Nodo* crearProducto(int codigo, const std::string& nombre, int cantidadDisponible){ // Se crea el producto con toda su informacion.
    Nodo* producto = new Nodo;
    producto->codigo = codigo;
    producto->nombre = nombre;
    producto->cantidadDisponible = cantidadDisponible;
    producto->siguienteProducto = nullptr;
    return producto;
}

void Inventario::agregarProducto(Nodo* nuevo){ // Si existe se agrega al principio de la lista de la posicion en la tabla
    Nodo* existe = buscarProductoHash(nuevo->codigo);
    int posicionHashCubeta = funcionHash(nuevo->codigo);

    if (existe != nullptr){ //Si existe simplemente se imprime repetido.
        delete nuevo;
        printf("repetido\n");
    }
    else{ //Si no existe se agrega encima de los nodos de la posicion en la tabla.
        nuevo->siguienteProducto = tablaHash[posicionHashCubeta]; // Se deja el nuevo producto apuntando al que antes estaba al frente de la lista.
        tablaHash[posicionHashCubeta] = nuevo; // Se deja el nuevo producto al frente.
        cantidadNodos = cantidadNodos + 1;
        printf("ok\n");
    }
}

void Inventario::eliminarProducto(int codigo){

    Nodo* existe = buscarProductoHash(codigo);
    int posicionHashCubeta = funcionHash(codigo);

    if(existe == nullptr){
        printf("no existe\n");
    }
    else{
        if (tablaHash[posicionHashCubeta] == existe){ // Si el producto que se quiere borrar es el primero de la cubeta, se actualiza el frente para que apunte al siguiente nodo y luego se elimina el producto.
            tablaHash[posicionHashCubeta] = existe->siguienteProducto;
            delete existe;
            cantidadNodos = cantidadNodos - 1;
            printf("ok\n");
        }
        else{
            Nodo* productoAnterior = tablaHash[posicionHashCubeta]; // Aqui se guarda el frente de la cubeta que luego se va a usar para buscar el producto que se va a borrar.
            while (productoAnterior->siguienteProducto != existe){ // Se recorre la lista hasta encontrar el nodo donde siguiente apuntador sea el producto que se quiere borrar.
                productoAnterior = productoAnterior->siguienteProducto;
            }
            Nodo* borrar = productoAnterior->siguienteProducto;
            productoAnterior->siguienteProducto = borrar->siguienteProducto; // Se conecta el producto anterior, con el producto que esta despues del elegido para ser borrado.
            delete borrar;

            cantidadNodos = cantidadNodos - 1;
            printf("ok\n");
        }
    }
}

void Inventario::consultarProducto(int codigo){
    Nodo* existe = buscarProductoHash(codigo);

    if(existe == nullptr){
        printf("no existe\n");
    }
    else{
        printf("%d %s %d\n", existe->codigo, existe->nombre.c_str(), existe->cantidadDisponible);
    }
}

void Inventario::reponerProducto(int codigo, int cantidadAgregar){
    Nodo* existe = buscarProductoHash(codigo);

    if(existe == nullptr){
        printf("no existe\n");
    }
    else{
        existe->cantidadDisponible = existe->cantidadDisponible + cantidadAgregar;
        printf("ok\n");
    }
}

void Inventario::listarProductos(){

    for(int i = 0; i < capacidadHash; i++){
        Nodo* actual = tablaHash[i]; // frente de la lista de esta cubeta (copia: la tabla real no se mueve).
        while(actual != nullptr){
            printf("%d %s %d\n", actual->codigo, actual->nombre.c_str(), actual->cantidadDisponible);
            actual = actual->siguienteProducto; // pasa al siguiente nodo de la misma cubeta.
        }
    }
}

Inventario::~Inventario(){
    for(int i = 0; i < capacidadHash; i++){
            while(tablaHash[i] != nullptr){
                Nodo* temporal = tablaHash[i];
                tablaHash[i] = tablaHash[i]->siguienteProducto;
                delete temporal;
            }
        }
        delete[] tablaHash;
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
