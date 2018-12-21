*Manuel Gachs Ballegeer. 2ºDGIIM UGR* 

# EC: Cómo desactivar `estonoesunabomba.c`

### 1. Primer paso: Entrar en `gdb`

Ejecutamos el siguiente comando en la terminal:

```bash
gdb estonoesunabomba
```
Una vez dentro del depurador, lo primero que hacemos es visualizar el código en ensamblador. Para ello ejecutamos el comando `layout asm`. Una vez realizado esto, le ponemos una parada para poder tener control sobre la ejecución del programa. Para ello escribimos `break main`.

Tras esto, vamos a buscar comparaciones, tanto las de lenguaje ensamblador (como `cmpl`) como funciones externas que sabemos que son de comparación (por ejemplo `strcmp`). Estas sentencias las marcamos como posibles pistas para encontrar las contraseñas, puesto que sabemos que en algún momento el programa comparará nuestra respuesta con alguna dada.

Ejecutamos el programa con `run`. Tras esto, una vez llegados al `breakpoint`, ejecutamos `nexti`, y esperamos a que nos muestre el mensaje *¿Quieres desactivar la bomba?*.

### 2. Segundo paso: Primera clave

Una vez llegados a ese mensaje, seguimos ejecutando `nexti` hasta llegar a una instrucción de llamada a `strcmp`. Una vez situados en esta, ejecutamos `stepi`. Tras esto, vamos ejecutando `nexti` hasta justo sobrepasar estas instrucciones, puesto que parecen sospechosas:

```bash
0xf7f25240 <__strcmp_sse4_2>    mov    0x4(%esp),%edx
0xf7f25244 <__strcmp_sse4_2+4>  mov    0x8(%esp),%eax
```

Tras estas instrucciones, vamos a ver que contienen los registros `%edx` y `%eax`. Como sabemos que en C el ensamblador pasa los parámetros de las funciones en orden inverso en la pila, y suponemos que la respuesta es el segundo parámetro de la función `strcmp`, entonces vamos a ver que contiene el registro `%eax`. Para ello utilizamos el siguiente comando: `x/cb $eax`. Si lo hacemos varias veces, obtenemos el siguiente resultado:

```bash
(gdb) x/cb $eax
0xffffd7d4:     110 'n'
0xffffd7d5:     111 'o'
0xffffd7d6:     10 '\n'
```

**Hemos encontrado la clave: "no"**. Si seguimos ejecutando el programa acaba con la explosión, pero ya conocemos una de las claves.

### 3. Tercer paso: Segunda clave

Volvemos a ejecutar el programa, dando la respuesta adecuada a la primera pregunta. Llegamos a una segunda pregunta: *¿Quieres que explote?*. Buscamos la siguiente llamada a `strcmp` y una vez llegados ahí ejecutamos `stepi` dos veces seguidas. Volvemos a encontrarnos dos instrucciones sospechosas:

```bash
0xf7f25240 <__strcmp_sse4_2>    mov    0x4(%esp),%edx
0xf7f25244 <__strcmp_sse4_2+4>  mov    0x8(%esp),%eax
```

Una vez sobrepasadas estas dos instrucciones, siguiendo el mismo racionamiento que para la primera pregunta, vemos el contenido de `%eax`:

```bash
(gdb) x/cb $eax
0x56559038 <estanoeslacontrasenia>:     112 'p'
0x56559039 <estanoeslacontrasenia+1>:   111 'o'
0x5655903a <estanoeslacontrasenia+2>:   114 'r'
0x5655903b <estanoeslacontrasenia+3>:   102 'f'
0x5655903c <estanoeslacontrasenia+4>:   97 'a'
0x5655903d <estanoeslacontrasenia+5>:   118 'v'
0x5655903e <estanoeslacontrasenia+6>:   111 'o'
0x5655903f <estanoeslacontrasenia+7>:   114 'r'
0x56559040 <estanoeslacontrasenia+8>:   10 '\n'

```

**Hemos encontrado la segunda contraseña: "porfavor"**. Seguimos ejecutando el programa y vemos que se repiten 9 veces más el mismo conjunto de instrucciones, por lo que llegamos a la conclusión de que tenemos 10 intentos para responder correctamente a la segunda pregunta.

### 4. Cuarto paso: Clave numérica.

Tras ejecutar el programa de forma normal unas cuantas veces, cambiando el momento en el que damos la respuesta correcta en la segunda pregunta, podemos llegar rápidamente a la conclusión de que la clave numérica corresponde con el número de respuestas dadas en la segunda pregunta. Por tanto, hemos encontrado las 3 claves necesarias para desactivar la bomba.