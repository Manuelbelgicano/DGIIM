# Módulo II. Sesión I

Para realizar la sesión, es necesario conocer lo siguiente:
### ``open``

La función ``open`` abre un fichero para su posterior uso en el programa.

- **Cabeceras necesarias:** ``<sys/types.h>``,  ``<sys/stat.h>``, ``<fcnlt.h>``

- **Formato de uso:**
  ```c
  int open(const char *pathname, int flags);
  int open(const char *pathname, int flags, mode_t mode);
  int creat(const char *pathname, mode_t mode);
  ```

- **Parámetros:**
  - ``pathname``: Se refiere a la ruta del archivo.
  - ``flags``: Este argumento indica los permisos o macros. Se pueden combinar más de uno usando el operador or (|). No se indican todos, sólamente los que podrían utilizarse en la asignatura. Para más infromación sobre las posibles flags, consultar con ``man 2 open``.

    - ``O_RDONLY``: La apertura es solamente para lectura.
    - ``O_WRONLY``: La apertura es solamente para escritura.
    - ``O_RDWR``: La apertura es para lectura y escritura.
    - ``O_CREAT``: Si el archivo no existe, se crea.
    - ``O_EXCL``: Al combinarse con ``O_CREAT``, genera un fallo en ``open`` si el archivo ya existía.
    - ``O_TRUNC``: Si el archivo ya existe, es regular y se permite escribir, será truncado a longitud 0.
    - ``O_APPEND``: El archivo se añade en modo de sólo-añadir. Antes de cada escritura, el offset se posiciona al final del archivo.
  - ``mode``: Este argumento especifica los permisos a emplear en caso de que se cree un nuevo fichero. Se pueden combinar de la misma manera que el argumento ``flags``. Este argumento es modificado por la máscara umask del proceso.

    |           Nombre           |               Descripción                | Código |
    | :------------------------: | :--------------------------------------: | :----: |
    |        ``S_IRWXU``         | El usuario tiene permisos de lectura, escritura y ejecución | 00700  |
    | ``S_IRUSR`` o ``S_IREAD``  |   El usuario tiene permisos de lectura   | 00400  |
    | ``S_IWUSR`` o ``S_IWRITE`` |  El usuario tiene permisos de escritura  | 00200  |
    | ``S_IXUSR`` o ``S_IEXEC``  |  El usuario tiene permisos de ejecución  | 00100  |
    |        ``S_IRWXG``         | El grupo tiene permisos de lectura, escritura y ejecución | 00070  |
    |        ``S_IRGRP``         |    El grupo tiene permisos de lectura    | 00040  |
    |        ``S_IWGRP``         |   El grupo tiene permisos de escritura   | 00020  |
    |        ``S_IXGRP``         |   El grupo tiene permisos de ejecución   | 00010  |
    |        ``S_IRWXO``         | Los otros tienen permisos de lectura, escritura y ejecución | 00007  |
    |        ``S_IROTH``         |   Los otros tienen permisos de lectura   | 00004  |
    |        ``S_IWOTH``         |  Los otros tienen permisos de escritura  | 00002  |
    |        ``S_IXOTH``         |  Los otros tienen permisos de ejecución  | 00001  |

- **Valor de retorno:** La función ``open`` devuelve el nuevo descriptor de fichero, o -1 en caso de error.

### ``close``

La función ``close`` cierra un descriptor de fichero de forma que ya no se refiera a fichero alguno.

- **Cabeceras necesarias:** ``<unistd.h>``

- **Formato de uso:**

  ```c
  int close(int fd);
  ```

- **Parámetros:**

  - ``fd``: Se refiere al descriptor de fichero que se quiere cerrar.

- **Valor de retorno:** Devuelve 0 en caso de éxito y -1 en caso de error.

### ``read``

Esta función lee un número de bytes de un archivo y los guarda en un búffer.

- **Cabeceras necesarias:** ``<unistd.h>``

- **Formato de uso:** 

  ```c
  ssize_t read(int fd, void *buf, size_t nbytes);
  ```

- **Parámetros:**

  - ``fd``: Descriptor de fichero del archivo del que se quiere leer.
  - ``buf``: Búffer donde se quieren guardar los bytes leídos.
  - ``nbytes``: Número de bytes que se quieren leer. También es el número de bytes que avanza el offset.

- **Valor de retorno:** En caso de éxito, se devuelve el número de bytes leídos (0 indica el fin del fichero). En caso de error, se devuelve -1.


### ``write``

Esta función escribe un número de bytes del búffer en un archivo.

- **Cabeceras necesarias:** ``<unistd.h>``

- **Formato de uso:** 

  ```c
  ssize_t write(int fd, const void *buf, size_t num);
  ```

- **Parámetros:**

  - ``fd``: Descriptor de fichero del archivo que se quiere leer.
  - ``buf``: Búffer del que se escribe en el archivo.
  - ``num``: Número de bytes que se quieren escribir.

- **Valor de retorno:** En caso de éxito se devuelve el número de bytes escritos (0 en el caso de que no se haya escrito nada). En caso de error, se devuelve -1.

### ``lseek``

Esta función reposiciona el offset de un archivo. Permite posicionarlo tras el final del archivo.

- **Cabeceras necesarias:** ``<sys/types.h>``, ``<unistd.h>``

- **Formato de uso:**

  ```c
  off_t lseek(int fildes, off_t offset, int whence);
  ```

- **Parámetros:**

  - ``fildes``: Descriptor de fichero del archivo al cual se le quiere modificar el offset.
  - ``offset``: Número de bytes que se quiere mover el offset.
  - ``whence``: En este argumento se pueden especificar 3 directivas distintas:
    - ``SEEK_SET``: El puntero (offset) se coloca a ``offset`` bytes del inicio del archivo.
    - ``SEEK_CUR``: El número de bytes de ``offset`` se suma a la dirección actual del puntero y se coloca en el resultado de la suma.
    - ``SEEK_END``: El puntero se coloca a ``offset`` bytes tras el final del archivo.

