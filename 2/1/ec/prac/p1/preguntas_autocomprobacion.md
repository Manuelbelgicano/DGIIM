Manuel Gachs Ballegeer 2ºDGIIM
##Preguntas de autocomprobación.
###Preguntas sobre saludo.s
<div style="text-align: justify">**1. **¿Qué contiene EDX tras ejecutar `mov longsaludo, %edx`? ¿Para qué necesitamos esa instrucción, o ese valor? Responder no sólo el valor concreto (en decimal y hex) sino también el significado del mismo (¿de dónde sale?). Comprobar que se corresponden los valores hexadecimal y decimal mostrados en la ventana `Status->Registers`.

**2. **¿Qué contiene ECX tras ejecutar `mov $saludo, %ecx`? Indicar el valor en hexadecimal, y el significado del mismo. Realizar un dibujo a escala de la memoria del programa, indicando dónde empieza el programa (`_start, .text`), dónde empieza saludo (`.data`), y dónde está el tope de pila (`%esp`).

**3. **¿Qué sucede si se elimina el símbolo de dato inmediato ($) de la instrucción anterior? (`mov saludo, %ecx`) Realizar la modificación, indicar el contenido de ECX en hexadecimal, explicar por qué no es lo mismo en ambos casos. Concretar de dónde viene el nuevo valor (obtenido sin usar $).

**4. **¿Cuántas posiciones de memoria ocupa ocupa la variable longsaludo? ¿Y la variable saludo? ¿Cuántos bytes ocupa por tanto la sección de datos? Comprobar con un volcado `Data‐>Memory` mayor que la zona de datos  antes de hacer Run.
</div>
