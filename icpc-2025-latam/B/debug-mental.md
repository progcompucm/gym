En cada paso, el número total de balones debe ser divisible por el número actual de personas.
How many sequences of N balloon contributions (each contribution between 1 and
K) satisfy the fairness rule at every step?

Two sequences are considered different if they differ at any position.

Tenemos:
    N: Miembros
    K: Número maximo de balones que un miembro puede dar.

Output:
    Output a single line with an integer indicating the number of balloon contribution sequences that
    satisfy the fairness rule.

Ejemplo 1:
N = 3, K = 3.

Salida: 5.

[1, 1, 1], [1, 3, 2], [2, 2, 2], [3, 1, 2], [3, 3, 3]

Pero por que no:
[2, 3, 2] => 2 + 3 + 2 = 7

Razonando:
De partida, vamos a tener como base, en ans, K:
    [1, 1, 1],
    [2, 2, 2],
    ...
    [K, K, K]

Luego, ¿cuántas veces podemos modificar el arreglo de modo que se cumpla la condición?
    N - 1 veces

=> 3 - 2 = 2 + K = 5.
