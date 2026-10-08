Nos piden:
    Determinar una secuencia de pisos f1, f2, ..., fk tal que:
        - f[1] = 1
        - f[k] = 2 * N
        - Existe un código de acceso que permita movernos de f[i] a f[i + 1]
        - No debe existir un piso f[i] y f[j] que esten monitoreados por el mismo sensor.
    
    Si no es posible determinar la ruta, imprimir "*".

Tenemos:
    N: número de pisos en la ruta.
    M: codigos de accesos.
    Luego, k integers, representando la ruta.

Razonando el ejercicio:
    Empezamos desde f[1], llegar a f[2 * N].
    Tenemos M codigos de acceso. Cada código conecta los pisos S y T (S < T) y pueden ser usados para movernos desde S a T.

    Existen N sensores. 
    Sensor i monitorea sensor i y i + N (1 <= i <= N).

    Cuando se usa un codigo de acceso, el monitor lo detecta, y le prohibe ingresar a ambos pisos que monitorea.
    Por consecuencia, podemos entrar a lo más a un piso de cada monitor.

    Pueden existir multiples soluciones.

Ejemplo 1:
Input:
1 1
1 2

Output:
*

Tenemos N = 1 y M = 1.
Eso quiere decir que tenemos 2 * 1 pisos en total, es decir 2.
Debemos llegar desde el piso 1 hasta el 2.
Y tenemos el código de acceso para llegar.

Sin embargo, es imposible ya que, el sensor asociado al piso 1 monitorea tambien al piso 1 + N = 1 + 1 = 2.

Ejemplo 2:
4 9
1 2
2 3
3 6
6 7
7 8
1 3
3 7
2 6
6 8

Output:
4
1 3 6 8

Tenemos N = 4 y M = 9.
En total tenemos: 2 * 4 = 8 pisos.

¿Por qué 1 3 6 8 es una solución valida?
Comenzamos en 1.
Nos movemos a 3:
    Utilizamos un codigo de acceso -> M = 8.
    Y ahora, se nos bloquea el piso 3 + 4 = 7.
Nos movemos a 6:
    M = 7.
    Bloqueo de piso 6 + 4 = 10.
Nos movemos a 8. Llegamos a 2 * N.

Ejemplo 3:
4 8
1 2
1 3
2 3
2 6
3 7
6 7
6 8
7 8

Output:
*

¿Por qué es imposible?
Tenemos N = 4 y M = 8.
2 * 4 = 8 pisos.

g[1] = [2, 3]
g[2] = [3, 6]
g[3] = [7]
g[4] = []
g[5] = []
g[6] = [7, 8]
g[7] = [8]
g[8] = []

Desde g[1] nos podemos mover a g[3]:
    => M = 7, bloqueo de g[3 + 4] = g[7].
       Imposible! Desde g[3] solo podemos movernos a g[7] para llegar a g[8].
    
Si nos movemos de g[1] a g[2]:
    => M = 7, bloqueo de g[2 + 4] = g[6]
       Se nos bloquea la conxión con g[6], y si nos movemos a g[3]
       volvemos a lo que ya vimos con g[1] - g[3].

Estrategia Candidata:
Dado el input:
4 9
1 2
2 3
3 6
6 7
7 8
1 3
3 7
2 6
6 8
Guardamos:
    N = 4, M = 9.
Y, los códigos de accesos que conectan nodos S con T (S < T) en una lista de adyacencia:
    g[1] = [2, 3]
    g[2] = [3, 6]
    g[3] = [6, 7]
    g[6] = [7, 8]
    g[7] = [8]
Siempre, debemos partir desde g[1]. Por lo tanto, por defecto, y dado que nada nos lo impide,
partimos desde el primer nodo conectado a g[1], en este caso, g[2].
Al hacer esto, se nos bloquea g[2 + 4] = g[6]. 
¿Tenemos algun nodo en g[2] != 6? Si: 3.
Nos movemos a g[3], se nos bloquea g[3 + 4] = g[7].
¿Tenemos algun nodo en g[3] != 6 != 7? No. Mirar otro camino desde g[1].

g[1] -> g[3], se nos bloquea g[3 + 4] = g[7].
Desde g[3], ¿tenemos algun nodo != 7? si: 6.
Nos movemos a g[6], se nos bloquea g[6 + 4] = 10.
¿Desde g[6] podemos movernos a algun nodo != 10 != 7? ¿Podemos movernos a g[8]?: Si.
¿Qué ruta recorrimos?
1 -> 3 -> 6 -> 8.

Okeyyyy, programando esta regla, como primera aproximación:
Tendremos un nodo de inicio, de donde siempre debemos movernos para llegar al nodo 2 * N:
    root_node = 1.
Sabemos que los vecinos de root_node:
    g[root_node]
Por lo tanto, por cada uno de estos vecinos, intentaremos llegar a g[8] respetando las condiciones dadas.
    each(neigh : g[root_node]){

    }
Dentro de cada iteración:
Declaramos un vector "blocked". Este no es global. Ya que si no podemos  llegar
a través de un vecino de root_node, quizas podemos llegar por medio de otro:
    vector<bool> blocked(2 * n, false)
Luego, para el BFS:
    queue<ll> q;
    vector<bool> seen(2 * N, false);
    q.push(neigh);
    seen[neigh] = true;
    while(!q.empty()){
        ll x = q.top();
        q.pop();
        each(v : g[x]){
            ...
        }
    }
Cada vez que miremos un vecino "v", lo marcaremos en blocked[v + N] y insertamos "v"
en la cola para mirar sus vecinos, hasta llegar al nodo 2 * N, en código:
    each(v : g[x]){
        if(seen[v]) continue;
        if(blocked[v + N]) continue;
        blocked[v + N] = true;
        if(v == 2 * N) break;
        q.push(v);
    }
Sin embargo, como necesitamos mostrar la ruta, registraremos los padres de cada vecino:
    vector<ll> p(2 * n, -1)
    p[seen] = root_node
    p[root_node] = 0
    each(v : g[x]){
        p[v] = u;
    }
De modo que, para mostrar la ruta cuando if(v == 2 * N):
    curr = v
    while(curr != 0){
        p(curr, endl)
        curr = p[curr]
    }