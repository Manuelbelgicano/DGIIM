*Manuel Gachs Ballegeer*

# Makefiles

## 0. Introducción

Un archivo del tipo *makefile* es un archivo que hace uso de la utilidad `make`. Esta utilidad determina que partes de un programa deben de compilarse, y les manda comandos para hacerlo. En esencia, un *makefile* sirve para autocompilar un proyecto en lugar de hacerlo manualmente.

Para poder hacer uso de `make`, en primer lugar debe crearse un archivo del tipo *makefile*. Para ello basta con crear uno con nombre "makefile" o "Makefile". Ambos nombres son completamente válidos (el manual de la GNU recomienda usar el segundo, puesto que suele aparecer cerca del inicio en los listados de directorios, junto otros arhcivos importantes como README).

Es posible también nombrar un archivo *makefile* con otro nombre, pero debemos especificarselo a make después con uno de los siguientes formatos:

```bash
make -f ARCHIVO
make --file=ARCHIVO
make --makefile=ARCHIVO
```

En estos apuntes se usarán ejemplos de programas en lenguaje C++. Sin embargo, los makefiles sirven para muchos más lenguajes de programación. Para información más a fondo sobre makefiles que no aparezca en estos apuntes consultar en el [manual de la GNU](https://www.gnu.org/software/make/manual/make.html).

### 0.1. Contenido de un makefile

Los makefiles están compuestos por 5 tipos de cosas:

1. **Reglas**. Es en definitiva lo que queremos que haga la orden ``make``.
   1. Relgas explícitas. Reglas descritas por el autor del makefile.
   2. Reglas implícitas. Reglas automáticas de ``make``.
2. **Definiciones de variables**. Las variables son alias puestos por el autor del makefile para hacer el archivo más legible y fácil de modificar o ampliar.
3. **Directivas**. Son expresiones o palabras que se usan para diversas funciones que ayudan a simplificar un makefile.
4. **Comentarios**. Se tratan de anotacionesPara escribir un comentario, simplemente se debe escribir el caracter '#' antes del comentario.

## 1. Reglas

Pongamos un ejemplo de una regla. Imaginemos que tenemos un programa en lenguaje C++ que consta de un archivo ``goblin.cpp``, que tiene en su interior una inclusión de la cabecera ``evil.h``. Para obtener el objeto de forma manual escribiríamos en la terminal la siguiente orden:

```bash
g++ -c -g goblin.cpp
```

Esto se traduciría como la siguiente regla en un makefile:

```makefile
goblin.o: goblin.cpp evil.h
	g++ -c -g goblin.cpp
```

Esta regla nos dice dos cosas:

1. Cuándo se ejecutará. Solamente tendrá efecto si el ``goblin.o`` no existe o si los archivos ``goblin.cpp`` o ``evil.h`` han sido modificados desde la última vez que se ejecutó. Por tanto, si usamos la orden ``make`` dos veces de forma consecutiva, esta regla no hará nada.
2. Cómo se obtiene ``goblin.o``. La regla dice exactamente como se construye el archivo objeto a partir de las fuentes.

### 1.1. Sintaxis de una regla

#### Sintaxis general

Una regla está compuesta por tres cosas: objetivos (normalmente uno), pre-requisitos o dependencias y recetas. Un objetivo es el archivo u orden que se quiere realizar. Los pre-requisitos son los archivos o reglas de las que depende el objetivo, mientras que las recetas son las acciones que se siguen para obtener el objetivo. Una regla suele verse así:

```Makefile
objetivos: pre-requisitos
	receta
	...
```

O alternativamente de esta manera:

```makefile
objetivos: pre-requisitos; receta
	receta
	...
```

Es **muy importante** seguir al pie de la letra esta sintaxis, puesto que ``make`` no identificará una línea como una receta si no comienza por un tab (literalmente un tab, no es válido una sucesión de espacios), así como no sabrá interpretar la regla si el objetivo no está separado de los pre-requisitos por el caracter ':'. Además, esta sintaxis tiene las siguientes consecuencias:

- Una línea en blanco que comienza por una tab no es una línea en blanco, sino una receta vacía.
- Un comentario en una receta no es un comentario de *makefile*, sino que será pasado al shell literalmente, por lo que depende del shell si es tratado como comentario o no.
- La definición de una variable dentro del "contexto de una receta" (dentro de una regla e indentado con un tab), será tratado como parte de una receta, no como una variable del makefile, y pasado al shell.
- Una expresión condicional dentro del "contexto de una receta" será considerado parte de una receta y pasado al shell. 

#### Sintaxis específica

Volvamos al ejemplo del principio. En la práctica, los programa son más grandes y no suelen tener todos los archivos en un solo directorio. Imaginemos ahora que tenemos el siguiente árbol de directorios:

```
.
├── include
│   ├── evil.h
│   └── underground.h
├── Makefile
├── obj
└── src
    ├── dungeon.cpp
    ├── goblin.cpp
    └── main.cpp
```

Imaginemos que en el archivo Makefile se encuentra la regla descrita anteriormente para construir ``goblin.o``. Si hacemos la orden ``make`` saltará el siguiente error:

```bash
make: *** No rule to make target 'evil.h', needed by 'goblin.o'.  Stop.
```

¿Cuál es la razón de este error? ¿No era ``evil.h`` una dependencia y no un objetivo? Esto ocurre porque ``make`` busca archivos solamente en el directorio de trabajo actual. Al no encontrar la cabecera, interpreta que se trata del objetivo de una regla. ¿Cómo arreglar esto? Primeramente, debemos escribir la ruta completa del archivo de cabecera. Después, debemos especificar donde se encuentra ese archivo en la receta. Existen varias maneras de hacer esto: a través de la directiva ``vpath``, la variable ``VPATH`` y el uso de la opción ``-I`` o ``--include-dir`` en la regla. Las dos primeras opciones serán explicadas más adelante.

Esta opción de compilación busca posibles dependencias en  ``[directorio]``. En caso de no especificar ningún directorio, ``make`` busca en los siguientes directorios (si existen) en este orden: ``/usr/local/include``, ``usr/gnu/include``, ``/usr/local/include`` y ``/usr/include``. Otra opción interesante del compilador es ``-o <nombre>``. Esta opción permite modificar el nombre de la salida de la compilación, cambiándolo por ``nombre``. Además, suele ser interesante usar los siguientes flags: ``-Wall`` y ``-g``. El primero hace que el compilador nos muestre todos los warnings, mientras que el segundo especifica al compilador que el archivo resultante pueda ser debuggeado.

En resumen, un archivo *makefile* válido para el programa del ejemplo sería el siguiente:

```makefile
all: adventure

adventure: obj/dungeon.o obj/goblin.o obj/main.o
  g++ -Wall -g -o adventure obj/dungeon.o obj/goblin.o obj/main.o

obj/main.o: src/main.cpp include/dungeon.h
  g++ -Wall -g -I./include -c src/main.cpp -o obj/main.o

obj/dungeon.o: src/dungeon.cpp include/dungeon.h
  g++ -Wall -g -I./include -c src/dungeon.cpp -o obj/dungeon.o
  
obj/goblin.o: src/goblin.cpp include/evil.h
  g++ -Wall -g -I./include -c src/goblin.cpp -o obj/goblin.o
```

Sin embargo, es evidente que esta forma de realizar un makefile no es muy práctica, puesto que si se realiza un cambio en el nombre de una carpeta o de un archivo debe buscarse manualmente todas sus instancias en las reglas y escribir el nuevo nombre. Es por ello que se suelen usar variables para nombrar la mayoría de elementos de un makefile.

### 1.2. Reglas especiales

No todas las reglas tienen como objetivos archivos, o sus recetas son simplemente compilar, o tienen pre-requisitos. Como puede observarse, en el ejemplo anterior existe una regla llamada ``all``, que no es un archivo y no tiene recetas. A continuación se explican qué son y cómo se usan este tipo de reglas.

#### Objetivos que no son archivos

