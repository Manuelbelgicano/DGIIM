/*
Implementa un programa que realice la siguiente funcionalidad. El programa
acepta como argumento el nombre de un archivo (pathname), lo abre y lo lee en bloques de
tamaño 80 Bytes, y crea un nuevo archivo de salida, salida.txt, en el que debe aparecer la
siguiente información:
Bloque 1
// Aquí van los primeros 80 Bytes del archivo pasado como argumento.
Bloque 2
// Aquí van los siguientes 80 Bytes del archivo pasado como argumento.
...
*/

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>

int main (int argc, char *argv[]) {
	//Comprobacion inicial
	if (argc<2) {
		printf("Error en el numero de argumentos\n");
		exit (EXIT_FAILURE);
	}
	//Apertura del primer archivo
	int fd_in = open(argv[1],O_RDONLY);
	if (fd_in==-1) {
		printf("Error %d en la operacion open del archivo de entrada\n",errno);
		exit (EXIT_FAILURE);
	}
	
	//Creacion segundo archivo
	char filename[] = "salida.txt";
	int fd_out = open(filename,O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR);
	if (fd_out==-1) {
		printf("Error %d en la operacion open del archivo de salida\n",errno);
		exit (EXIT_FAILURE);
	}
	
	//Tamaño del archivo y numero de bloques
	int filesize = lseek(fd_in,0,SEEK_END);
	if (filesize<0) {
		printf("Error %d en la operacion lseek (filesize)\n",errno);
		exit (EXIT_FAILURE);
	}
	
//-----------------Escritura de los datos en el archivo de salida-----------------
	//Tamaño del archivo
	int ini_file = lseek(fd_in,0,SEEK_SET);
	if (ini_file!=0) {
		printf("Error %d en la operacion lseek (ini_file)\n",errno);
		exit (EXIT_FAILURE);
	}
	
	char buf[1];
	char message[80];
	int block_count = 1;
	int char_count = 1;
	int aux = 0;
	int is_read;
	int is_written;
	int m_size;
	
	//Numero de bloques
	m_size = sprintf(message,"\nEl numero de bloques es %d:\n",(filesize/80));
	is_written = write(fd_out,message,m_size+1);
	if (is_written==-1) {
		printf("Error %d en la escritura del numero de bloques",errno);
		exit (EXIT_FAILURE);
	}
	
	//Primer bloque
	m_size = sprintf(message,"\nBloque %d:\n",block_count);
	is_written = write(fd_out,message,m_size+1);
	if (is_written==-1) {
		printf("Error %d en la escritura del bloque %d",errno,block_count);
		exit (EXIT_FAILURE);
	}
	else
		block_count++;
	
	//Resto de bloques
	while (aux<filesize) {
		if (char_count%80==0) {
			m_size = sprintf(message,"\nBloque %d:\n",block_count);
			char_count = 1;
			block_count++;
			is_written = write(fd_out,message,m_size+1);
			if (is_written==-1) {
				printf("Error %d en la escritura del bloque %d",errno,block_count);
				exit (EXIT_FAILURE);
			}
		} else {
			is_read = read(fd_in,buf,1);
			if (is_read==-1) {
				printf("Error %d en la lectura del %d-esimo bloque",errno,block_count);
				exit (EXIT_FAILURE);
			}
			is_written = write(fd_out,buf,1);
			if (is_written==-1) {
				printf("Error %d en la escritura en el bloque %d",errno,block_count);
				exit (EXIT_FAILURE);
			}
			char_count++;
			aux++;
		}
	}
	
	//Fin del programa
	close(fd_in);
	close(fd_out);
	exit (EXIT_SUCCESS);
}
