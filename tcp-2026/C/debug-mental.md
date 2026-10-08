¿Qué tenemos?
    n: cantidad de bizcochos.
    a[i]: tamaño del i-esimo biscocho (1 <= i <= n).

Nos piden:
    Mostrar la cantidad máxima de tortas que se pueden armar.

¿Qué necesito para armar una torta?
    Torta = Conjunto de exactamente 3 bizcochos con tamaños distintos entre sí.
    
    Cada bizcocho puede usarse en a lo más una torta.

Ejemplo 1:
Input:
6
1 2 3 1 2 3

Output:
2

¿Por qué es 2?
1 2 3 => 3 bizcochos de tamaño dif
1 2 3 => lo mismo
=> 2 tortas a lo max.

Ejemplo 2:
Input:
7
4 4 4 4 7 7 9

Output:
1

¿Por qué es 1?
4 7 9 => Única combinación con alturas no repetidas.

Ejemplo 3:
Input:
5
10 10 10 10 10

Output:
0

¿Por qué es 0?
Todos los bizcochos tienen el mismo tamaño.

Estrategia Candidata 1:
Podriamos crear un mapa, tal que, guardemos como key la altura
que tiene cada bizcocho.

Para el ejemplo 1:
m[1] = 2
m[2] = 2
m[3] = 2

Vamos a tener tantas tortas como conjuntos (a, b, c) con
a != b != c podamos formar. 

Para el ejemplo 2:
m[4] = 4
m[7] = 2
m[9] = 1

Podemos observar que la respuesta para este tipo de casos sera:
    if m.size() == 3:
        ans = min_element(m)
    
Y, para casos como el ejemplo 3:
m[10] = 5

Es decir:
    if m.size() <= 2:
        cout << "0\n"

La respuesta estara en función de, para CADA conjunto (a, b, c)
con a != b != c: ans += min(m[a] m[b], m[c])?

Sin embargo, creo que lo anterior fallaria, por ejemplo:
Input:
7
1 2 3 2 3 4 4

m[1] = 1
m[2] = 2
m[3] = 2
m[4] = 2

Si elegimos (1, 2, 3), ans = min(1, 2, 2) = 1.
Sin embargo, (2, 3, 4), ans = min(2, 2, 2) = 2.

Quiero decir, tenemos otro problema: Saber que conjunto (a, b, c) elegir.

Quizas, si lo representamos como vector:

v = { { height, freq } }
v = { {1, 1}, {2, 2}, {3, 2}, {4, 2} }

Luego ordenando por cantidad:

v = { {4, 2}, {3, 2}, {2, 2}, {1, 1} }

Seria valido entonces a partir de este vector ordenado garantizar
que los 3 primeros elementos produciran la mejor selección posible:

    i = 0
    v[i] = {4, 2}
    v[i + 1] = {3, 2}
    v[i + 2] = {2, 2}

    min(v[i].second, v[i + 1].second, v[i + 2].second) = 2
    ans += 2

    i = 1
    v[i] = { 1, 1 }
    v[i + 1] = v[i + 2] = X

    ans = 2.

    Para garantizar que siempre podamos trabajar con i, i + 1 y i + 2
    y evitar el caso de i = 1, podemos:
    for(ll i = 0; i < n - 2; i += 3)

...me da WA en test 10.

Revisando:
Input:
7
1 2 3 2 3 4 4

m[1] = 1
m[2] = 2
m[3] = 2
m[4] = 2

v = { { 4, 2 }, { 3, 2 }, { 2, 2 }, { 1, 1 } }
          0         1         2         3

sz(v) = 4
ans = 0
i = 0 (0 < 2)
    v[i].S = 2         {4, 2}
    v[i + 1].S = 2     {3, 2}
    v[i + 2].S = 2     {2, 2}
    ans += min(2, min(2, 2))  (2)

i = 3 (3 < 2) 
Por lo tanto:
ans = 2.

¿En qué otros casos fallaria esta estrategia...?
¿Puede ser que la estrategia de ordenar por freq, tomar de 3 en 3 no siempre funcione?

Ya vi donde falla:
Input:
6
1 2 3 3 4 4

m[1] = 1
m[2] = 1
m[3] = 2
m[4] = 2

v = { { 4, 2 }, { 3, 2 }, { 2, 1 }, { 1, 1 } }

