# Bitácora

## 2026-11-16

- Quiénes: Juan Felipe Durán Chaparro
- Qué hicimos: Implementé los métodos `consultarProducto` y `reponerProducto` en la clase `Inventario` (tabla hash con encadenamiento) reutilizando `buscarProductoHash`[cite: 16]. Además, corregí la lectura en el `main` para validar los retornos de `scanf` y consumir el sobrante de caracteres en caso de que se ingresen nombres largos[cite: 10, 16].
- Qué quedó pendiente: Implementar el método `listarProductos` en la tabla hash[cite: 16], mantener ambas estructuras (`InventarioLista` e `InventarioHash`) con la misma interfaz pública[cite: 4, 6], ejecutar los experimentos de rendimiento y redactar el informe final (`docs/informe-final.md`)[cite: 4, 13].

## 2026-11-16

- Quiénes: Juan Felipe Durán Chaparro
- Qué hicimos: Corregí el informe de avance (`docs/informe-avance.md`) atendiendo la retroalimentación: agregué la cita formal al texto guía (CLRS 4.ª ed. sec. 10.2 y Thareja cap. 6) en la sección 3[cite: 10], corregí el invariante estructural de la lista enlazada (frente, final y cantidadNodos)[cite: 10], ajusté el diagrama Mermaid con el estado real del inventario[cite: 10], actualicé la referencia al destructor `~Inventario`[cite: 10] y alineé la tabla de casos de prueba de la sección 5 con las salidas reales obtenidas por el programa[cite: 10].
- Qué quedó pendiente: Completar los métodos faltantes de la tabla hash en `principal.cpp` (`consultarProducto`, `reponerProducto` y `listarProductos`)[cite: 16], corregir la lectura de nombres largos[cite: 10], ejecutar los experimentos de rendimiento y redactar el informe final[cite: 4, 13].

## 2026-11-16

- Quiénes: Carlos Rojas
- Qué hicimos: Cambio de char por string en los nombres, cambio de buscarProductos para que devuelva un nodo y no un bool y asi optimizar 4 funciones que antes hacian esa busqueda.
- Qué quedó pendiente: Los metodos de eliminarProducto, consultarProducto y reponerProducto.

## 2026-11-02

- Quiénes: Federico Galvez
- Qué hicimos: Finalizacion del informe y cambios al mermail.
- Qué quedó pendiente: Revision del profesor.

## 2026-11-02

- Quiénes: Carlos Rojas
- Qué hicimos: Implementacion de POO en el codigo para tener mejor organizado para la proxima entrega y la creacion de los archivos de prueba .in y .out.
- Qué quedó pendiente:Parte del informe.

## 2026-11-02

- Quiénes: Federico Galvez
- Qué hicimos: Implementacion de `listarProductos` y `destruirLista`, escritura de costo operativo de la funciones del codigo,
- Qué quedó pendiente:crear los casos de prueba en `datos/` y completar la justificación teórica en el informe de avance.

## 2026-10-27

- Quiénes: Juan Felipe Durán Chaparro
- Qué hicimos: Implementé la función `reponerProducto` para la lista enlazada, la cual permite buscar un artículo por su código e incrementar su cantidad disponible. Agregué las validaciones de salida ("ok" o "no existe") según el enunciado e integré la lectura de argumentos y la llamada a la función dentro de la estructura principal (`main`). 
- Qué quedó pendiente: Queda pendiente implementar las funciones `listarProductos` y `destruirLista`, crear los casos de prueba en `datos/` y completar la justificación teórica en el informe de avance.

## 2026-10-26

- Quiénes: Federico Galvez
- Qué hicimos: Adelanto del informe tabla de casos de prueba y costos esperados. Trabaje en las funciones eliminarProducto y consultarProducto. eliminarProducto maneja los tres casos, actualiza final cuando se borra el último nodo y escribe "ok" o "no existe". 
				consultarProducto recorre la lista y escribe código, nombre y cantidad, o "no existe". En el main completé la lógica de ELIMINAR y de CONSULTAR, que llaman a esas dos funciones.
- Qué quedó pendiente: Queda pendiente avanzar en las partes de "REPONER" y "LISTAR" y avanzar en el informe sobre la estructura que escogimos y porque.

## 2026-10-25

- Quiénes: Carlos Rojas
- Qué hicimos: Comence el punto 1 y 2 del informe. Comence a crear la estructura del codigo, con una especie de switch, implemente strcut,crearProducto,comparacionPalabraOperacion,buscarExistencia.
- Qué quedó pendiente: Queda pendiente avanzar en las operaciones y avanzar en el informe



