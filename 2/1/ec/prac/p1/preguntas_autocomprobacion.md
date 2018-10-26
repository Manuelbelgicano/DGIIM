Manuel Gachs Ballegeer 2ºDGIIM

##Preguntas de autocomprobación.
###Preguntas sobre saludo.s
**1. **¿Qué contiene EDX tras ejecutar `mov longsaludo, %edx`? ¿Para qué necesitamos esa instrucción, o ese valor? Responder no sólo el valor concreto (en decimal y hex) sino también el significado del mismo (¿de dónde sale?). Comprobar que se corresponden los valores hexadecimal y decimal mostrados en la ventana `Status->Registers`.

*El registro `%edx` contiene el valor de `longsaludo` (28 en decimal, 0x1C en hexadecimal), que es el tamaño del string `saludo`. Necesitamos ese valor puesto que en la siguiente instrucción se hace una llamada al sistema que necesita saber el tamaño de la cadena de caracteres que se quiere mostrar en pantalla.*

**3. **¿Qué sucede si se elimina el símbolo de dato inmediato (\$) de la instrucción anterior? (`mov saludo, %ecx`) Realizar la modificación, indicar el contenido de ECX en hexadecimal, explicar por qué no es lo mismo en ambos casos. Concretar de dónde viene el nuevo valor (obtenido sin usar \$).

*En lugar de guardar la dirección de memoria del inicio del string `saludo`, guarda su contenido (1634496328 en decimal, 0x616C6F48 en hexadecimal), mientras que el valor anterior era 4202520 en decimal y 0x402018 en hexadecimal.*

**7. **¿Qué sucede si se elimina del programa la primera instrucción `int $0x80`? ¿Y si se elimina la segunda?. Razonar las respuestas.

*Si se elimina la primera, en la pantalla no aparece el mensaje de `saludo`, mientras que si se elimina la segunda, no acaba la ejecución del programa. Esto ocurre porque la instrucción `int $0x80` realiza una llamada al sistema y, dependiendo de los valores de los registros `%eax` y `%ebx`.*

###Preguntas sobre suma.s
**1.**¿Cuál es el contenido de EAX justo antes de ejecutar la instrucción RET, para esos componentes de lista concretos? Razonar la respuesta, incluyendo cuánto valen 0b10, 0x10, y `(.‐lista)/4`.

*El contenido de EAX es 37  (la suma de los 9 elementos) y el de `(.‐lista)/4` es 9, puesto que es el número de elementos de `lista`. El número 0b10 es 2 en decimal y 0x10 es 16 en decimal.*

**3. **¿Qué dirección se le ha asignado a la etiqueta suma? ¿Y a bucle? ¿Cómo se ha obtenido esa información? 

*A suma se le ha asignado 0x4005A1 y a bucle 0x4005AC. Se ha obtenido haciendo un displaay de su contenido, ya que al lado de la etiqueta aparece su dirección de memoria.*

**4. **¿Para qué usa el procesador los registros EIP y ESP?

*ESP lo usa el procesador para guardar la última dirección de la pila con contenido, mientras que EIP lo usa para obtener la dirección de memoria de la instrucción que se está ejecutando.*

**5. **¿Cuál es el valor de ESP antes de ejecutar `call`, y cuál antes de ejecutar RET? ¿En cuánto se diferencian ambos valores? ¿Por qué? ¿Cuál de los dos valores de ESP apunta a algún dato de interés para nosotros? ¿Cuál es ese dato?

*El valor de ESP antes de ejecutar `call`  es 0xBFFFF26C y después es 0XBFFFF268. Se diferencian en 4 bytes. Se diferencian en esa cantidad porque en la pila se ha almacenado la dirección de retorno de la función suma. Nos interesa el segundo valor, ya que sin él no podríamos salir de la función suma.*

###Preguntas sobre suma64unsigned.s
**1. **Para N≈32, ¿cuántos bits adicionales pueden llegar a necesitarse para almacenar el resultado? Dicho resultado se alcanzaría cuando todos los elementos tomaran el valor máximo sin signo. ¿Cómo se escribe ese valor en hexadecimal? ¿Cuántos acarreos se producen? ¿Cuánto vale la suma (indicarla en hexadecimal)? Comprobarlo usando ddd.

*Hacen falta 5 bits adicionales. El máximo valor que se puede tomar es 0x0FFFFFFFF, y se producen 31 acarreos. La suma vale 0x0000001FFFFFFFE0*

**2. **Si nos proponemos obtener sólo 1 acarreo con una lista de 32 elementos iguales, el objetivo es que la suma alcance $2^{32}​$ (que ya no cabe en 32bits). Cada elemento debe valer por tanto $\frac{2^{32}}{32}​$ =  ? ¿Cómo se escribe ese valor en hexadecimal? Inicializar los 32 elementos de la lista con ese valor y comprobar cuándo se produce el acarreo.

*El valor debe ser 134217728, que en hexadecimal es 8000000. El acarreo se produce en la última suma.*

###Preguntas sobre suma64signed.s
**1. **¿Cuál es el máximo entero positivo que puede representarse (escribirlo en hexadecimal)? Si se sumaran los N≈32 elementos de la lista inicializados a ese valor ¿qué resultado se obtendría (en hexadecimal)? ¿Qué valor aproximado tienen el elemento y la suma (indicarlo en múltiplos de potencias de 10)? Comprobarlo usando ddd.

*El número más grande es 0x7FFFFFFFF. Se obtendría 0x0000000FFFFFFFE0. Aproximadamente el valor de la suma sería 68719476704 y el de cada elemento 2147483647.*

**2. **Misma pregunta respecto a negativos: menor valor negativo en hexadecimal, suma, valores decimales aprox., usar ddd.

*El menor número es 0x80000001. Se obtendría 0xFFFFFFF000000020. Aproximadamente el valor de la suma sería -68719476704 y el de cada elemento -2147483647.*

###Preguntas sobre media64.s

**1. **Rellenando la lista al valor ‐1, la media es ‐1. Cambiando un elemento a 0, la media pasa a valer 0. ¿Por qué? Consultar el manual de Intel sobre la instrucción de división. ¿Cuánto vale el resto de la división en ambos casos? Probar con ddd.

*Esto ocurre porque la instrucción de división es de números enteros, y como $|-1\times 31|<32$, la media es 0. En el primer caso el resto es 0 y en el segundo -31.*