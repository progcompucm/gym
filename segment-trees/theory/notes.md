Segment Tree => Query Optimization + Updates

a = [2, 1, 4, 9, 3, 4, 2, 8]

Internamente, se construye un arbol binario, por el cual podemos ir 
descendiendo en función del rango consultado.

Para el arreglo "a", tenemos el nodo padre que contiene, en su totalidad, el rango [0, 7],
sin embargo, este se divide en dos partes, dos nodos hijos, uno para el rango [0, 3], otro para [4, 7].
Cada uno de estos nodos seran tambien arboles binarios. El nodo [0, 3], tendra [0, 1] y [2, 3], luego [0, 1] -> [0, 0] y [1, 1]
y [2, 3] -> [2, 2] y [3, 3]. Lo mismo sucede con [4, 7].

¿Cómo se construye?
A sabiendas que para:
    a = [2, 1, 4, 9, 3, 4, 2, 8]
Tenemos:

[0, 7] -> [0, 3], [4, 7]

[0, 3] -> [0, 1], [2, 3]
[0, 1] -> [0, 0], [1, 1]
[2, 3] -> [2, 2], [3, 3]

[4, 7] -> [4, 5], [6, 7]
[4, 5] -> [4, 4], [5, 5]
[6, 7] -> [6, 6], [7, 7]

Cada uno de estos nodos tendra asignado el valor minimo para el rango en particular que abarca en el arreglo, comenzando
a partir de las hojas.

Por lo tanto:
[0, 0] = 2         a[0] = 2
[1, 1] = 1         a[1] = 1
[2, 2] = 5         a[2] = 5
[3, 3] = 9         a[3] = 9
[4, 4] = 3         a[4] = 3
[5, 5] = 4         a[5] = 4
[6, 6] = 2         a[6] = 2
[7, 7] = 8         a[7] = 8

Los padres de estos nodos hojas, deben contener como valor, el minimo entre los valores de sus nodos hojas.
Por lo tanto:
[0, 1] = min([0, 0], [1,1]) = 1
[2, 3] = min([2, 2], [3, 3]) = 5
[4, 5] = min([4, 4], [5, 5]) = 3
[6, 7] = min([6, 6], [7, 7]) = 2

[0, 3] = min([0, 1], [2, 3]) = 1
[4, 7] = min([4, 5], [6, 7]) = 2

[0, 7] = min([0, 3], [4, 7]) = 1

Es valido afirmar que:
    "El arbol, para cada nodo, contiene una respuesta para un rango de segmento dado" 
Para lo anterior, en el caso de que deseamos encontrar el valor maximo dentro de un rango, en lugar de hallar los minimos, escogeriamos
los máximos a partir de los nodos hijos, hasta llegar al nodo root.

Si quisieramos crear un segment tree para suma de rangos, a partir de lo anterior,
se asume de que, ahora para un nodo padre, sumar los valores de sus nodos hijos. Y asi sucesivamente:

[0, 0] = 2         a[0] = 2
[1, 1] = 1         a[1] = 1
[2, 2] = 5         a[2] = 5
[3, 3] = 9         a[3] = 9
[4, 4] = 3         a[4] = 3
[5, 5] = 4         a[5] = 4
[6, 6] = 2         a[6] = 2
[7, 7] = 8         a[7] = 8

[0, 1] = [0, 0] + [1, 1] = 3
[2, 3] = [2, 2] + [3, 3] = 14
[4, 5] = [4, 4] + [5, 5] = 7
[6, 7] = [6, 6] + [7, 7] = 10

[0, 3] = [0, 1] + [2, 3] = 17
[4, 7] = [4, 5] + [6, 7] = 17

[0, 7] = [0, 3] + [4, 7] = 34

Ahora, ¿como hacemos queries?
Por ejemplo: [2, 5] (left = 2, right = 5).
Empezamos desde el nodo root, para explorar el arbol.
Para cada nodo, nos preguntamos, ¿lo necesitamos?

Por lo tanto:
Query = [2, 5]

[0, 7] = X
        - [0, 1] = Non-Overlapping Range (Nothing to do, ignore and stop traverse this subtree, return to top)
    - [0, 3] = X (Partial Overlap => Buscamos la respuesta de uno de sus segmentos)
        - [2, 3] = Complete Overlapping Range! (+14), return to top

Por lo tanto, de recorrer el lado izquierdo del arbol obtenemos:
    0 + 14 = 14 (left + right).

Ahora navegando el lado derecho:
[0, 7] = X
        - [6, 7] = Non-Overlapping Range (Nothing to do)
    - [4, 7] - Partial Overlap! 
        - [4, 5] = Complete Overlapping Range! (+7) return to top

Por lo tanto, ahora en el root node, sumando left + right => 14 + 7 = 21. 

3 steps for recursion:
    - No overlap => Dont go in subtreee return 0
    - Complete overlap => return the value 
    - Partial overlap => Go in left subtree and right subtree and return left + right 

Query = [2, 2]
[0, 7] -> [0, 3] (Partial Overlap) -> [2, 3] (Partial Overlap) -> [2, 2] (Complete Overlap)

¿Cómo hago un update?
Si quisieramos actualizar el indice 2, con un valor de 10, nos ubicamos en la hoja (2, 2), actualizamos, y luego, 
por consecuencia debemos actualizar todos sus ancestros (DFS):
[2, 2] -> [2, 3] -> [0, 3] -> [0, 7]

[2, 2] = 10
[2, 3] = [2, 2] + [3, 3] = 19
[0, 3] = [0, 1] + [2, 3] = 22
[0, 7] = [0, 3] + [4, 7] = 39

La complejidad de esto esta en función de la altura del segment tree, pues sera la cantidad de operaciones a realizar.