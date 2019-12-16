// Enunciado:
// https://github.com/Mapachana/Apuntes/blob/master/SO/examenes/SO_Examen2015_Modulo2_Mar%C3%ADaAngustiasS%C3%A1nchezBuend%C3%ADa.pdf

#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>

// Contador del literal
int contador = 0;

// Handler de la señal
void handler(int sig) {
	printf("Contador parcial %d\n",contador);
	kill(0,SIGKILL);
	exit(EXIT_FAILURE);
}

// Programa
int main(int argc,char *argv[]) {
	// Comprobamos que se dan los argumentos
	if (argc!=3) {
		perror("Error en el número de argumentos");
		exit(EXIT_FAILURE);
	}
	char *literal_c;
	char *nombre_directorio;
	literal_c = argv[1];
	nombre_directorio = argv[2];
	umask(0);
	
	// Desactivamos el buffer de salida para que haga los print de inmediato.
	setvbuf(stdout,NULL,_IONBF,0);
	
	// Aplicamos el nuevo manejo de señales
	struct sigaction sa;
	sa.sa_handler = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT,&sa,NULL)==-1) {
		perror("Error en el manejo de señales");
		exit(EXIT_FAILURE);
	}

	// Modificamos la salida de error para que aparezca en el archivo "ErrorMigrep"
	int fd_error;
	if ((fd_error=open("ErrorMigrep",O_CREAT|O_WRONLY,0666))<0) {
		perror("Error en la creación de archivo de errores");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd_error,STDERR_FILENO)<0) {
		perror("Error en la redirección de errores");
		exit(EXIT_FAILURE);
	}
	
	// Abrimos el directorio
	DIR *directorio;
	struct dirent *archivo;
	if ((directorio=opendir(nombre_directorio))==NULL) {
		perror("Error abriendo el directorio");
		exit(EXIT_FAILURE);
	}

	// Creamos el archivo fifo
	int fd[2];
	pipe(fd);
	
	// Recorremos el directorio
	struct stat atrib;
	int pid;
	char nombre_archivo[256];
	char res_c[10];
	while ((archivo=readdir(directorio))!=NULL) {
		// Comprobamos que es un archivo regular
		sprintf(nombre_archivo,"%s/%s",nombre_directorio,archivo->d_name);
		stat(nombre_archivo,&atrib);
		if (S_ISREG(atrib.st_mode)) {
			// Creamos el hijo que va a ejecutar grep
			pid = fork();
			if (pid<0) {
				perror("Error en la creación del hijo");
				exit(EXIT_FAILURE);
			}

			// Proceso hijo
			if (pid==0) {
				// Cerramos la lectura y pasamos la salida estándar a la salida
				close(fd[0]);
				if(dup2(fd[1],STDOUT_FILENO)<0) {
					perror("Error en la redirección de salida");
					exit(EXIT_FAILURE);
				}

				// Ejecutamos grep -c literal nombre
				execlp("grep","grep","-c",literal_c,nombre_archivo,NULL);
			// Proceso padre
			} else {
				// Cerramos la escritura
				close(fd[1]);
				
				// Leemos el valor del hijo y lo añadimos al contador
				int res = 0;
				read(fd[0],res_c,10);
				res = atoi(res_c);
				contador += res;
			}
		}
	}
	
	// Escribimos por pantalla el resultado
	printf("Cuenta final: %d\n",contador);

	// Cerramos el directorio
	if (closedir(directorio)<0) {
		perror("Error cerrando el directorio");
		exit(EXIT_FAILURE);
	}

	// Para probar a matar al proceso
	sleep(5);
	exit(EXIT_SUCCESS);
}