- **Valor de retorno: **Devuelve la posición del offset resultante desde el inicio del archivo medida en bytes. En caso de error, devuelve (off_t)-1.

### ``struct stat``

Esta estructura contiene la información de un archivo.

- **Descripción de la estructura:**

  ```c
  struct stat {
    dev_t st_dev; 		//Dispositivo
    ino_t st_ino; 		//Inodo
    mode_t st_mode; 		//Permisos
    nlink_t st_nlink; 	//Numero de enlaces fisicos
    uid_t st_uid;			//ID del usuario propietario
    gid_t st_gid;			//ID del grupo propietario
    dev_t st_rdev;		//Tipo de dispositivo (si es dispositivo inodo)
    off_t st_size;		//Tamaño total en bytes
    blksize_t st_blksize;	//Tamaño de bloque para el sistema de ficheros de E/S
    blkcnt_t st_blocks;	//Número de bloques asignados
    time_t st_atime;		//Hora de último acceso
    time_t st_mtime;		//Hora de última modificación
    time_t st_ctime;		//Hora de último cambio
  };
  ```

- **``st_mode``**: Este parámetro contiene los permisos sobre el archivo, y se definen las siguientes macros y flags:

  - Macros:
    - ``S_ISLINK(mode)``: Indica si es un enlace simbólico.
    - ``S_ISREG(mode)``: Indica si es un fichero regular.
    - ``S_ISDIR(mode)``: Indica si es un directorio.
    - ``S_ISCHR(mode)``: Indica si es un dispositivo de caracteres.
    - ``S_ISBLK(mode)``: Indica si es un dispositivo por bloques.
    - ``S_ISFIFO(mode)``: Indica si es una tubería nombrada (fifo).
    - ``S_ISLNK(mode)``: Indica si es un enlace simbólico.
    - ``S_ISSOCK(mode)``: Indica si es un conector.

  - Flags: Aparte de las mostradas aquí, también se pueden usar las del parámetro ``flags`` de ``open``, añadiendo dos ceros al inicio de los códigos.

    |    Nombre     |               Descripción                | Código  |
    | :-----------: | :--------------------------------------: | :-----: |
    |  ``S_IFMT``   | Máscara de bits para los campos de bits del archivo | 0170000 |
    | `` S_IFSOCK`` |                  Socket                  | 0140000 |
    | `` S_IFLNK``  |             Enlace simbólico             | 0120000 |
    | `` S_IFREG``  |             Archivo regular              | 0100000 |
    | `` S_IFBLK``  |          Dispositivo de bloques          | 0060000 |
    | `` S_IFDIR``  |                Directorio                | 0040000 |
    | `` S_IFCHR``  |        Dispositivo de caracteres         | 0020000 |
    | `` S_IFIFO``  |             Cauce con nombre             | 0010000 |
    | `` S_ISUID``  |                 bit SUID                 | 0004000 |
    | `` S_ISGID``  |                 bit SGID                 | 0002000 |
    |  ``S_ISVTX``  |                sticky bit                | 0001000 |

### ``lstat``

Esta función obtiene la información de un archivo específico.

- **Cabeceras necesarias:** ``<sys/types.h>``, ``<sys/stat.h>``, ``<unistd.h>``

- **Formato de uso:** 

  ```c
  int stat(const char *file_name, struct stat *buf);
  int fstat(int filedes, struct stat *buf);
  int lstat(const char *file_name, struct stat *buf);
  ```

- **Parámetros:**

  - ``file_name``/```filedes``: Se refiere al fichero especificado. En caso de ``stat`` y ``lstat`` es la ruta del archivo, mientras que con ``fstat`` se refiere al descriptor de fichero que se obtiene con la función ``open``.
  - ``buf``: Se trata de la ``struct stat`` en la que queremos que se copie la del archivo. Se pasa por referencia en la función.

- **Valor de retorno:** En caso de éxito se devuelve 0, y en caso de error -1.

### Otras funciones/conceptos de utilidad

#### ``sprintf``

Esta función copia un mensaje en una string.

- **Cabeceras necesarias:** ``<stdio.h>``

- **Formato de uso:** 

  ```c
  int sprintf(char *str, const char *format, ...);
  ```

- **Parámetros:**

  - ``str``: String donde se guarda el mensaje.
  - ``format`` y ``...``: Mensaje que se quiere guardar. Tiene el mismo formato que ``printf``.

- **Valor de retorno:** En caso de éxito, devuelve el número de caracteres impresos (sin contar el caracter '\0'). En caso de error, se devuelve un valor negativo.

#### Macros

Las macros consisten en una declaración al inicio de un archivo de código que actúa como alias. Se realizan de la siguiente manera.

```c
#define <alias> <condicion/valor/variable...>
```

#### Conocer el tipo de archivo/permisos a partir de ``st_mode``

Se puede realizar de dos maneras. La primera consiste en usar las directivas ya definidas para el parámetro. La segunda es realizar la operación Y (&) entre ``st_mode`` y la máscara de bits (``S_IFMT``). Ambos métodos son equivalentes. Ejemplo:

```c
...
sruct stat atrib;
lstat(pathname,&atrib);
if (S_ISREG(atrib.st_mode))							       //Con la directiva
  printf("%s es un archivo regular.\n",pathname);
if ((atrib.st_mode & S_IFMT)==S_IFREG)				//Con la operación lógica
  printf("%s es un archivo regular.\n",pathname);
...
```

