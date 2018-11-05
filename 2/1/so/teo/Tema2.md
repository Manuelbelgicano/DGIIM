Sistemas operativos. Curso 2018/2019
# Tema 2. Procesos e hilos.
### 1. Generalidades sobre procesos e hilos.
#### 1.1. Ejecución del SO dentro de los procesos de usuario
El sistema operativo se percibe como un conjunto de rutinas que el usuario invoca para realizar diferentes funciones, ejecutadas dentro del entorno de proceso de usuario.

Cuando ocurre una llamada al sistema o una interrupción, el procesador se pone en modo núcleo y se pasa el control al sistema operativo, cambiando el modo a una rutina del sistema operativo, continuando aún así la ejecución en modo usuario. Tras haber realizado el trabajo, el sistema operativo determina si el programa debe continuar su ejecución, realizando un cambio de modo y continuando el proceso interrumpido. En caso contrario, el control se pasa a la rutina de cambio de proceso.

En cuanto a estructura de proceso, éste se compone de un bloque de control formado por un identificador y la información tanto del estado del procesador como de control de proceso, una pila de usuario, un espacio privado de direcciones de usuario, una pila de núcleo, utilizada para manejar llamadas/retornos cuando el proceso está en modo núcleo y un espacio compartido entre todos los procesos de direcciones, en el que se encuentra el código y los datos del sistema operativo. 
#### 1.2. Creación de procesos.
Cuando se va a añadir un nuevo proceso, el sistema operativo construye las estructuras de datos que se usan para manejar ese proceso así como reservar el espacio de direcciones en memoria principal. Los sucesos más comunes que provocan la creación de procesos son los siguientes:

- En un entorno por lotes, un proceso nuevo es creado por el planificador como respuesta a una nueva solicitud de trabajo.

- En una sesión interactiva, ocurre cuando un usuario entra en el sistema desde una terminal.

- Un programa de usuario puede necesitar realizar una función o un servicio, para el cual el SO crea un nuevo proceso en respuesta.

- Por motivos de modularidad o paralelismo, un proceso puede crear otros mediante llamadas al sistema.
#### 1.3. Cambio de contexto
Durante la ejecución de un proceso, sus registros, su puntero a pila, sus registros, su PC, etc. están cargados en la CPU. El sistema operativo puede interrumpirlo, para ello guarda primero los valores actuales de esos registros (contexto) en el PCB (Process Control Block) de ese proceso. Tras ello, puede cederle el uso de la CPU a otro proceso u operación. A esta conmutación de un proceso a otro de la CPU se le denomina **cambio de contexto**.
#### 1.4. PCBs y colas de estados
El SO mantiene una colección de colas que representan el estado de todos los procesos en el sistema, y de forma usual existe una cola por estado. Cada PCB está encolado en una cola de estado acorde al estado actual del proceso al que está asociado. Conforme un proceso cambia de estado, su PCB es retirado de una cola y encolado en otra. Podemos diferenciar las colas de estados en:

- Cola de trabajos: Conjunto de trabajos pendientes de ser admitidos por el sistema.

- Cola de preparados: conjunto de todos los procesos que residen en memoria principal, preparados y esperando para ejecutarse.

- Cola(s) de bloqueados: conjunto de procesos esperando un evento o un recurso actualmente no disponible.
#### 1.5. Planificación de procesos
El **planifcador de procesos** es la parte del sistema operativo que se encarga de, cuando dos o más procesos entran al mismo tiempo en el estado listo, decidir cuál de ellos va a ejecutarse a continuación y ocupar la CPU. Existen tres tipos de planificadores de la CPU:

- Planificador a largo plazo (o planificador de trabajos): Selecciona los trabajos que deben admitirse en el sistema.

- Planificador a corto plazo (o planificador de la CPU): Selecciona al proceso en estado preparado o ejecutable que debe ejecutarse a continuación y le asigna la CPU. Es invocado muy frecuentemente.

- Planificador a medio: Se encarga de sacar o introducir procesos de la memoria principal.
##### Comportamiento de un proceso
Se denomina **ráfaga de CPU** al tiempo que está un proceso en estado de ejecución. Normalmente un proceso alterna ráfagas de CPU con periodos de tiempo en que se encuentra en estado bloqueado.

Se dice que un proceso está "limitado por la E/S" si intercala pequeñas ráfagas de CPU con muchos tiempos de espera, es decir, que frecuentemente realice operaciones que provoquen un cambio al estado de bloqueo (como las operaciones E/S).

Un proceso que realiza operaciones muy largas que obligan a ráfagas largas de CPU con pocas interrupciones se dice que está "limitado por la CPU". 

