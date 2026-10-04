A: Traducción Inversa:
    Dado un algoritmo o implementación en código.
    ¿Qué palabras clave en un problema lo activan?

B: ¿En qué test fallaría?
¿Qué pasa con n = 1? 
¿Qué pasa si todo es igual?
¿Qué pasa si la respuesta es "imposible"?
¿Mi algoritmo asume algo que no está garantizado?

T1 - El Preguntón Sistemático:
    - "Dado un array": 
        - ¿Orden importa?
        - ¿Hay repetidos?
        - ¿Qué rango tienen los valores?

    - "Encuentra el mínimo...":
        - ¿Siempre existe?
        - ¿Puede ser infinito?
        - ¿Es único?

    - "Dos elemntos están conectados si...":
        - ¿Es simétrica?
        - ¿Transitiva?
        - ¿Reflexiva?
        - ¿Grafo implicito?

    - "Puedes realizar la siguiente operación...":
        - ¿Es reversible?
        - ¿Cuál es el invariante?
        - ¿Monótono?
    
    - "Imprime -1 si es imposible"
        - ¿Cuándo es imposible?
        - ¿Lo detecté?

T2 - Inversión del Problema:
Si no veo cómo resolverlo, pregunto:
| En lugar de... | Pregunto...  |
| :--- | :---: | 
| ¿Cómo encuentro la respuesta? | ¿Cómo verifico si X es una respuesta válida? |
| ¿Cuál es el mínimo? | ¿Puedo lograrlo con un presupuesto de K? |
| ¿Cuántas formas? | ¿Para una forma dada, cumple las restricciones? |

Esto convierte problemas de optimización en problemas de decisión:
    - Binary Search
    - Greedy Verificable
    - etc.

T3 - Reducción a lo esencial:
Debemos borrar el cuento, y extraer.
Ejemplo:
"Hay n ciudades, m caminos. Juan quiere viajar del pueblo A al pueblo B pasando por la ciudad más bonita..."

-> Nodos: Ciudades (n)
-> Aristas: Caminos (m)
-> Costos "bonita" = valor en nodo
-> Objetivo: Camino A->B maximizando máximo valor en el camino.
-> Esto es widest path problem -> modificar Dijkstra con min(max)

T4 - Generar y Verificar:
Cuando no tenga idea del algoritmo:
    - Generar TODAS las soluciones para n pequeño (n <= 8)
    - Mirar los patrones
    - ¿Es siempre óptimo greedy? ¿Hay subestructura óptima?
