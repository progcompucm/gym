Tenemos:
    - N: Cantidad de cleaners disponibles.
    - S: Cantidad de calles a ser limpiadas.
    - K: Horas en las que el trabajo debe ser completado.

Cada cleaner identifcado por 1 ... N.
Luego, las siguientes N lineas describen al cleaner i-esimo con 3 enteros:
    - H[i]: cleaner[i] puede limpiar cualquier calle en H[i] horas.
    - L[i], U[i]: cleaner[i] acepta un pago entre [L[i], U[i]].

Nos piden:
    Determinar el pago minimo que permita limpiar todas las calles cumpliendo las reglas. Si no es posible, mostrar "*".

¿Qué reglas?
    1) El tiempo total que tardan los limpiadores no debe superar K.
    2) Un cleaner => Una sola calle.
    3) El pago por calle debe ser un número racional entre L[i] y U[i].
    4) El pago por cada hora de trabajo debe ser el mismo para todos los cleaners. 

Considerando el ejemplo 1:

Input:
2 15 10
1 4 10
2 2 8

Output:
80 1

Aqui:
N = 2, S = 15, K = 10.

        H[i] U[i] L[i]
c = { { 1,   4,   10 }, { 2, 2, 8 } }
            c[1]            c[2]

Razonando el output:
La salida es 80 1. 
Eso quiere decir que: 
    El minimo pago posible para limpiar todas las calles es de $80.

¿Por qué?
Tenemos a lo más, 10 horas (K = 10).
Y tenemos 15 calles por limpiar (S = 10).
Solo contamos con 2 limpiadores (N = 2).

Nos dicen que, cada trabajador tarda s[i] * H[i] para limpiar las calles que le fueron asignadas. Y además, nos dicen que:
    s[i] * H[i] <= K

Con lo anterior, podemos determinar la cantidad de trabajadores que necesitamos para completar el trabajo. Como no conocemos s[i], podemos despejar de tal forma que obtenemos:
    s[i] <= K / H[i]
Y, considerando que vamos a colocar cada trabajador en su máxima capacidad:
    s[i] = K / H[i]

Por lo tanto:
s[1] = 10 / 1 = 10
s[2] = 10 / 2 = 5
Al sumarlos, s[1] + s[2] = 15 <= K. 
Por consecuencia, para cumplir con la regla, ambos trabajadores deben ser contratados.

Luego, como debemos contratar a ambos, nos piden que el pago por hora de trabajo:
    p[i] / H[i]
debe ser igual para todos los trabajadores. Dado lo anterior, se asume que sera un valor constante, por lo que podemos darle un nombre:
    pmin = p[i] / H[i]
Luego, despejando p[i]:
    pmin * H[i] = p[i]
La regla dice:
    "p[i] must be a rational number between L[i] and U[i] (L[i] <= p[i] <= U[i])"
Por lo tanto:
    L[i] <= pmin * H[i] <= U[i]
Para el primer trabajador:
    4 <= pmin * 1 <= 10    / 1
    4 <= pmin <= 10
Preferimos pmin = L[i] = 4, ya que intentamos minimizar el pago, por lo tanto:
    p[1] = 4
Luego, para el segundo trabajador:
    2 <= pmin * 2 <= 8    / 2
    1 <= pmin <= 4
Aqui, no podemos escoger p[2] = L[2] = 1, ya que el pago para cada trabajador
debe ser constante (pmin), por consecuencia debe cumplir con las condiciones L[i] <= p[i] <= U[i] de cada trabajador. Si podemos escoger p[2] = U[2] = 4, ya que 4 esta contenido en el rango del pago que acepta el trabajador 1.

Por lo tanto, el valor de pmin que satisface la condición para ambos trabajadores es:
    pmin = 4.
Luego, para hallar p[i], a sabiendas de:
    pmin * H[i] = p[i]
Tenemos:
p[1] = 4 * 1 = 4
p[2] = 4 * 2 = 8

Ahora, a sabiendas del pago total que recibira cada trabajador, nos dicen además:
    "Hired cleaner i will receive s[i] * p[i] as payment, being the total payment sum (s[i] * p[i])".

Por lo tanto.
total_payment = (s[1] * p[1]) + (s[2] * p[2])
total_payment = (10 * 4) + (5 * 8) = 40 + 40 = 80.

Y como debemos expresarlo en una fracción irreducible, colocamos 1 en el denominador.
80 1