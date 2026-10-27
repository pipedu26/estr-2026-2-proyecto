# Informe del avance

*(Borren los comentarios entre paréntesis al escribir.)*

## 1. El escenario

El escenario que escogimos fue el A, el cual trata sobre el inventario de una tienda y tenemos que hacer un programa para manejar un inventario. Los productos se identifican por código y se debe permitir modificar y consultar información, por medio de las siguientes funciones: Agregar, Eliminar, Consultar, Reponer, Listar. Con este programa el dueño de una tienda va a poder tener todo su inventario organizado para poder saber que productos tienen disponibilidad y así saber cuáles ofrecer. 

## 2. Qué guarda la estructura y qué operaciones necesita
| Operación | Qué hace | Precondición |
|---|---|---|
| Agregar | Recibe código, nombre, cantidad disponible y agrega ese producto al inventario. | Agrega el producto solo si no hay ningún producto con el mismo código. |
| Eliminar | Quita un producto usando el código. | Debe existir el producto con el código indicado para poder ser borrado. |
| Consultar | Se busca un producto con el código indicado y si existe se muestra su código, nombre y cantidad existente. | Debe existir el producto con el código indicado para poder mostrar su información. |
| Reponer | Aumenta la cantidad de productos disponibles, recibe código y la cantidad de productos que se van a adicionar. | Debe existir el producto con el código indicado para poder modificar su cantidad. |
| Listar | Muestra todos los productos existentes en el inventario y escribe un producto por línea. | No requiere que exista algún producto en el inventario. |

## 3. La estructura escogida y por qué

(Por qué esa y no la otra, en términos del orden en que entran y salen
los elementos y de lo que cuesta cada operación. Citen el texto guía:
Thareja capítulo X, o CLRS 4.ª ed. capítulo Y.)

Costos esperados, con $n$ el número de elementos:

| Operación | Tiempo (peor caso) | Espacio adicional |
|---|---|---|
| Agregar | $O(n)$: la búsqueda del código repetido domina; enlazar al final es $O(1)$ | $O(1)$ |
| Eliminar | $O(n)$ | $O(1)$ |
| Consultar | $O(n)$ | $O(1)$ |
| Reponer | $O(n)$ | $O(1)$ |
| Listar | $\Theta(n)$ | $O(1)$ |

El invariante de la estructura, como fórmula:

$$I:\quad 0 \leq n \leq \text{capacidad}$$

Un diagrama del estado de la estructura, en Mermaid:

```mermaid
flowchart LR
  n1["dato 7"] --> n2["dato 3"] --> n3["dato 9"] --> nil["NULL"]
```

## 4. Qué piensan medir

(Qué entrada van a variar, entre qué tamaños, y qué esperan ver.)

## 5. Casos de prueba
 
En este avance están implementadas "ELIMINAR" y "CONSULTAR" (además de "AGREGAR", que ya estaba), así que los casos prueban esas dos operaciones. En la columna «Salida obtenida» faltan las líneas "ok" de "AGREGAR", porque "agregarProducto" todavía no las imprime; "REPONER" y "LISTAR" también están pendientes. Las demás líneas coinciden con lo esperado.
 
| Caso | Entrada | Salida esperada | Salida obtenida |
|---|---|---|---|
| funcional 1 (consultar un código que está y otro que no) | 3<br>AGREGAR 1004512 arroz 20<br>CONSULTAR 1004512<br>CONSULTAR 999 | ok<br>1004512 arroz 20<br>no existe | 1004512 arroz 20<br>no existe |
| funcional 2 (eliminar el primero) | 5<br>AGREGAR 1 pan 10<br>AGREGAR 2 leche 4<br>ELIMINAR 1<br>CONSULTAR 1<br>CONSULTAR 2 | ok<br>ok<br>ok<br>no existe<br>2 leche 4 | ok<br>no existe<br>2 leche 4 |
| funcional 3 (eliminar el último y volver a agregar) | 7<br>AGREGAR 10 sal 3<br>AGREGAR 20 ron 4<br>AGREGAR 30 te 5<br>ELIMINAR 30<br>AGREGAR 40 cafe 6<br>CONSULTAR 40<br>CONSULTAR 30 | ok<br>ok<br>ok<br>ok<br>ok<br>40 cafe 6<br>no existe | ok<br>40 cafe 6<br>no existe |
| límite 1 (lista vacía y un solo elemento) | 7<br>ELIMINAR 5<br>CONSULTAR 5<br>AGREGAR 9 x 1<br>ELIMINAR 9<br>CONSULTAR 9<br>AGREGAR 8 y 2<br>CONSULTAR 8 | no existe<br>no existe<br>ok<br>ok<br>no existe<br>ok<br>8 y 2 | no existe<br>no existe<br>ok<br>no existe<br>8 y 2 |
| límite 2 (eliminar un nodo del medio) | 6<br>AGREGAR 1 a 1<br>AGREGAR 2 b 2<br>AGREGAR 3 c 3<br>ELIMINAR 2<br>CONSULTAR 2<br>CONSULTAR 3 | ok<br>ok<br>ok<br>ok<br>no existe<br>3 c 3 | ok<br>no existe<br>3 c 3 |

(El caso límite es la estructura vacía, con un solo elemento, llena, o
con la clave repetida: digan cuál escogieron y por qué.)
