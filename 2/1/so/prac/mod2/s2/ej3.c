// NO FUNCIONA LA PARTE RECURSIVA, PERO NO PASA NADA PORQUE SIEMPRE USAREMOS LAS FUNCIONES DEL EJ4 EN VEZ DE ESTO
/*
Programa una nueva orden que recorra la jerarquía de subdirectorios existentes a partir de uno dado como
argumento y devuelva la cuenta de todos aquellos archivos regulares que tengan permiso de ejecución para el
"grupo" y para "otros". Además del nombre de los archivos encontrados, deberá devolver sus números de inodo
y la suma total de espacio ocupado por dichos archivos. El formato de la nueva orden será:
		$> ./buscar <pathname>
donde <pathname> especifica la ruta del directorio a partir del cual queremos que empiece a analizar la
estructura del árbol de subdirectorios. En caso de que no se le de argumento, tomará como punto de partida
el directorio actual.
*/
#include<sys/types.h>
#include<unistd.h>
#include<sys/stat.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>

/*
 - Resumen: Funcion auxiliar para la apertura del directorio.
 - Argumentos:
 	- argc		Numero de argumentos pasados al programa
 	- argv		Lista de argumentos pasados al programa
 	- pathname	Ruta del directorio que se abre ES MODIFICADO
 - Valor de retorno: Devuelve la estructura DIR del directorio abierto
*/
DIR *get_dir(int argc, char *argv[],char *pathname);

/*
 - Resumen: Muestra la informacion de un archivo
 - Argumentos:
 	- pathname	Ruta del archivo
 	- atributos	Estructura stat del archivo
 	- numbytes	Numero de bytes totales que ocupan los archivos del directorio ES MODIFICADO
 - Valor de retorno: 1 si el archivo tiene permiso x para grupo y otros
*/
int infofile(char *pathname,struct stat atributos,int *numbytes);

/*
 - Resumen: Muestra todos los archivos de un directorio (recursivo)
 - Argumentos:
 	- directory	Directorio del que se sacan todos los archivos
 	- pathname	Ruta del directorio
 	- exec		Numero de archivos con permiso x para grupo y otros
 	- numbytes	Tamaño en bytes que ocupan todos los archivos del directorio
*/
void showdir(DIR *directory,char *dirname,int *exec,int *numbytes);

int main (int argc, char *argv[]) {
	//Apertura del directorio
	char dirname[100];
	DIR *directorio = get_dir(argc,argv,dirname);
	printf("El directorio con el que trabajara el programa es %s\n",dirname);
	
	//Lectura de los archivos del directorio
	int exec = 0;
	int numbytes = 0;
	printf("Los i-nodos son:\n");
	showdir(directorio,dirname,&exec,&numbytes);
	
	//Mostrado de la informacion final
	printf("Existen %d archivos con permiso x para grupo y otros\n",exec);
	printf("El tamaño total ocupado por dichos archivos es %d bytes\n",numbytes);
	
	exit (EXIT_SUCCESS);
}

DIR *get_dir(int argc, char *argv[],char *pathname) {
	char currentdir[] = ".";
		DIR *directorio;
		if (argc>2) {
			printf("Error en el número de argumentos\n");
			exit (EXIT_FAILURE);
		} else if (argc==1) {
			directorio = opendir(currentdir);
			strcpy(pathname,currentdir);
		} else {
			directorio = opendir(argv[1]);
			strcpy(pathname,argv[1]);
		}
		
		return directorio;
}

int infofile(char *pathname,struct stat atributos,int *numbytes) {
	printf("%s %d\n",pathname,atributos.st_ino);
	numbytes += atributos.st_size;
	if (S_ISREG(atributos.st_mode) && (atributos.st_mode & 011)==011)
		return 1;
	else
		return 0;	
}

void showdir(DIR *directory,char *dirname,int *exec,int *numbytes) {
	struct dirent *archivo;
	while ((archivo=readdir(directory))!=NULL) {
		//Ignoramos archivos problematicos
		if (strcmp(archivo->d_name,".")!=0 && strcmp(archivo->d_name,"..")!=0) {
			//Obtenemos la ruta del fichero
			char pathname[300];
			strcpy(pathname,dirname);
			strcat(pathname,"/");
			strcat(pathname,archivo->d_name);
			
			//Comprobamos si es un directorio
			struct stat atributos;
			if (lstat(pathname,&atributos)==-1) {
				printf("Error %d en lstat\n");
				exit (EXIT_FAILURE);
			}
			if (S_ISDIR(atributos.st_mode)) {
				DIR *directorio = opendir(pathname);
				showdir(directorio,pathname,exec,numbytes);
				closedir(directorio);
			} else
				exec += infofile(pathname,atributos,numbytes);
		}
	}
	closedir(directory);
}
