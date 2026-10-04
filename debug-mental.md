P0: ¿Qué me piden exactamente? 
-> Traducir a una frase matemática precisa:
    - "Minimo número de monedas" -> Minimizar X donde ...
    - "¿Es posible llegar?" -> ¿Existe camino tal que ...?
    - "Cuántas formas" -> contar |{soluciones validas}|

P1: ¿Cuáles son los objetos?
-> Listar explicitamente:
    - ¿Qué es una "solución válida"? (definir formalmente)
    - "¿Qué son las restricciones?" (desigualdades, igualdades)
    - "¿Qué es la respuesta"? (valor, si/no, estructura)

P2: ¿Cuál es el tamaño?
    - n <= 10: backtracking, permutaciones, fuerza bruta
    - n <= 20: DP con bitmask, meet-in-the-middle
    - n <= 2 * 10⁵: O(n log n), lineal, greedy con estructuras
    - n <= 10⁶: O(n), lineal simple
    - n <= 10¹⁸: matemática, binary search, fórmula cerrada

P3: ¿Qué propidades tiene la estructura?
    - ¿Es monótona?: Binary Search
    - ¿Tiene subestructura óptima?: Greedy, DP
    - ¿Se puede dividir?: Divide and conquer
    - ¿Hay repetición de estados?: Memoización
    - ¿Es un grafo?: Ver árbol de decisiones de grafos
    - ¿Es númerico?: Teoría de números, modularidad
    - ¿Es geométrico?: Sweep line, convex hull, etc.

P4: ¿Hay un problema clásico equivalente?
    - "Esto es knapsack con twist"
    - "Esto es LIS en 2D"
    - "Esto es max flow disfrazado"
    - "Esto es 2-SAT"

De esta forma, para todo problema:
1. Traducción Matemática:
Entrada:
Salida:
Formalmente: ¿Qué nos piden?

2. Ejemplo Manual:
Input: ...
¿Por qué la respuesta es ...?

3. Observaciones Claves:
- Propiedad 1: ...
- Propiedad 2: ...

4. Estrategia Candidata
Algoritmo: ...
¿Por qué funciona? 
¿Por qué podria fallar?

5. Casos Borde
- n = 0, n = 1
- Todos iguales, todos diferentes
- Sin solución posible
- Solución única
- Valores máximos/mínimos

6. Verificación
- ¿Mi solución produce la respuesta correcta para el ejemplo?
- ¿Y para un caso aleatorio pequeño que pueda verificar a mano?