Actualmente estamos eligiendo:
    Una torta con 1 bizcocho de altura 4, otro de altura 3, y el último de altura 2. 

Y luego no se hace ninguna otra iteración por el i += 3,
cuando aún tenemos bizcocho disponible para hacer otra torta,
ya que tenemos:

v = { { 4, 1 }, { 3, 1 }, { 2, 0 }, { 1, 1 } }

Podemos hacer una con { 4, 1 }, { 3, 1 }, { 1, 1 }.

Okey. 
La solución es:
    Si al menos una de las frecuencias es diferente, entonces
    querra decir que, al "utilizar" los bizcochos con 
    min(v[i], ...), en el caso de que v[i + 2] sea el valor
    minimo, nos sobrara bizcocho aún en v[i] y v[i + 1],
    si v[i + 1] es el minimo, nos sobrara en v[i] y v[i + 2].

    Debemos permanecer en i hasta que v[i].S == 0.
    Y eso implica que, cuando v[i + 1].S o v[i + 2].S
    se hagan 0 debamos "ignorarlos" para que v[i + ...] pase
    a ser el indice de bizcocho disponible hasta que v[i].S se consuma.

Se me ocurre:
    ans = 0
    offset = 0
    for(ll i = 0; i < sz(v) - 2; i += 3){
        while(v[i].S > 0){
            max_cakes = min(v[i].S, min(v[i + 1].S, v[i + 2].S))
            v[i].S -= max_cakes
            v[i + 1].S -= max_cakes
            v[i + 2].S -= max_cakes
            ans += max_cakes

                if(v[i].S == 0) break;

            if(v[i + 1].S == 0){
                swap(v[i + 1], v[sz(v) - 1 - offset])
                offset++
            }

            if(v[i + 2].S == 0){
                swap(v[i + 2], v[sz(v) - 1 - offset])
                offset++
            }
        }
    }

Con lo anterior, si tenemos:
    v = { { 4, 2 }, { 3, 2 }, { 2, 1 }, { 1, 1 } }
Entonces, para la primera iteración:
    target = 2
Para la primera iteración del while:
    while(V[i].S > 0){
        max_cakes = 1
        ans += max_cakes
        v[i].S = 1
        v[i + 1].S = 1
        v[i + 2].S = 0

        if(v[i].S == 0) break;

        if(v[i + 1].S == 0){ ... }
        if(v[i + 2].S == 0){
            swap(v[i + 2], v(sz(v) - 1 - offset))
        }
    }
Lo que produce:
    v = { { 4, 1 }, { 3, 1 }, { 1, 1 }, { 2, 0 } }
Segunda iteración del while:
    while(V[i].S > 0){
        max_cakes = 1
        v[i].S = 0
        v[i + 1].S = 0
        v[i + 2].S = 0

        if(v[i].S == 0) break;
    }
Produce:
    v = { { 4, 0 }, { 3, 0 }, { 1, 0 }, { 2, 0 } }
Se ejecuta el break!
No es posible producir más cakes!
Respuesta = 2. 

Okey! Ahora tenemos WA en test case 15 :p

Input:
12
1 1 1 2 2 2 3 3 3 4 4 4 

m[1] = 3
m[2] = 3
m[3] = 3
m[4] = 3

v = { { 4, 3 }, { 3, 3 }, { 2, 3 }, { 1, 3 } }
c = 3
ans += 3

Y no se vuelve a ejecutar otro ciclo.
Pero la respuesta correcta es 4.
Ya que podemos formar:

{ 1, 2, 3 }, { 1, 2, 4 }, { 1, 3, 4 }, { 2, 3, 4 }

Estrategia Candidata 2:
Podemos tener una priority_queue, de modo que:

Input:
12
1 1 1 2 2 2 3 3 3 4 4 4 

En la pq: [3, 3, 3, 3]
Mientras el sz(pq) >= 3, intentamos formar
(a, b, c) con a != b != c:
    a = pq.top();
    pq.pop();
    b = pq.top();
    pq.pop();
    c = pq.top();
    pq.pop();

Esto dejaria la pq en [3]
Sin embargo, solo queremos consumir una vez a, b y c:
    if(a > 1) pq.push(a - 1);
    if(b > 1) pq.push(b - 1);
    if(c > 1) pq.push(c - 1);

Esto ultimo permite que siempre tengamos en el top la mejor opción posible. Y además, no tengamos que hacer swaps...