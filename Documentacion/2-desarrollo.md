# Desarrollo

## Solución

El problema puede ejecutarse de 2 maneras, puede hacer una búsqueda por anchura y una en profundidad. La implementación  usual es en  profundidad, pero en este caso plantearé ambas para que posea un marco más amplio acerca de cuando usar una y usar otra.

## Solución en profundidad

### Explicación (primer vistazo)

Supongamos que tenemos un grafo de 5 puntos  conectados.

1. Lo convertiríamos en un árbol (imaginariamente, ya que el algoritmo sólo sabe que del nodo actual hay un camino que lo acerca al nodo final, pero no sabe cuál es ese camino. Sólo sabe que hay nodos próximos.
2. Los nodos próximos a visitar se agregan a la pila de próximos a visitar.  
3. El nodo actual se marca como visitado, para que ya no se vuelva a visitar.
4. Visitamos el siguiente nodo de la pila.
   1. Sumamos el valor desde el punto inicial hasta el nodo actual,
   2. Verificamos si se ha llegado al punto final, en caso se ser cierto comparar el valor del camino desde el punto de inicio hasta el punto actual, de ser cierto se establece el nuevo valor como valor superar y esta se establece como la ruta optima, en caso contrario se descarta esta ruta y retira el último nodo y se prueba otro camino.
5. 

## Solución en anchura 

