F :=

all: help exec

exec:
	@echo "Compilando..."
	@g++ -Wall $(F).cpp -o test
	@echo "`tput bold`EJECUTANDO:`tput sgr0`"
	@./test

clean:
	@rm test

help:
	@echo "`tput bold`Forma de uso del makefile:`tput sgr0` make F=<nombre_del_ejercicio>"
