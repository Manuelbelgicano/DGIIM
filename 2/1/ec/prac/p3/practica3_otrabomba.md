*Manuel Gachs Ballegeer. 2º DGIIM UGR*

## Desactivando la boma de Daniel Gonzálvez

### 1. Primer paso: Entrar en `gdb`

Primero entramos en el depurador y ejecutamos la orden `layout asm`, para mostrar el código en ensamblador. Después le añadimos un breakpoint con `break main`, y ejecutamos el programa con `run`. Vamos avanzando por el programa usando `nexti`, y nos encontramos con la pregunta: *¿Cómo está usted hoy?*.

### 2. Segundo paso: Primera clave

Si simplemente ejecutamos el programa, podemos observar que la respuesta que proporcionamos a la pregunta carece de importancia, puesto que se realiza la pregunta un total de 10 veces antes de explotar.

Volvemos a ejecutar el programa desde el depurador, y, tras la pregunta, buscamos la llamada a `strcmp` y escribimos `stepi`. Tras esto, vamos ejecutando `nexti` hasta llegar a estas dos instrucciones sospechosas:

```bash
0xf7f25240 <__strcmp_sse4_2>    mov    0x4(%esp),%edx
0xf7f25244 <__strcmp_sse4_2+4>  mov    0x8(%esp),%eax 
```
Como en C el ensamblador llama a los parámetros en orden inverso, por lo que veremos el contenido de `%eax` ejecutando `x/cb $eax` y sus siguientes posiciones de memoria, llegando al siguiente resultado:

```bash
(gdb) x/cb $eax
0xffffd83a:     98 'b'
0xffffd83b:     105 'i'
0xffffd83c:     101 'e'
0xffffd83d:     110 'n'
0xffffd83e:     10 '\n'
```

**Hemos encontrado la clave: "bien".** Sin embargo, si al ejecutarlo ponemos bien en alguna de las tres primeras preguntas, nos explota la bomba; en general explota salvo que la pongamos en la cuarta pregunta.

### 3. Tercer paso: Segunda clave

Tras ejecutar el programa y salir de la primera pregunta, el programa nos pide introducir una clave numérica. Buscamos en las instrucciones posteriores una comparación, y encontramos `cmp`, que compara el valor con el que hemos respondido (en mi caso usé 27), con el valor 4. Con
Tras ejecutar varias veces el programa me di cuenta de que el valor era siempre 4.




