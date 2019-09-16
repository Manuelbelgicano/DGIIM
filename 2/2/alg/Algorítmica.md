## Algorítmica

### Tema 1.

La **Ciencia de la Computación** es el estudio de los algoritmos, incluyendo sus propiedades, su hardware, sus aspectos lingüísticos y sus aplicaciones.

Un **algoritmo** es una secuencia finita y ordenada de pasos, exentos de ambigüedad, tal que al llevarse a cabo con fidelidad, dará como resultado que se realice la tarea para la que se ha diseñado (se obtenga la solución del problema planteado) con recursos limitados y en tiempo finito.
También puede definirse de la siguiente manera:
Un método computacional es una cuaterna $(Q,I,\Omega,f)$ en la que $Q$ es un conjunto, $I,\Omega\subset Q$ y $f:Q\to Q$ tal que $f(q) = q$, $\forall q\in\Omega$. $Q$ es el conjunto de los estados del cálculo, $I$ el input, $\Omega$ el output y $f$ la regla de cálculo que se esté aplicando. Cada input $x\in I$ define una sucesión computacional ${x_n}$ como sigue: $x_0=x$ y $x_{k+1}=f(x_k)$ cuando $k\geq 0$. Se dice que la sucesión computacional termina en $k$ etapas si k es el menor entero para el que $x_k$ está en $\Omega$. Un algoritmo es un método computacional que termina en un número finito de etapas.

El **tamaño de un caso** $x$ es el número de bits necesarios para representar el caso en un computador usando un código precisamente definido y razonablemente compacto.

El **peor caso posible** es el que da el máximo tiempo para resolver el problema. El **mejor caso posible** es aquel que da el mínimo tiempo de resolución del problema. El **caso promedio** es la media de los tiempos de todos los casos posibles del mismo tamaño.

#### Eficiencia teórica

##### Notación $O$

Sean $f,g:\mathbb{N}\to\mathbb{R}^+$. Se dice que $f$ es de orden $g$, denotado por $O(g(n))$, si existen dos constantes positivas $k$ y $C$ tales que:
$\forall n\geq k,\;f(n)\leq C\cdot g(n)$

##### Notación $\Omega$

Sean $f,g:\mathbb{N}\to\mathbb{R}^+$. Se dice que $f$ es $\Omega(g(n))$, si existen dos constantes positivas $k$ y $C$ tales que:
$\forall n\geq k,\;f(n)\geq C\cdot g(n)$

##### Notación $\Theta$

Sean $f,g:\mathbb{N}\to\mathbb{R}^+$. Se dice que $f$ es $\Theta(g(n))$ si  $f$ es $O(g(n))$ y $f$ es $\Omega(g(n))$.

#### Recurrencias

Sea $a_0t_n+a_1t_{n-1}+\dots+a_kt_{n-k}=b_1^np_1(n)+b_2^np_2(n)+\dots+b_m^np_m(n)$
- *Ecuación característica*: $(a_0x^k+a_1x^{k-1}+\dots+a_k)(x-b_1)^{d_1+1}+...\cdot(x-b_m)^{d_m+1}=0$, donde $d_i$ es el grado de $p_i(n)$.
- *Cambio de variable*: Si la recurrencia es del tipo $T(n)=T(n/2)+p(n)$ se puede realizar el cambio $n=2^k,\;T(2^k)=t_k$.

### Tema 2

El diseño de algoritmos **Divide y Vencerás (DV)** consiste en:
1. Dividir un problema $P$ en varios subproblemas $P_i$.
2. Resolver los subproblemas.
3. Combinar las soluciones de los subproblemas para obtener la solución del problema inicial.

Este enfoque, sobre todo cuando se utiliza recursivamente, a menudo proporciona soluciones eficientes para problemas en los que los subproblemas son versiones reducidas y resolubles del problema original.
Algunas consideraciones importantes a la hora de determinar si se puede utilizar el método DV:
- Los $P_i$ deben tener la misma naturaleza entre ellos y con $P$, y deben ser más sencillos de resolver que $P$.
- Debe tener sentido combinar las soluciones de los subproblemas para llegar a la solución final.
- Al tratarse de funciones recursivas, un valor muy importante es el umbral, puesto que si el tamaño es menor que ese umbral no subdividirá el problema.

#### Métodos de búsqueda y ordenación

##### Búsqueda binaria


