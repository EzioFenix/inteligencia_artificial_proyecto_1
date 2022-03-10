```yaml
Titulo: Proyecto 1
Materia: Inteligencia artificial
Integrantes :
 - Barrera Peña Victor Miguel
 Fecha entrega : 08/03/2022
```

# Introducción



# Definición del problema

Agente viajero generalizado: sea $C$ un conjunto de ciudades en un mapa dado, particionado $C=C_{1} \cup C_{2} \cup \ldots \cup C_{n}$ tal que $C_{1} \cap C_{2} \cap \ldots \cap C_{n} \neq \emptyset$, calcular una ruta que pase por al menos una ciudad de cada partición $C_{i \leq n}$ e inicie y termine en una ciudad dada.

# Reglas con les que delimitamos el problema

Para poder resolver el problema tenemos que restringir el problema con ciertos criterios, con los cuales se planteará  el problema:

- Se define el punto de inicio y el punto final.
- El peso de ida y de regreso puede ser diferente.
- Si por un lugar existe un peso para ir de $a\rightarrow b,\text{ entonces existe también la ruta  } b \rightarrow a $. Pero el peso puede variar de ida con respecto al de regreso.
- Existe al menos una forma de llegar del punto $a \rightarrow b$, ya que de no existir el caso sería trivial.
  - Una extensión  de la clausula, es que el camino tiene que poder recorrer todas las secciones dadas como input, de lo contrario , se dice no hay solución.
- Las secciones es un conjunto ,  y cada ciudad pertenece a un conjunto.
- Si llega a existir mas de una solución optima mostrará todas ellas.
- No puede existir una ciudad que no este conectada con el resto del mapa.