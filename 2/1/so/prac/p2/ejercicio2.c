#include<sys/types.h>	
#include<unistd.h>		
#include<sys/stat.h>		
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
/*
Realiza un programa en C utilizando las llamadas al sistema necesarias que acepte como entrada: 
• Un argumento que representa el 'pathname' de un directorio.
• Otro argumento que es un número octal de 4 dígitos (similar al que se puede utilizar para cambiar los permisos en la llamada al sistema 
chmod). Para convertir este argumento tipo cadena a un tipo numérico puedes utilizar la función strtol. Consulta el manual en línea para conocer sus argumentos.
El programa tiene que usar el número octal indicado en el segundo argumento para cambiar los permisos  de  todos  los archivos  que se  encuentren  en el   directorio indicado  en  el  primer argumento.
El programa debe proporcionar en la salida estándar una línea para cada archivo del directorio que esté formada por:
<nombre_de_archivo> : <permisos_antiguos> <permisos_nuevos>
Si no se pueden cambiar los permisos de un determinado archivo se debe especificar la siguiente información en la línea de salida:
<nombre_de_archivo> : <errno> <permisos_antiguos>
*/
void sintaxis() {
	printf("USO DEL PROGRAMA:\nFormato de argumentos: ejercicio2 [pathname] [número_en_octal]\n");
	printf("- [pathname]: Ruta de un directorio.\n- [número_en_octal]: Número en octal para cambiar los permisos.\n");
}

int main(int argc,char *argv[]) {
	if (argc!=3) {
		printf("Error en el número de argumentos\n");
		sintaxis();
		exit(EXIT_FAILURE);
	}
	
	//Asignación de valores iniciales
	char pathname[300];
	int perm = strtol(argv[2],NULL,8);
	if (perm==0) {
		printf("Error en el argumento [número_en_octal]\n");
		sintaxis();
		exit(EXIT_FAILURE);
	}
	DIR *directorio = opendir(argv[1]); 
	if (directorio==NULL) {
		printf("Error %d en [pathname]",errno);
		sintaxis();
		exit(EXIT_FAILURE);
	}
	else
		printf("Abriendo directorio...\n");
	
	//Acceso a los archivos y cambio de permisos
	struct dirent *archivo;
	struct stat atributos;
	while ((archivo=readdir(directorio))!=NULL) {
		//Ignoramos los casos de los archivos "." y ".."
		if (strcmp(archivo->d_name,".")!=0 && strcmp(archivo->d_name,"..")!=0) {
			//Conseguimos la ruta completa del archivo
			strcpy(pathname,argv[1]);
			strcat(pathname,"/");
			strcat(pathname,archivo->d_name);
			printf("Archivo %s\n",pathname);
		
			//Conseguimos los atributos del archivo
			if (stat(pathname,&atributos)==-1) {
				printf("Error en el acceso a los atributos del archivo %s\n",archivo->d_name);
				exit(EXIT_FAILURE);
			}
			
			//Mostramos permisos antiguos y los cambiamos
			printf("Permisos antiguos: %d\n",atributos.st_mode);
			int aux = chmod(pathname,perm);
			if (aux==-1)
				printf("Error en el cambio de permisos\n");
			else  {
				stat(pathname,&atributos);
				printf("Nuevos permisos: %d\n",atributos.st_mode);
			}
		}
						
	}
	
	//Fin del programa
	closedir(directorio);
	printf("Cerrando directorio...\n");
	exit(EXIT_SUCCESS);
}
