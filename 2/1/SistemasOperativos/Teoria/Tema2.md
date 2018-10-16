Sistemas operativos. Curso 2018/2019
#Tema 2. Procesos e hilos.
###1. Generalidades sobre procesos e hilos.
####Ejecución del SO dentro de los procesos de usuario
<div style="text-align: justify">El sistema operativo se percibe como un conjunto de rutinas que el usuario invoca para realizar diferentes funciones, ejecutadas dentro del entorno de proceso de usuario.

Cuando ocurre una llamada al sistema o una interrupción, el procesador se pone en modo núcleo y se pasa el control al sistema operativo, cambiando el modo a una rutina del sistema operativo, continuando aún así la ejecución en modo usuario. Tras haber realizado el trabajo, el sistema operativo determina si el programa debe continuar su ejecución, realizando un cambio de modo y continuando el proceso interrumpido. En caso contrario, el control se pasa a la rutina de cambio de proceso.

En cuanto a estructura de proceso, este se compone de un bloque de control formado por un identificador y la información tanto del estado del procesador como de control de proceso, una pila de usuario, un espacio privado de direcciones de usuario, una pila de núcleo, utilizada para manejar llamadas/retornos cuando el proceso está en modo núcleo y un espacio compartido entre todos los procesos de direcciones, en el que se encuentra el código y los datos del sistema operativo. 
####Creación de procesos.
Cuando se va a añadir un nuevo proceso, el sistema operativo construye las estructuras de datos que se usan para manejar ese proceso así como reservar el espacio de direcciones en memoria principal. Los sucesos más comunes que provocan la creación de procesos son los siguientes:

- En un entorno por lotes, un proceso nuevo es creado por el planificador como respuesta a una nueva solicitud de trabajo.

- En una sesión interactiva, ocurre cuando un usuario entra en el sistema desde una terminal.

- Un programa de usuario puede necesitar realizar una función o un servicio, para el cual el SO crea un nuevo proceso en respuesta.

- Por motivos de modularidad o paralelismo, un proceso puede crear otros mediante llamadas al sistema.
####Cambio de contexto
Durante la ejecución de un proceso, sus registros, su puntero a pila, sus registros, su PC, etc. están cargados en la CPU. El sistema operativo puede interrumpirlo, para ello guarda primero los valores actuales de esos registros (contexto) en el PCB (Process Control Block) de ese proceso. Tras ello, puede cederle el uso de la CPU a otro proceso u operación. A esta conmutación de un proceso a otro de la CPU se le denomina **cambio de contexto**.
####PCBs y colas de estados
El SO mantiene una colección de colas que representan el estado de todos los procesos en el sistema, y de forma usual existe una cola por estado. Cada PCB está encolado en una cola de estado acorde al estado actual del proceso al que está asociado. Conforme un proceso cambia de estado, su PCB es retirado de una cola y encolado en otra. Podemos diferenciar las colas de estados en:

- Cola de trabajos: Conjunto de trabajos pendientes de ser admitidos por el sistema.

- Cola de preparados: conjunto de todos los procesos que residen en memoria principal, preparados y esperando para ejecutarse.

- Cola(s) de bloqueados: conjunto de procesos esperando un evento o un recurso actualmente no disponible.
####Planificación de procesos
El **planifcador de procesos** es la parte del sistema operativo que se encarga de, cuando dos o más procesos entran al mismo tiempo en el estado listo, decidir cuál de ellos va a ejecutarse a continuación y ocupar la CPU. Existen tres tipos de planificadores de la CPU:

- Planificador a largo plazo (o planificador de trabajos): Selecciona los trabajos que deben admitirse en el sistema.

- Planificador a corto plazo (o planificador de la CPU): Selecciona al proceso en estado preparado o ejecutable que debe ejecutarse a continuación y le asigna la CPU. Es invocado muy frecuentemente.

- Planificador a medio: Se encarga de sacar o introducir procesos de la memoria principal.
####Comportamiento de un proceso
Se denomina **ráfaga de CPU** al tiempo que está un proceso está en estado de ejecución. Normalmente un proceso alterna ráfagas de CPU con periodos de tiempo en que se encuentra en estado bloqueado.

Se dice que un proceso "está limitado por la E/S" si intercala pequeñas ráfagas de CPU con muchos tiempos de espera, es decir, que frecuentemente realice operaciones que provoquen un cambio al estado de bloqueo (como las operaciones E/S).

Un proceso que realiza operaciones muy largas que obligan a ráfagas largas de CPU con pocas interrupciones se dice que "está limitado por la CPU". 
</div>