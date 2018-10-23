#MAKEFILE DE LA PRACTICA 1 DE LA ASIGNATURA DE ESTRUCTURA DE COMPUTADORES

#Nombres de programas
S64US = suma64us
S64S = suma64s
M64 = media64
ALL = $(S64US) $(S64S) $(M64)

#Opciones de compilacion
LINKER = gcc
ASSEMBLER = as -g

#Construcción de los ejecutables
all: $(ALL)

#Suma sin signo
$(S64US): $(S64US).o
	$(LINKER) $< -o $@

$(S64US).o: $(S64US).s
	$(ASSEMBLER) $< -o $@

#Suma con signo
$(S64S): $(S64S).o
	$(LINKER) $< -o $@

$(S64S).o: $(S64S).s
	$(ASSEMBLER) $< -o $@

#Media de 32 valores
$(M64): $(M64).o
	$(LINKER) $< -o $@

$(M64).o: $(M64).s
	$(ASSEMBLER) $< -o $@

#Parametros extra
S64US: $(S64US)
	ddd $(S64US) &

S64S: $(S64S)
	ddd $(S64S) &

M64: $(M64)
	ddd $(M64) &

clean:
	rm -f *.o $(ALL)

help:
	@echo "-----------------PRACTICA1 ESTRUCTURA DE COMPUTADORES-----------------"
	@echo "Lista de parametros posibles:"
	@echo "		S64US		Compila la suma sin signo y la ejecuta en ddd"
	@echo "		S64S		Compila la suma con signo y la ejecuta en ddd"
	@echo "		M64		Compila la media y la ejecuta en ddd"
	@echo "		clean		Limpia la carpeta de ejecutables y objetos"
	@echo "		author		Muestra informacion sobre el autor"
	@echo "----------------------------------------------------------------------"

author:
	@echo "Practica realizada por Manuel Gachs Ballegeer (https://github.com/ManuelBelgicano)"
	@echo "Para la asignatura de Estructura de Computadores de la Universidad de Granada"
