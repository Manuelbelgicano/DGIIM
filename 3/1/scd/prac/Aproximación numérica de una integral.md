## Aproximación numérica de una integral

Para resolver el problema de la aproximación numérica de la integral $$\int_0^1\frac{4}{1+x^2}dx$$ a $$\pi$$, existían dos estrategias de reparto para la solución concurrente. En el caso de mi solución, he utilizado la estrategia de **asignación por bloques contiguos**, esto es, asignando a cada hebra la misma porción del total de la muestra.

#### Resolución del problema

Para evitar la repetición de valores y que cada hebra calculara su porción proporcional, existen dos variables definidas de forma que el conjunto de valores que calcula cada hebra sea (`valor_min`, `valor_max`), además de una variable `tam` que expresa el tamaño de las porciones de la muestra que debe calcular cada muestra.

- `valor_min` se calcula de la siguiente manera:

  $$0+(($$nº de la hebra$$)-1)\;\cdot\;($$`tam`)

  Este valor es el siguiente valor al último que tomó la hebra anterior, por lo que en el caso de la hebra primera (la que tiene como número el 1) el primer valor que toma es 0.

- `valor_max` se calcula de la siguiente manera:

  (nº de la hebra)$$\;\cdot\;$$(`tam`)

El programa, a partir de un número $n$ de hebras, separa el tamaño de la muestra en $n$ porciones, que ejecutan un código prácticamente idéntico al secuencial para su porción correspondiente. Estos resultados se guardan en un array de `future` usando `async`. Tras esto, se suman esos resultados parciales, llegando a la solución final.

#### Resultados

![Captura](/home/diagmatrix/git/DGIIM/3/1/scd/practicas/captura_ejercicio_propuesto.jpg)

Como puede verse en esta captura, la solución usando el programa concurrente no solamente obtiene mejores tiempos, sino que a su vez obtiene mejores resultados. Esto hace pensar que es sustancialmente mejor el uso de la programación concurrente.