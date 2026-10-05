P0: ¿Qué me piden exactamente?
Contar la cantidad de circuitos con más de un color.

P1: ¿Qué nos dan?
n: cantidad de puntos
m: cantidad de trazos de goop

m lineas donde tenemos:
u[i], v[i], c[i]

c[i] es el id del color del trazo que une a los puntos u[i], v[i]

P2: Observaciones claves
1. Dos trazos distintos pueden unir el mismo par de puntos siempre sean de colores diferentes. 
Los trazos de un mismo color forman un camino simple. 

Esto quiere decir que puedo tener:
u[i], v[i], c[i]
[1,   2,    3]
[1,   2,    4]

2. Un par peligroso (e, f) donde e != f.
P4: Ejemplo Manual:
Output: 3
Input:
4 5
1 2 1
2 3 1
3 4 2
4 1 2
1 3 3

¿Por qué la respuesta es 3?
Tenemos n = 4, y m = 5. 
4 nodos, 5 trazos.
Luego, se nos describen esos m trazos:
[1, 2, 1]
[2, 3, 1]
[3, 4, 2]
[4, 1, 2]
[1, 3, 3]

Tenemos estos circuitos cerrados, con su color asignado:
[1, 2] [1]    [1, 2] [1]    [1, 3] [3]
[2, 3] [1] -  [2, 3] [1]  - [3, 4] [2]
[1, 3] [3]    [3, 4] [2]    [4, 1] [2]
              [4, 1] [2]

Como un par de colores (e, f) es peligroso
si usando unicamente los trazos de esos dos colores, se puede recorrer
un circuito cerrado con e != f, entonces:
(1, 3), (1, 2), (3, 2)
son pares de colores validos para los circuitos encontrados.

Luego tenemos:
Output: 0
Input:
5 4
1 2 1
2 3 1
3 4 2
4 5 2

¿Por qué la respuesta es 0?
Tenemos los trazos:
[1, 2] [1]
[2, 3] [1]
[3, 4] [2]
[4, 5] [2]

No existe ningún camino cerrado.
Luego, no podemos encontrar (e, f) peligrosos. 

-> Estrategia Candidata:
Tenemos los siguientes caminos cerrados:
[1, 2] [1]    [1, 2] [1]    [1, 3] [3]
[2, 3] [1] -  [2, 3] [1]  - [3, 4] [2]
[1, 3] [3]    [3, 4] [2]    [4, 1] [2]
              [4, 1] [2]

Con la información de entrada, tenemos g la lista 
de vecinos para el nodo i-esimo:
g[1] = [2, 3, 4]
g[2] = [1, 3]
g[3] = [1, 2, 4]
g[4] = [1, 3]

Y para el tramo (i, j) tenemos su color c[{ i, j }]:
c[{ 1, 2 }] = 1       c[{ 2, 1 }] = 1
c[{ 3, 4 }] = 2       c[{ 4, 3 }] = 2
c[{ 2, 3 }] = 1   -   c[{ 3, 2 }] = 1
c[{ 4, 1 }] = 2       c[{ 1, 4 }] = 2
c[{ 1, 3 }] = 3       c[{ 3, 1 }] = 3

¿Cómo puedo detectar un circuito cerrado?
Tomando u = 1 como nodo root:
Sabemos que los vecinos de g[1]:
    [2, 3, 4]
Y sus colores:
    [1, 3, 2] => c[{ u, v[i] }]
Creamos un arreglo para almacenar los circuitos encontrados:
    circuits = []
Otro arreglo para marcar nodos ya visitados:
    vector<bool> vis(n + 1, false)
    vis[1] = true
Comenzamos la busqueda, mirando los vecinos de u = 1:
    [2, 3, 4]
Para la primera iteración:
    v = 2
    vis[2] = true
Un tramo por si solo siempre sera un circuito cerrado, ya que
iremos desde 1 -> 2 como de 2 -> 1. Es un loop. Por lo tanto:
    circuits.pb({ 1, 2 })
Luego, miramos los vecinos de 2.
    [1, 3]
