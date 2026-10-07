Input:
4 5
1 2 1
2 3 1
3 4 2
4 1 2
1 3 3

Tenemos:
n = 4, m = 5.

Para obtener el conjunto de nodos que pasan por un color dado:
    vector<set<ll>> nodes(m + 1);
De tamaño m + 1 dado que, en el peor de los casos tendremos tantos colores como aristas.

Luego, para poder obtener los colores que pasan por un nodo:
    vector<set<ll>> colors_by_node(n + 1);

Por lo tanto, con el input nos quedaria:
    nodes[color = 1] = [1, 2, 3]
    nodes[color = 2] = [1, 3, 4]
    nodes[color = 3] = [1, 3]
Y
    colors_by_node[node = 1] = [1, 2, 3]
    colors_by_node[node = 2] = [1]
    colors_by_node[node = 3] = [1, 2, 3]
    colors_by_node[node = 4] = [2]

Ahora:
    ans = 0
que guardara la cantidad de pares (e, f) con e != f encontrados
dentro de ciclos/loops, y:
    vector<vector<ll>> cnt(m + 1)
que guardara la cantidad de veces que hemos visto un color.

A sabiendas de que la cantidad máxima posible de colores que vamos a tener sera igual a la cantidad de aristas, iteramos desde color = 1 hasta m:
    for(ll color = 1; color <= m; color++){
        
    }

Dentro de cada iteración, obtendremos la lista de nodos
por los que pasa ese color, para color = 1:
    nodes[color = 1] = [1, 2, 3]

Para cada nodo, iteraremos sobre los colores por los que pasa, con la finalidad de identificar otro color diferente al que estamos iterando actualmente (color = 1). Como estamos guardando la lista de colores en un set, estos estaran ordenados, por lo tanto todo color "x" donde "x > color", sera un color diferente no procesado.

Con "no procesado", me refiero a que, si estamos con color = 1, "x" en algún momento, sera 2. Y procesaremos esa interacción entre color 1 y 2.
Por lo tanto, en otra iteración, cuando color = 2, la manera en la que evitamos volver a procesar la interacción con el color 1, es por medio de ese "x > color". 

Cada vez que iteremos sobre un color, para obtener la cantidad de pares diferentes que se pueden formar registraremos la cantidad de veces que vimos un color diferente respecto del actual. 
    vector<vector<ll>> seen;

Si "x > color", y es primera vez que vemos x, significa que cnt[x] == 0, entonces seen.pb(x), luego, cnt[x]++ => cnt[x] = 1.

Cuando cnt[x] = 2, significa que, dado el color que estamos iterando y el conjunto de nodos que pasan por el, fue posible que, de este conjunto de nodos, dos de ellos pasan por el color "x". Por lo tanto, si estamos obteniendo este conjunto de nodos por medio de nodes[color], se asume que ya pasan por el color que estamos iterando y, al iterar sobre los colores por los que pasan estos nodos, encontramos dos de ellos que pasan por un mismo color diferente, por lo que forman un par (e, f) con e != f y por consecuencia un ciclo. 

Sabemos que se forma un ciclo, porque, a sabiendas de:
    k = un color arbitrario.
    l = otro color, l != k.
    nodes[k] = el conjunto de nodos que pasa por el color "k".
    colors[nodes[k][i]] = el conjunto de colores que pasan por el nodo i-esimo del conjunto de nodos que pasan por el color "k".
    count[x] = la cantidad de veces que hemos visto el color "x".
Si tenemos count[x] == 2 implica que:
    1) Hemos visto el color "x" dos veces.
    2) Existe un nodes[k][i] y un nodes[k][j] que comparten "x" en 
       colors[nodes[k][i]] y colors[nodes[k][j]]
Y, como estamos obteniendo nodes[k] a partir de:
    for k = 1 ... m:
Implica tambien que, colors[nodes[k][i]] y colors[nodes[k][j]] comparten además del color "x" el color "k". Por lo tanto, se esta formando un ciclo. 
Existe un nodo, que a partir del color "k", conecta con otros nodos en donde al menos dos comparten un color "x". Si comparten un color "x", significa que, sus tramos estan unidos y ambos llegan a un mismo punto, al nodo con el color "k". 
Dado lo anterior, debemos reestablecer el contador de cuantas veces hemos visto cada nodo, por que en cada iteración sobre un valor "k" se buscara este par de colores diferentes en un ciclo implicito. 

