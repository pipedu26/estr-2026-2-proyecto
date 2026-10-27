// Autores: Juan Felipe Duran Chaparro  9035667, Carlos Eduardo Rojas Meme  9033707, Federico Galvez Gomez 9035583
#include <cstdio>

struct Nodo{
    int codigo = 0;
    char nombre [21]; //Problema si se ingresan nombre con espacios, por ejemplo aceite de oliva
    int cantidadDisponible = 0;
    Nodo* siguienteProducto = nullptr;
};

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

bool buscarExistencia(Nodo* frente, int codigoVerificar){
    bool existe = false;
    while(frente != nullptr && existe != true){
        int codigoFrente = frente->codigo;
        if(codigoFrente == codigoVerificar){
            existe = true;
        }
        else{
            frente = frente->siguienteProducto;
        }
    }
    return existe;
}

void agregarProducto(Nodo*& frente,Nodo*& final, Nodo* nuevo){
    if(frente == nullptr){
        frente = nuevo;
        final = nuevo;
    }
    else{
        if(!buscarExistencia(frente,nuevo->codigo)){
            final->siguienteProducto = nuevo;
            final = nuevo;
        }
        else{
            printf("repetido");
        }
    }
}

void eliminarProducto(Nodo*& frente, Nodo*& final, int codigo){
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
        printf("ok\n");
    }
}
void consultarProducto(Nodo* frente, int codigo){
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



int main() {
    int cantidadOrdenes = 0;
    scanf("%d",&cantidadOrdenes);
    Nodo* frenteLista = nullptr;
    Nodo* finalLista = nullptr;
    for(int i = 0; i<cantidadOrdenes; i++){
        char operacion[21];
        scanf("%s", operacion);
        //-------------------------"switch"----------------------------
        if (comparacionPalabraOperacion(operacion,"AGREGAR")){
            char nombre[21];
            int codigo = 0, cantidadDisponible = 0;
            scanf("%d %s %d",&codigo,nombre,&cantidadDisponible);
            Nodo* producto = crearProducto(codigo,nombre,cantidadDisponible);
            agregarProducto(frenteLista,finalLista,producto);
        }
        if (comparacionPalabraOperacion(operacion,"ELIMINAR")){ 
			int codigo = 0;
			scanf("%d",&codigo);
			eliminarProducto(frenteLista,finalLista,codigo)
        }
        if (comparacionPalabraOperacion(operacion,"CONSULTAR")){
			int codigo = 0;
			scanf("%d",&codigo);
			consultarProducto(frenteLista,codigo);
        }
        if (comparacionPalabraOperacion(operacion,"REPONER")){//Faltan estas logicas----------------------------

        }
        if (comparacionPalabraOperacion(operacion,"LISTAR")){

        }



    }
    return 0;
}
