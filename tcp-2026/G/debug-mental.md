Tenemos:
    n: Cantidad de bloques en fila.
       Cada i-esimo bloque esconde un valor a[i].
       Los valores estan ordenados crecientemente.

    x: Valor a encontrar.

    Solo se puede avanzar hacia la derecha.
    
Cada consulta:
    1) Debe ser estrictamente mayor que la de la consulta anterior.
    2) Podemos reiniciar una unica vez y volver a cualquier posición. 

Nos piden:
    Dado un valor "x" que aparece en el conjunto de bloques, encontrar su posición usando como maximo 145 consultas.

Iteracción:
    ? i: consulta posición i (i <= i <= n).
         juez responde con a[i].
    
    R para reiniciar.
    ! p: informar que "x" esta en la posición p.

Estrategia Candidata:
Como tenemos solo 145 consultas, si n <= 145 entonces
podemos consultar por cada posición en el rango 1 ... 145 hasta
coincidir con x == p. 

Caso contrario, a sabiendas de que la lista de valores
de cada bloque esta ordenada de forma creciente, podemos 
ir moviendonos en pasos de tal forma que podamos asegurarnos de que
p este en un rango [start, end] y consultar cada posición de ese rango.

Para hacer lo anterior y garantizar que p este en ese rango, implica que debemos consultar hasta que un bloque a[i] sea mayor a nuestro "x".

1 <= n <= 5000, es decir, podemos tener hasta 5,000 bloques.
¿Qué cantidad de bloques deberiamos ir saltando para asegurar que
nos queden (end - start) consultas disponibles para hallar p cuando a[end] > x? 
    - Con un step_size de 50, necesitamos 100 consultas en el peor de los casos. 50 * 100 => 5,000. Tenemos 45 consultas disponibles, por lo tanto end - 45. 

Tendremos:
    step_size = 50
    step = 0
Luego:
    rep(i, 1, n + 1){

    }
Dentro de cada iteracion:
    step += step_size
Consultamos por la posición actual:
    p("? ", step)
Leemos la respuesta:
    ll v; 
    cin >> v;
Si v >= x, entonces:
    p("R\n")
    rep(i, max(1, step - step_size), step + 1){
        p("? ", i)
        cin >> v;
        if(v == x){
            p("! ", i);
            break;
        }
    }
