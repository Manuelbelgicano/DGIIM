/*-----Sección de Declaraciones --------------*/ 
%{
#include <stdio.h>
#include <ctype.h>
#include <string.h>
FILE * salida;
unsigned MAX_CHAR = 80;
unsigned num_char;
unsigned lin_cor;
unsigned ref_elim;
unsigned p_tilde;
char tildes[5000][100];
void escribe_palabra(FILE * fichero,char * datos);
void anade_palabra_tilde(char * palabra);
%}   

/*-----Sección de Reglas ----------------*/ 
%%
([a-zñA-Z])*[áéíóú]([a-z]|ñ)*   {anade_palabra_tilde(yytext);REJECT;}
(,|\.)[0-9]+        {ref_elim++;unput(yytext[0]);}
"[cita requerida]"  {ref_elim++;}
[^ \t\n\.,:]+       {
                    num_char += yyleng;
                    char word_buffer[100];
                    if (num_char<MAX_CHAR) { // Si la palabra cabe en la línea
                        sprintf(word_buffer,"%s",yytext);
                    } else { // La palabra no cabe en la línea
                        num_char = yyleng;
                        lin_cor++;
                        sprintf(word_buffer,"\n%s",yytext);
                    }
                    escribe_palabra(salida,word_buffer);
                    }
(\n\n)+             {num_char = 0;escribe_palabra(salida,"\n");}
(" "|\n|\t)+(" ")*      {
                        num_char++;
                        register int c;
                        escribe_palabra(salida," ");
                        while ((c = input())==' '); // Se come todos los espacios que vengan después
                        if (c!=' ')
                            unput(c);
                        }
\.|,|:              {num_char++;escribe_palabra(salida,yytext);}

%%   
/*-----Sección de Procedimientos --------*/
int main (int argc, char *argv[]) {
    if (argc!=3) {
        printf("No se ha proporcionado ningún fichero...\n");
        printf("Formato:\n\t./wikipedia archivo_entrada.txt archivo_salida.txt\n");
        exit(-1);
    }   
    else {
        yyin = fopen(argv[1],"rt");
        if (yyin==NULL) {
            printf("El fichero %s no se puede abrir\n", argv[1]);
            exit(-1);
        } 
        salida = fopen(argv[2],"w");
    }

    num_char = 0;
    lin_cor = 0;
    ref_elim = 0;
    p_tilde = 0;
    
    yylexs();

    printf("\nLíneas salida: %d\n",lin_cor);
    printf("Referencias eliminadas: %d\n",ref_elim);
    printf("Palabras con tilde: %d\n\n",p_tilde);

    exit(0);
}

void escribe_palabra(FILE * fichero,char * datos) {
    fprintf(fichero,"%s",datos);
}

void anade_palabra_tilde(char * palabra) {
    char * copia = strdup(palabra);
    for (int i=0;i<p_tilde;i++) {
        copia[0] = tolower(copia[0]);
        if (strcmp(tildes[i],copia)==0)
            return;
        copia[0] = toupper(copia[0]);
        if (strcmp(tildes[i],copia)==0)
            return;
    }
    sprintf(tildes[p_tilde],"%s",palabra);
    p_tilde++;
}