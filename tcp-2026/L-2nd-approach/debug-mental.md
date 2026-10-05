-> Estrategia Candidata:
4 5
1 2 1
2 3 1
3 4 2
4 1 2
1 3 3

Con la información de entrada, tenemos g la lista 
de vecinos para el nodo i-esimo:

Cómo debemos contar la cantidad de circuitos cerrados con pares
de colores diferentes, podemos entonces agrupar los nodos según color:
c[1][1] = { 2 }
c[1][2] = { 1, 3 }
c[1][3] = { 2 }
c[2][1] = { 4 }
c[2][3] = { 4 }
c[2][4] = { 3, 1 }
c[3][1] = { 3 }
c[3][3] = { 1 }

u = 2
v = 1 (c = 1)

c[3][3] -> 1


c[2][1] = 4
c[3][1] = 3
c[{ 4, 3 }] ?

Donde c[color][u] = v[i].

Si, comenzamos desde u = 1:
    c[1][1] = { 2 };
Iteramos sobre los vecinos de u = 1:
    { 2 }
Para v = 2:
    ¿Podemos cerrar el circuito con otro color != (c = 1)?
No. No existe c[2][2] ni c[3][2].
¿Podemos alargar con c[1][2]? 
Si, c[1][2] = { 1, 3 }.
Iteramos sobre { 1, 3 }.
Como 1 == u, continuamos.
¿Podemos cerrar el circuito con otro color usando el nodo 3?
Si. Existe c[3][3], y u esta contenido. Incrementar ans.
Además, existe c[2][3] = { 4 }.
¿Podemos desde 4 llegar a 1? 
Si. Existe c[2][4], contiene u. Incrementar ans.
