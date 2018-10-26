Manuel Gachs Ballegeer 2ºDGIIM
##Preguntas de autocomprobación.
###Preguntas sobre saludo.s
<div style="text-align: justify">**1. **¿Qué contiene EDX tras ejecutar `mov longsaludo, %edx`? ¿Para qué necesitamos esa instrucción, o ese valor? Responder no sólo el valor concreto (en decimal y hex) sino también el significado del mismo (¿de dónde sale?). Comprobar que se corresponden los valores hexadecimal y decimal mostrados en la ventana `Status->Registers`.
*El registro `%edx` contiene el valor de `longsaludo` (28 en decimal, 0x1C en hexadecimal), que es el tamaño del string `saludo`. Necesitamos ese valor puesto que en la siguiente instrucción se hace una llamada al sistema que necesita saber el tamaño de la cadena de caracteres que se quiere mostrar en pantalla.*
**3. **¿Qué sucede si se elimina el símbolo de dato inmediato ($) de la instrucción anterior? (`mov saludo, %ecx`) Realizar la modificación, indicar el contenido de ECX en hexadecimal, explicar por qué no es lo mismo en ambos casos. Concretar de dónde viene el nuevo valor (obtenido sin usar $).
*En lugar de guardar la dirección de memoria del inicio del string `saludo`, guarda su contenido (1634496328 en decimal, 0x616C6F48 en hexadecimal), mientras que el valor anterior era 4202520 en decimal y 0x402018 en hexadecimal.*
**4. **¿Cuántas posiciones de memoria ocupa ocupa la variable longsaludo? ¿Y la variable saludo? ¿Cuántos bytes ocupa por tanto la sección de datos? Comprobar con un volcado `Data‐>Memory` mayor que la zona de datos  antes de hacer Run.
</div>
