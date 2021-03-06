## Examen práctica 1

Modificar el programa solución del problema de los fumadores de la práctica 1 tal y como se muestra a continuación, guardando el resultado en un archivo `estancos2.cpp`:

**a)** Se pretende que la nueva solución permita el trabajo de dos estanqueros. En lugar de tener una hebra estanquero, se tendrán dos hebras estanquero: `estanquero[0]` y `estanquero[1]`.

**b)** Ambos estanqueros interactuarán con los tres fumadores, de la misma forma que en la práctica 1 pero lo harán en diferentes periodos, siguiendo las órdenes de un gestor central, que se implementará como una hebra adicional e indicará qué estanquero puede actuar en cada periodo.

**c)** El gestor central está continuamente realizando las siguientes tareas:
​	1. Decide aleatoriamente qué estanquero servirá los próximos 5 ingredientes.
​	2. Avisa al estanquero seleccionado.
​	3. Espera a que termine su servicio.

**d)** Los estanqueros funcionan en ciclos de 5 ingredientes. Esperan a que el gestor central le dé permiso y generan 5 ingredientes para los fumadores (siguiendo la misma sincronización que el problema original).  Cuando se retira el quinto ingrediente, el estanquero avisa al gestor central de ello y vuelve a quedar en espera de que el gestor central le dé permiso para iniciar un nuevo ciclo.

**e)** Ambos estanqueros comparten el mismo estanco y mostrador, pero lo usan en distintos periodos siguiendo  las caprichosas órdenes del gestor central.

**f)** Se requiere que las dos hebras estanquero se describan con la misma función parametrizada en base a un índice entero (al igual que ocurre con las hebras fumadoras) y que la solución utilice arrays de hebras (que pueden ser fumadoras o estanqueros) y uno o varios arrays de semáforos.