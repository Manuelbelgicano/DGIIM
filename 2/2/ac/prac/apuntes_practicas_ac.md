# AC. Prácticas

#### Ejecución en el `atcgrid`

- Comandos: `echo '<command>' | qsub -q ac`

- Scripts: `qsub script.sh -q ac`

- Consulta de trabajos: `qstat`

- Compilación: `gcc -O2 -fopenmp -o <executable_name> <file>`

#### Directivas

1. **Parallel**
	- Especifica qué calculos se ejecutan en paralelo.
	- Cada thread ejecuta el código de la región `parallel`.
	- No reparte trabajo entre threads.
	- Tiene una barrera implícita al final.
	- Se pueden anidar.
2. **For**
	- Distribuye las iteraciones de un bucle entre las iteraciones.
	- No puede ser un bucle do-while (porque son una mierda, todos lo sabemos).
	- Tiene una barrera implícita al final.
3. **Sections**
	- Distribuye de forma manual las tareas a cada thread.
	- Cada sección a ejecutar por un thread distinto tiene que estar encapsulado por el encabezado `#pragma omp section`
  - Tiene una barrera implícita al final.
4. **Single**
	- El código del interior lo realiza solamente un thread, pero no podemos elegir  el thread que lo ejecuta.
	- Tiene una barrera implícita al final.
5. **Master**
	- Alternativa a `single` en la que el thread que lo ejecuta es el thread 0.
6. **Barrier**
	- Crea una barrera en ese punto
7. **Critical**
	- Permite que varios threads accedan a una variable compartida a la vez sin que eso produzca problemas.
8. **Atomic**
	- Variante de `critical` más eficiente.
	- Solamente válida para operaciones de los tipos: `+`,`*`,`-`,`/`,`&`,`^`,`|`,`<<` y `>>`.

#### Cláusulas

Las cláusulas son sólo válidas para las siguientes directivas: `parallel`, `for`, `sections` y `single`.

1. **Shared**
	- Sintaxis: `shared(<variables>)`
	- Indica que el conjunto de variables son compartidas por todos los threads.
2. **Private**
	- Sintaxis: `private(<variables>)`
	- Indica que el conjunto de variables son privadas a cada thread.
	- El valor de entrada y de salida son *indefinidos* aunque la variable sea declarada fuera de la zona paralela.
	- Los índices de los bucles son privados de forma predeterminada.
3. **Lastprivate**
	- Sintaxis: `lastprivate(<variables>)`
	- Alternativa a `private` en la que los valores de salida del conjunto de variables no son indefinidos, sino que tienen el último valor asignado en la zona paralela.
4. **Firstprivate**
	- Sintaxis: `firstprivate(<variables>)`
	- Alternativa a `private` en la que los valores de  entrada del conjunto de variables no son indefinidos, sino que tienen el último valor asignado antes de la zona paralela.
5. **Default**
	- Sintaxis: `default(none|shared)`
	- Con `none`, se deben especificar si las variables usadas son compartidas o privadas (salvo índices de bucles).
	- Con `shared` hace compartidas  todas las variables.
	- Solamente puede haber una claúsula `default`.
	- Se puede combinar con las claúsulas anteriores.
6. **Reduction**
	- Sintaxis: `reduction(<operador>:<variables>)`
	- Los operadores válidos son: `+`, `-`, `*`, `&`, `|`, `^`, `&&` y `||`.
	- Tiene un uso parecido a `critical`, por lo que realiza la operación en las variables con comunicación colectiva todos a uno.
	- Ejemplo con 4 threads:
	```c
	#pragma omp parallel for reduction(+:suma)
	for (int i=0;i<n;i++)	suma+=a[i];
	```
	La variable $\mathrm{suma}$ tiene el valor: $\mathrm{suma}=\mathrm{suma}_0+\mathrm{suma}_1+\mathrm{suma}_2+\mathrm{suma}_3$, donde $\mathrm{suma}_i$ es la suma parcial del thread $i$.
7. **Copyprivate**
	- Sintaxis: `copyprivate(<variables>)`
	- Solamente se puede usar con la directiva `single`.
	- Copia el valor del conjunto de variables a las variables privadas del mismo nombre del resto de threads.

