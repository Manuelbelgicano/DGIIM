# Modelos Matemáticos: Tema 1

- **Ecuación en diferencias lineal**

  $$a_k(n)x_{n+k}+...+a_1(n)x_{n+1}+a_0(n)x_n=b(n)$$

  - *Orden* $k$
  - *Homogénea* si $b(n)=0$, $n\geq 0$

- **Ecuación en diferencias de primer orden lineal con coeficientes constantes**

  $$x_{n+1}=\alpha x_n+\beta$$ (1)

  - *Progresión aritmética:* $x_{n+1}=x_n+\beta \implies x_n=x_0+n\beta$
  - *Progresión geométrica:* $x_{n+1}=\alpha x_n \implies x_n=x_0\alpha^n$

- **Proposiciones**

  - Si $\alpha\neq 1$, la ecuación (1) tiene una única solución constante $x_*=\displaystyle\frac{\beta}{1-\alpha}$
  - Si $\alpha\neq 1$, la sucesión $\{x_n\}_{n\in\mathbb{N}}$ es solución de la ecuación (1) si y solo si la sucesión $\{z_n\}_{n\in\mathbb{N}}$, definida por $z_n=x_n-x_*$ es solución de la ecuación $z_{n+1}=\alpha z_n$
  - Si $\alpha\neq 1$, la ecuación (1) tiene tantas soluciones como valores posibles tenga la condición inicial $x_n=x_*+(x_0-x_*)\alpha^n\quad n=0,1,2,...$

- **Fórmula de De Moivre**

  $$\alpha=a+\imath b\in\mathbb{C},\;\alpha^n=r^n(\cos(n\theta)+\imath\sin(n\theta))$$

  - *Módulo* $r=\sqrt{a^2+b^2}$
  - *Argumento* $\theta$

- **Comportamiento asintótico de las soluciones**

  Las soluciones $\{x_n\}_{n\geq0}$ de la ecuación (1) verifican:

  - Si $|\alpha|<1$, entonces $\{x_n\}\to x_*$
  - Si $|\alpha|>1$, entonces $\{x_n\}$ diverge
  - Si $|\alpha|=1,\,\alpha\neq 1$, entonces $\{x_n\}$ está en la circunferencia de centro $x_*$ y radio $|x_0-x_*|$

- **Modelo de la telaraña**

  - *Oferta* $O(p)=a+bp$
  - *Demanda* $D(p)=c-dp,\;D(p_n)=O(p_{n-1})$
  - *Solución constante* $p_*=\displaystyle\frac{c-a}{b+d}$
  - *Solución general* $p_n=p_*+(-1)^n\Big(\displaystyle\frac bd\Big)^nK$

- **Modelo de Malthus**

  - *Número de individuos en un periodo*  $P_n$
  - *Tasa de natalidad/fertilidad* $\alpha_N$
    - $\alpha_NP_n=$ *Número de nacimientos en el periodo $n$*
  - *Tasa de mortalidad* $\alpha_M$
    - $\alpha_MP_n=$ *Número de muertes en el periodo $n$*
  - *Número de individuos en el siguiente periodo* $P_{n+1}=(1+\alpha_N-\alpha_M)P_n$
    - *Razón de crecimiento* $R=1+\alpha_N-\alpha_M=\displaystyle\frac{P_{n+1}}{P_n}$
    - *Tasa de crecimiento* $\alpha=\alpha_N-\alpha_M=\displaystyle\frac{P_{n+1}-P_n}{P_n}$

- **El modelo de Verhulst**

  - *Máximo de individuos* $M$

  - *Modelo (tasa proporcional a "espacios libres")* 

    $$\displaystyle\frac{P_{n+1}-P_n}{P_n}=k(M-P_n)\implies P_{n+1}=(1+kM)P_n-kP_n^2=(1+kM)P_n(1-\displaystyle\frac{k}{1+kM}P_n)$$

  - *Ecuación final (ecuación logística discreta)* $x_{n+1}=\mu x_n(1-x_n)$

    - $\mu=1+kM$
    - $x_n=\displaystyle\frac{k}{1+kM}P_n$

- **Sistema dinámico discreto (SDD)**

  Supogamos que $I\subset \mathbb{R}$ es un intervalo que contiene al menos dospuntos y $f:I\to I$ es una función continua. Entonces al par $\{I,f\}$ se ledenomina un sistema din ́amico discreto (**SDD**), de primer orden, autónomo y en forma normal. A la función $f$ se le suele llamar función de evolución.

  - *Lineal* si $f$ es lineal
  - *Afín* si $f$ es afín
  - *No lineal* en cualquier otro caso
  - *Sucesivas iteradas* $f^n=f\;\circ\;f\;\circ\;...\;\circ\;f$