Es importante que el planificador seleccione una buena mezcla de trabajos, puesto que en el caso de que la mayor parte fueran procesos limitados por E/S, la cola de preparados estaría prácticamente vacía y se infrautilizaría de CPU. Si ocurriera al contrario, serían entonces los dispositivos de E/S y, en general, los recursos aparte la CPU, los que estarían infrautilizados.

##### Planificador a corto plazo
El **planificador a corto plazo** es la parte del SO que decide a qué proceso darle el control de la CPU. El **despachador** es la parte del SO que realiza las acciones adecuadas para efectuar el cambio de asignación de CPU entre dos procesos, tal como haya decidido el planificador a corto plazo. Esto involucra salvar el contexto del proceso actual y restaurar el del nuevo proceso, aparte de saltar a la posición de memoria de del nuevo proceso para su reanudación. Estos términos se pueden usar de forma equivalente.

El planificador a corto plazo se activa en las siguientes situaciones:

- Al crear un nuevo proceso, se debe elegir si ejecutar el proceso padre o el proceso hijo.
- Cuando un proceso termina o se bloquea por esperar una operación de E/S u otra razón. Se debe elegir en este caso otro proceso para ejecutar.
- En el caso de que algún elemento del SO determine que el proceso actual no puede seguir ejecutándose, pasándolo al estado de bloqueo.
- Si un evento ajeno al proceso actual hace que el SO determine que el proceso actual no es el más preferente para disfrutar de la CPU, por ejemplo si un proceso agota el periodo de tiempo que tiene asignado.

Se dice que una política de planificación es **apropiativa o preemptive** si incluye los dos últimos puntos. Una política de planificación es denominada **con derecho preferente o con desplazamiento** si gestiona la activación del planificador por las siguientes razones:

- Se ha creado un nuevo proceso.

- Cierto suceso ha provocado un cambio en el estado de un proceso de *bloqueado* a *ejecutable*.

##### Medidas y objetivos de las políticas de planificación de CPU
Se definen ciertas medidas asociadas a cada proceso. Denotamos $t$ al tiempo de CPU de un proceso y definimos:

- Tiempo de respuesta o de finalización($T$): Tiempo total transcurrido desde que se crea el proceso hasta que se termina.

- Tiempo de espera($E$): Tiempo que el proceso ha estado esperando en la cola de ejecutables. Se calcula de la siguiente manera: $E=T-t$

- Penalización($P$): Proporción del tiempo empelado por el SO en tomar decisiones alusivas a la planificación de procesos. Debe representar entre el 10 y el 30% del tiempo total de la CPU. Se calcula de la siguiente manera: $P=\frac{T}{t}$

Las políticas de planificación de CPU tienen las siguientes metas:

- Realizar un buen uso de la CPU: Una alta proporción del tiempo se debe emplear para la ejecución de procesos.
- Dar un buen servicio: Se debe minimizar la penalización de los procesos.
- En entornos interactivos, es prioritario asegurar una ágil respuesta del sistema por encima de la eficiencia de la CPU.
- En entornos no interactivos, se debe asegurar el buen aproechamiento de la CPU

#### 1.6. Algoritmo de planificación FIFO (First In First Out)
Se trata del algoritmo de planificación más simple, puesto que los procesos son servidos según el orden de llegada a la zona de ejecutables. Se trata de un algoritmo no apropiativo, puesto que cada proceso se ejecuta hasta que se finaliza o se bloquea. 

... (faltan algoritmos)

### 2. Diseño e implementación de procesos en Linux.

