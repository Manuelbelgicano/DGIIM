## Examen práctica 2

Modificar la solución al problema del barbero durmiente, tal como se muestra a continuación, guardando la solución en un archivo denominado `barberia2.cpp`. El comportamiento es idéntico al problema original, salvo en dos aspectos:

**a)** En este caso, existen 2 tipos de clientes, *tipo 0* y *tipo 1*, existiendo sillas específicas en la sala de espera para los clientes de cada tipo concreto. Se puede asumir que existen 3 clientes de cada tipo.

**b)** el barbero no puede cortar de forma consecutiva a dos clientes del mismo tipo por lo que debe ir cortando el pelo de forma alternada a los clientes de cada tipo.

**c)** Cuando el barbero termina con un cliente de un tipo, comprueba si hay hay algún cliente del otro tipo y, si no lo hay, se echa a dormir hasta que llegue uno del tipo apropiado.

**d)** Si llega un cliente que no es demandado en ese instante por el barbero, debe entrar en la sala de espera, aunque el barbero esté durmiendo. Al abrir la barbería, el barbero empieza siempre pelando a un cliente del *tipo 0*, después a uno del *tipo 1* y así sucesivamente.

**e)** Una vez despertado, el barbero debe pelar al cliente que le despertó que ya estará sentado o estará a punto de sentarse en la silla de pelar.
