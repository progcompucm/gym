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
    for(ll i = 0; i < n - 2; i++)

Por lo tanto:
A sabiendas de n, y el tamaño de los bizcochos:
    unordered_map<ll, ll> m;
Creamos un mapa, donde la key = height y el valor = freq.
Unordered ya que, luego de guardar todo, ordenaremos segun freq.