Para la primera iteración v_neigh = 1. Sin embargo, ya sabemos
que existe un circuito. Y lo creamos. Por lo que lo obviamos.
Ya sabemos de antemano que, como estamos empezando desde u = 1, nuestro
circuito siempre incluira este nodo en el inicio. 
Luego, el vecino actual (v) que estamos iterando, en este caso, 2.
    vll path = { 1, 2 }
Para la segunda iteración, v_neigh = 3. 
Haremos un BFS, por lo que crearemos una cola q, y un arreglo para
poder ir registrando las rutas de los circuitos:
    qll q;
    q.push(3)
Por medio del BFS encontraremos circuitos de este estilo:
1) En el caso de que 3 tenga una conexión con nuestro nodo de inicio u = 1:
    1 - 2 - 3 - 1 
2) En el caso de que 3 NO tenga una conexión con u = 1 pero, un vecino de 3 si la puede tener, o un vecino del vecino del vecino... 
    1 - 2 - 3 - ... - 1
Entonces con:
    qll q = [3]
    path = { 1, 2 }
    vis[3] = 1

Tendremos un: while(!q.empty())
    - 1ra iteración:
        x = 3              (q.front())
        q = [ ]            (q.pop())
        path = { 1, 2, 3 } (path.pb(x))
        
        Miramos los vecinos de 3:
            [1, 2, 4]
        - 1ra iteración:
            neigh = 1
            Si neigh es igual a u (1), quiere decir que 
            el nodo 3 nos permite llegar al inicio donde 
            comenzamos la busqueda.
            Entonces:
                path = { 1, 2, 3, 1 } (path.pb(u))
                circuits = [ path ]   (circuits.pb(path))
                path = { 1, 2, 3 }
                continue;
        - 2ra iteración:
            neigh = 2
            Nodo ya visitado. 
                continue;
        - 3ra iteración:
            neigh = 4
            Nodo no visitado.
            vis[4] = true
            Lo insertamos a la cola, para buscar una posible ruta 
            del estilo:
                1 - 2 - 3 - 4 - ... - 1
No hay más vecinos. Por lo que ahora vuelve a evaluarse
la condición del while: !q.empty()
Nuestra cola tiene:
    [4]
Por lo tanto:
    - 2ra iteración:
        x = 4
        q = [ ]
        path = { 1, 2, 3, 4 } (path.pb(4))

        Miramos los vecinos de 4:
            [1, 3]
        - 1ra iteración:
            neigh = 1
            neigh == u (1):
                path = { 1, 2, 3, 4, 1 }
                circuits.pb(path)
                path = { 1, 2, 3, 4 }
                continue;
        - 2da iteración:
            neigh = 3
            Nodo ya visitado.
Ahora la cola esta vacia.
¿Qué circuitos fueron descubiertos?
circuits = [
    { 1, 2 }
    { 1, 2, 3, 1 }
    { 1, 2, 3, 4, 1 }
]
Ahora, con estos circuitos:
    ¿cuántos de ellos tienen más de 1 color diferente en sus tramos?
Inicializamos:
    ans = 0
Iteramos por cada circuito encontrado:
    - 1era iteración:
        Circuito:
            { 1, 2 }
        Creamos un set para que, a medida de insertar el color
        de un tramo, no se inserte como valor duplicado si ya
        esta registrado:
            set<ll> colors;
        Iteramos por cada tramo del circuito. Es decir, tomando 
        un par de nodo en cada paso:
            - 1era iteración:
                u = 1
                v = 2
                c[{ 1, 2 }] = 1
                colors = [1] (colors.insert(c))
        No hay mas nodos. 
        Solo hay un color. No cumple condicion.
    
    - 2da iteración:
        Circuito:
            { 1, 2, 3, 4, 1 }
            set<ll> colors
                - 1era iteración:
                    u = 1
                    v = 2
                    c[{ 1, 2 }] = 1
                    colors = [1]
                - 2da iteración:
                    u = 2
                    v = 3
                    c[{ 2, 3 }] = 1
                    colors = [1]
                - 3era iteración:
                    u = 3
                    v = 4
                    c[{ 3, 4 }] = 2
                    colors = [1, 2]
                - 4ta iteración:
                    colors.size >= 2:   
                        Encontramos un circuito con más de un color.
                        Incrementamos ans y hacemos break;
                        ans++;
                        break;
    ...
Mostramos ans!
