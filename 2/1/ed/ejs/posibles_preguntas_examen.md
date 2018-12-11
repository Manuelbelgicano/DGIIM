# ED: Preguntas examen

### Diseño de iteradores

Se pide el diseño de un iterador de un tipo de dato nuevo, que normalmente suele tener tipos de datos que ya tienen iteradores propios. Por ejemplo, el diseño  de iteradores para esta clase:

```c++
template<class T,class U>
    class diccionario {
        private:
        	list<data<T,U> > datos;
        ...
    };
```

Donde `data` se define como:

```c++
template<class T,class U>
    struct data {
        T clave;
        list<U> info_asoci;
    };
```

Una solución sería crear una clase `iterator` con las funciones:

- `begin()`
- `end()`
- Los siguientes operadores: `++`, `--`, `==`, `!=` y `*`

También puede ocurrir que no existan iteradores de los miembros del nuevo tipo de dato. Por ejemplo una clase matriz en la que se quiera que el iterador recorra por columnas los elementos pares:

```c++
class Matriz {
    private:
    	int **datos;
    	int nf,nc;
    ...
}
```

En este caso se puede utilizar como iterador un puntero a un entero. También puede definirse una matriz como un vector de vectores.

Normalmente se ponen restricciones para los iteradores, como por ejemplo en la siguiente clase:

```c++
class contenedor {
    private:
    	map<string,bintree<int> > datos;
    ...
}
```

En la que el iterador debe iterar sobre elementos cuyo `string` tenga tamaño 4 y el `bintree` sea ABB. En este caso podemos aprovechar el tipo `iterator` de la clase `map`, donde la única dificultad se encuentra en el operador `++`.

> Según el profesor, en el examen se pedirá la definición del tipo de dato también, simplemente se dará un ejemplo de ejecución.

### Ejercicios sobre la STL

Se harán preguntas de tipos de datos de la STL, pero con algunas restricciones. Por ejemplo, un ejercicio con `std::list` en la que no se puede usar la función `sort()`. Un ejemplo de ejercicio es el siguiente:

*Diseñar una función que dada una lista de enteros elimine todos aquellos que no sean más grandes que todos los anteriores. Por ejemplo: `<1,3,4,2,4,7,7,1>` se convierte en `<1,3,4,7>`*

Normalmente se trata de diseñar algoritmos (funciones) que resuelvan un problema dado (agrupar elementos, eliminar cierto tipo de elementos, ...). En este tipo de ejercicios se puede pedir que la función tenga un cierto grado de optimización. 

### Árboles

Otro tipo de ejercicios se basan en realizar funciones sobre árboles, como por ejemplo una que encuentre nodos que tengan al menos 5 descendientes más por un lado que por otro. 

En este tipo de ejercicios es importante diferenciar las diferentes propiedades de los distintos tipos de árboles, como los `bintree` y los `ABB`. En estos casos suele ser interesante el uso de iteradores o funciones recursivas.

> Siempre hay un ejercicio "tirado", que se basa en el entendimiento del tipo de dato con el que se está trabajando y suele ser fácil

**Siempre pueden usarse estructuras auxiliares salvo que se diga lo contrario.** 

### Otros comentarios de interés

- Es importante estudiar y conocer las diferencias entre las distintas clases disponibles de la STL.
- Conocer y tener en cuenta `reverse_iterator`.
- Estudiar **BIEN** árboles e igual con tablas Hash.