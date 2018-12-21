#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SIZE 100
char estanoeslacontrasenia[] = "porfavor\n";

void boom() {
	printf("     _.-^^---....,,--\n");
	printf(" _--                  --_\n");
	printf("<                        >)\n");
	printf("|                         |\n");
	printf(" \\._                   _./\n");
	printf("    ```--. . , ; .--'''\n");
	printf("          | |   |\n");
	printf("       .-=||  | |=-.\n");
	printf("       `-=#$%&%$#=-'\n");
	printf("          | ;  :|\n");
	printf(" _____.,-#%&$@%#&#~,._____\n");
	printf("_____EXPLOTO LA BOMBA_____\n");
	exit(EXIT_FAILURE);
}

void defused() {
	printf("_____________________________________\n");
	printf("ENHORABUENA, DESACTIVASTE LA BOMBA!!!\n");
	printf("_____________________________________\n");
	exit(EXIT_SUCCESS);
}

int main () {
	char pass[SIZE];
	int passnum;
	char ans[] = "no\n";
	int contador = 0;

	printf("¿Quieres desactivar la bomba?\n");
	fgets(pass,SIZE,stdin);
	if (strcmp(pass,ans)!=0)
		boom();
	
	printf("¿Quieres que explote?\n");
	do {
		contador++;
		fgets(pass,SIZE,stdin);
		printf("\r");
	} while (strcmp(pass,estanoeslacontrasenia)!=0 && contador<10);
	if (contador>=10)
		boom();

	printf("Introduce el codigo:\n");
	scanf("%i",&passnum);
	if (passnum==contador)
		defused();
	else
		boom();
}