- **Órbita/Trayectoria**

  Sea un SDD $\{I,f\}$ y un $x_0\in I$, se denomina órbita o trayectoria asociada al valor inicial $x_0$ a la sucesión definida por $\{x_0,x_1,x_2,...,x_n,...\}=\{x_0,f(x_0),f^2(x_0),...,f^n(x_0),...\}$, y se denota por $\gamma(I,f,x_0)$

  - *Retrato de fase* Conjunto de todas las órbitas asociadas al SDD y a todos los puntos $x_0$

- **Punto de equilibrio**

  Se dice que un $\alpha\in\mathbb{R}$ es un punto de equilibrio del SDD $\{I,f\}$ si $\alpha=f(\alpha)$. Constituye una **solución constante** de la ecuación en diferencias

  - *Órbita estacionaria* La órbita $\gamma(I,f,x_0)=\{\alpha,\alpha,\alpha,...\}$
    - *Órbita eventualmente estacionaria* Si dado $x_0\in I$, $\exists k$ tal que $f^k(x_0)=\alpha=f(\alpha)$. La órbita sería por tanto $\gamma(I,f,x_0) =\{x_0,f(x_0),f2(x_0), ...,f^{k−1}(x_0),\alpha,\alpha,\alpha, ...\}$
  - Los puntos de equlibrio se encuentran en la intersección de $f$ con la bisectriz del primer cuadrante dentro del subconjunto $I\times I$
  - Si $\alpha$ es un un punto de equilibrio del SDD $\{I,f\}$ también lo es del SDD $\{I,f^n\}$

- **Teoremas**

  - Todo SDD $\{I,f\}$ con $I$ cerrado y acotado posee un punto de equilibrio
  - Sea un SDD $\{I,f\}$ con $I$ cerrado y $f$ contractiva (existe $0<k<1$ tal que $|f(x)-f(y)|\leq k|x-y|$)  entonces existe un único punto de equilibrio
  - Sea el SDD $\{I,f\}$ con $I$ cerrado y acotado, $f\in\mathcal{C}^1(I)$ tal que $|f′(x)|<1,\,\forall x\in I$. Entonces existe un único punto de equilibrio
  - Sea el SDD $\{I,f\}$ con $I$ cerrado. Sea $f\in\mathcal{C}^1(I)$ y supongamos $0<k<1$ verificando$|f′(x)|\leq k<1,\,\forall x\in I$. Entonces existe un único punto de equilibri

- **Estabilidad de los puntos de equilibrio**

  Un punto de equilibrio $\alpha$ del SDD $\{I,f\}$ se dice que es

  - *Estable* si para cualquier $\varepsilon>0,\,\exists\delta>0$ tal que si $|x_n-\alpha|<\delta$ y $x_n=f^n(x_0)$, entonces $|x_n-\alpha|<\varepsilon$
  - *Asintóticamente estable* si es estable y además $\displaystyle\lim_{n\to\infty} x_n=\alpha$
  - *Inestable* si no es estable

- **Atractores**

  Se dice que un punto de equilibrio $\alpha$ del SDD $\{I,f\}$ es

  - *Atractor global* si para cualquier $x_0\in I$ y $x_n=f^n(x_0)$, se verifica $\displaystyle\lim_{n\to\infty} x_n=\alpha$
  - *Atractor local/Localmente asintóticamente estable* si si existe $\eta >0$ tal que para cualquier $x_0\in I\cap(\alpha-\eta,\alpha+\eta)$ y $x_n=f^n(x_0)$, se verifica $\displaystyle\lim_{n\to\infty} x_n=\alpha$

- **Estabilidad asintótica local**

  Si $\alpha$ es un punto de equilibrio del SDD $\{I,f\}$ y $f\in\mathcal{C}^1(I)$, entonces:

  - Si $|f'(\alpha)|<1$, entonces $\alpha$ es *localmente asintóticamente estable*
  - Si $|f'(\alpha)|>1$, entonces $\alpha$  es *inestable*

  Sea $\alpha$ un punto de equilibrio del SDD $\{I,f\},\, f\in\mathcal{C}^3(I)$ y $f'(\alpha) =1$. Entonces

  - Si $f''(\alpha)\neq 0$, entonces es *inestable*
  - Si $f''(\alpha)=0$ y $f'''(\alpha)<0$, entonces $\alpha$ es *localmente asintóticamente estable*
  - Si $f''(\alpha)=0$ y $f'''(\alpha)>0$, entonces $\alpha$ es *inestable*

- 