Estos apuntes están basados en el kernel 2.6 de Linux ([enlace](https://www.kernel.org)), y tomaremos como equivalentes los términos **tarea (task)** y **proceso**.

### 2.1 Representación de los procesos

La estructura de datos del núcleo que representa un proceso es ``struct task_struct`` definida en el archivo ``<linux/shed.h>``. Es el BCP de ese proceso, siendo una estructura relativamente extensa (1.7 KB en una máquina de 32 bits); y el kernel almacena la lista de procesos como una lista circular doblemente enlazada. Dentro del kernel, las tareas son referenciadas mediante un puntero a su ``task_struct``.

#### Contenidos importantes de ``task_struct``
- Información sobre **identificación del proceso**.
- **Estado**.
- Punteros para manejar las **relaciones entre procesos** (padre-hijo, hermanos, ...).
- Información sobre planificación.
- **Credenciales del proceso** como identificadores de usuario y de grupo.
- **Información estadística** sobre recursos consumidos.
- **Puntero a la estructura ``thread_info``** asociada al proceso.
  - *``flags``*: Contiene varios flgs específicos del proceso, como por ejemplo ``TIF_SIGPENDING`` si el proceso tiene señales pendientes.
  - *``preempt_count``*: Contador para implementar la apropición en modo kernel.
```c
struct thread_info {
	strcut task_struct *task; // puntero a la task_struct del proceso
	...
	unsigned long flags; // low level flags
	_u32 CPU; // CPU en el que el proceso se está ejecutando
	int preempt_count;
	...
	};
}
```
- Información sobre **asignación de memoria**. El kernel representa el espacio de direcciones de un proceso con una estructura ``mm_struct``.
- Información sobre el **terminal** asociado al proceso.
- **Puntero a la estructura ``fs_struct``** que contiene la siguiente información:
  - *``umask``*: Máscara de permisos en creación.
  - *Directorio de trabajo*.
  - *Directorio raíz*.
- **Información sobrearchivos abiertos**. En la ``task_struct`` del proceso hay un puntero a la estructura ``files_struct`` donde se almacena la información sobre archivos abiertos.
- Información alusiva a **señales**:
  - *Manejadores de señales especificados por el proceso*.
  - *Conjunto de señales pendientes*.
  - *Conjunto de señales bloqueadas*.
- **Contexto del proceso**. Los valores de los registros de la CPU específicos del proceso se salvan en la ``task_struct`` cuando el proceso pierde la CPU, y se restauran cuando vuelve a ejecutarse.
- Código de la señal a enviar al padre al finalizar.
- Código a devolver al padre:
  - *bits(0,..,7)*: Número de la señal que provocó el final del proceso, o bien 0 si la finalización ha tenido lugar debido a un ``exit``.
  - *bits(8,...,15)*: Valor con el que se llamó a la función ``exit``.

### 2.2. Estados de un proceso
La variable ``state`` de ``task_struct`` especifica el estado actual del proceso (Valores definidos en ``<sched.h>``).
- **``TASK_RUNNING``**: Proceso ejecutable, tanto si está ejecutándose o está esperando a que se le asigne CPU. Si el proceso se está ejecutando puede estar tanto en el espacio de usuario como en el espacio del kernel.
- **``TASK_INTERRUPTIBLE``**: Proceso bloqueado o durmiendo (la tarea no está lista para ejecutarse porque espera un evento). Cuando el kernel notifique mediante una señal al proceso de que el evento ha ocurrido, cambiará al estado ``TASK_RUNNING`` y podrá reanudar su ejecución cuando se le asigne CPU.
- **``TASK_UNINTERRUPTIBLE``**: Estado idéntico al anterior salvo que es el código del kernel quien lo califica como ejecutale cuando lo considere oportuno.
- **``TASK_STOPPED``**: Proceso parado o detenido, no está ejecutando ni es elegible para serlo. Ocurre cuando la tarea recibe señales como ``SIGSTOP`` o ciertas señales de depuración.
- **``EXIT_ZOMBIE``**: Este estado ocurre cuando el proceso ha terminado pero está espeando a que el padre tome el valor de retorno con un ``wait``, por lo que todavía no se puede destruir su ``task_struct``.
- **``EXIT_DEAD``**: Es el estado al que pasa un proceso tras la ejecución de ``wait`` por el padre, hasta ser completamente eliminado del sistema.

### 2.3. Estructura interna de un proceso en Linux
La **pila** es la zona del espacio de direcciones lógicas de un proceso que se utiliza para gestionar las llamadas a función que se efectúan en el código del programa. Está formada por un conjunto de capas con estructura LIFO (Last In-First Out). Como un proceso puede estar trabajando en dos modos (usuario o kernel), existe una pila para cada uno.

Cada vez que se realiza una llamada a una función se crea un **marco** nuevo en la pila que contiene: 
- Las variables locales de la función.
- Sus parámetros actuales.
- Una dirección de retorno.
- La dirección del marco anterior para poder eliminar éste.

Cada vez que una función retorna se elimina el marco acutal.

### 2.4. Contexto de un proceso
La ejecución normal de un proceso ocurre en el espacio de usuario (``user-space``). Si se produce una llamada al sistema o se genera una excepción, entra en el espacio del kernel (``kernel-space``) y se dice entonces que el kernel "se está ejecutando en el contexto del proceso", o que está en el contexto del proceso.

Cuando se termina dicha llamada o tratamiento de excepción, el proceso reanuda su ejecución en su espacio de usuario (a no ser que un proceso de más alta prioridad se haya convertido en ejecutable en ese espacio de tiempo, en cuyo caso el planificador lo elegirá para asignarle CPU). 

Contrariamente, cuando ocurre una interrupción, el sistema no está ejecutándose en el contexto de proceso alguno, sino que está ejecutando una rutina de manejo de interrupción (que nunca tiene asociado un proceso en particular).

### 2.5. El árbol de procesos
En todos los entornos UNIX hay una jerarquía de procesos con la siguiente definición:
- Si un proceso P0 hace una llamada al sistema ``fork``, generando el proceso P1, se dice que P0 es el **proceso padre** y P1 es el hijo.
- Si el proceso hace varios ``fork`` general de varios procesos hijos P1, P2, P3; la relación entre ellos es de **hermanos (siblings)**.
- Todos los procesos son descendientes del proceso **init** (pid = 1). El kernel comienza init en el último paso de arranque del sistema, siendo init el que lanza a los demás procesos, completando el de arranque.

Cada ``task_struct`` tiene los siguientes punteros:
- Un puntero a la ``task_struct`` de su **padre**: ``struct task_struct *parent``
- Un puntero a una lista de **hijos**: ``struct list_head children``
- Un puntero a una lista de **hermanos**: ``struct list_head sibling``

La macro ``current`` proporciona un puntero al descriptor de proceso de la tarea que se está ejecutando actualmente. Dado el proceso actual, es posible obtener el descriptor del proceso de su padre mediante el siguiente código: ``struct task_struct *my_parent = current->parent``. El descriptor del proceso init, sin embargo, está almacenado estáticamente como ``init_task``.

El siguiente código pone de manifiesto la relación entre cualquier proceso y el init:
```c
struct task_struct *task;
for (task=current;task!=&init_task;task=task->parent); //task ahora apunta a init
```

### 2.6 Hebras kernel
A veces puede resultar útil que el kernel realice algunas operaciones en segundo plano, para lo que se crean hebras kernel (procesos existentes únicamente en el espacio del kernel). En estos procesos, a diferencia de los normales, no tienen un espacio de direcciones (su puntero ``mm`` es ``NULL``).

Por lo demás, las hebras kernel son planificadas y podrían ser expropiadas, como procesos normales. Se crean por el kernel al levantar al sistema mediante una llamada a ``clone``. Como todo proceso, terminan con una operación ``exit`` o cuando otra parte del kernel provoca su finalización.

### 2.7 Ejecutando llamadas al sistema para gestión de procesos
Nos centramos en llamadas al sistema para gestión de procesos como ``frok``, ``vfork`` y ``clone``. Normalmente se invocan a través de las librerías de C que realizan la comunicación con el kernel. El punto de entrada para ellas son las funciones ``sys_fork``, ``sys_vfork`` y ``sys_clone``, respectivamente. Se caracterizan por:
1. Su implementación es dependiente de la arquitectura puesto que la forma en que los parámetros se pasan entre el espcaio de usuario y el espcaio del kernel son diferentes en las distintas arquitecturas.
2. Su labor es extraer la información suministrada en el espacio de usuario (parámetros de la llamada) e invocar la función ``do_fork``, que es independiente de la arquitectura.

#### Creación de procesos
A la hora de crear un proceso, se sigue el siguiente procedimiento:
1. Se produce una llamada a alguna de las rutinas de librería para crear un nuevo proceso como ``fork``, ``vfork`` o ``clone``. Estas llamadas realizan básicamente la misma función, aunque tienen distintos matices.
2. Se transfiere el control a la función ``do_fork`` del kernel, que a su vez llama a la función ``copy_process``, que realiza en sí la creación del nuevo proceso.
3. La función ``do_fork`` hace posible la ejecución del nuevo hijo.

#### Actuación de ``copy_process``
1. Se crea una **nueva pila kernel**, la estructura **``thread_info``** y la **``task_struct``** para el nuevo proceso con los valores de la tarea actual.
2. Para los elementos de ``task_struct`` del hijo que deban tener valores distintos, se le dan los valores iniciales correctos.
3. Se establece el estado del hijo a ``TASK_UNINTERRUPTIBLE`` mientras se realizan las acciones siguientes.
4. Se establecen los valores adecuados para los flags de la ``task_struct`` del hijo:
  1. Pone a 0 el flag ``PF_SUPERPRIV`` (indice si la tarea usa privilegio de superusuario).
  2. Pone a 1 el flag ``PF_FORKNOEXEC`` (indica si el proceso ha hecho ``fork`` pero no ``exec``).
5. Se llama a ``alloc_pid`` para asignar un PID a la nueva tarea.
6. Según cuáles sean los flags pasados a ``clone``, ``copy_process`` duplica o comparte recursos como archivos abiertos, información de sistemas de archivos, manejadores de señales, espacio de direccionamiento del proceso... Normalmente estos recursos son compartidos entre tareas de un mismo proceso (contrario al caso de que se creen nuevos recursos para el hijo con los valores iniciales que tenía del padre).
7. Finalmente ``copy_process`` termina devolviendo un puntero a la ``task_struct`` del hijo.

### 2.8. Creación de hebras con ``clone``
En el tercer argumento de la función ``clone`` (``flags``), se pueden expresar los llamados **indicadores de clonación**, mediante los caules indicamos qué recursos serán compartidos. Al expresarlos todos, obtenemos una hebra.
- **``CLONE_VM``**: Si este flag está establecido, tanto 