#### Variables de control

1. **dyn-var**
	- Afecta a `parallel`.
	- Valor inciales: `true`/`false`.
	- Permite el ajuste dinámico del número de threads.
2. **nthreads-var**
	- Afecta a `parallel`.
	- Valor incial: número.
	- Determina el número de threads en la siguiente región paralela.
3. **nest-var**
	- Afecta a `parallel`.
	- Valor inicial: `true`/`false`.
	- Permite el paralelismo anidado.
4. **run-shed-var**
	- Afecta a `for`.
	- Valor inicial: `(kind[chunk])`.
	- Determina la planificación de bucles para `runtime`.
5. **def-sched-var**
	- Afecta a `for`.
	- Valor inicial: `(kind[chunk])`.
	- Determina la planificación de bucles por defecto.

#### Variables de entorno

Estas variables se pueden modificar desde el shell.

1. **OMP_DYNAMIC**: Se corresponde con `dyn-var`.
2. **OMP_NUM_THREADS**: Se corresponde con `nthreads-var`.
3. **OMP_NESTED**: Se corresponde con `nest-var`.
4. **OMP_SCHEDULE**: Se corresponde con `run-sched-var`.

#### Funciones del entorno de ejecución

Permiten consultar y modificar los valores de las variables de control en el entorno de ejecución.

1. **dyn-var**
	- Consulta: `omp_get_dynamic()`
	- Modificación: `omp_set_dynamic()`
2. **nthreads-var**
	- Consulta: `omp_get_max_threads()`
	- Modificación: `omp_set_max_threads()`
3. **nest-var**
	- Consulta: `omp_get_nested()`
	- Modificación: `omp_set_nested()`
4. **Identificador de thread**: `omp_get_thread_num()`
5. **Número de threads en uso**: `omp_get_num_threads()`
6. **Número de procesadores disponibles**: `omp_get_num_procs()`
7. **Región paralela**: `omp_in_parallel()`. Devuelve `true` si se llama desde una región paralela.

#### Claúsulas de interacción con el entorno

1. **num_threads**
	- Sintaxis: `num_threads(<numero>)`
	- Fija el número de threads para esa región paralela.
2. **if**
	- Ejecuta la región paralela si se cumple la condición.
	- Solamente válida en `parallel`.
	- Orden de preferencia para fijar el número de threads:
		1. `if`
		2. `num_threads`
		3. `omp_set_num_threads()`
		4. `OMP_NUM_THREADS`
		5. Valor por defecto.
3. **Schedule**
	- Sintaxis: `schedule(kind[,chunk])`
	- Solamente válido para bucles.
	- Valores de `kind`:
		- `static`: Se asignan las iteraciones en round-robin de tamaño `chunk`. Es el valor por defecto.
		- `dynamic`: Se distribuyen en tiempo de ejecución las iteraciones en bloques de tamaño `chunk` de forma dinámica entre las threads (los threads más rápidos ejecutan más iteraciones).
		- `guided`: Se distribuyen las iteraciones en bloques de tamaño $\max\{\frac{\mathrm{iteraciones\_restantes}}{\mathrm{número\_threads}},\mathrm{chunk}\}$ entre las threads en tiempo de ejecución.
		- `runtime`: Se fija el tipo de distribución en tiempo de ejecución con el valor de `run-shed-var`.
	- El valor de `chunk` es 1 en caso de no ser especificado.

#### Optimización

- La división es una operación muy costosa que hay que evitar o reducir su número.
- Es más rápido en ocasiones realizar desplazamientos y sumas en lugar de multiplicaciones.
- El desenrollado de bucles disminuye el número de saltos.
- Los punteros son poco deseables, puesto que son ambiguos para el compilador.
- El acceso a datos que ocupan varias líneas de caché es costoso (acceder a las matrices por filas en lugar de columnas es mejor, ya que se almacenan por filas).
- Se pueden evitar saltos con movimientos condicionales.
- Si una posibilidad de un switch es alta, es mejor reorganizar el switch sacando esa posibilidad fuera en otro condicional.
- Las instrucciones `cmov`, `fcmov` y `set` pueden ayudar a eliminar saltos.