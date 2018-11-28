#!/bin/bash

# Primer nivel de optimización
echo "EJECUCION CON PRIMER NIVEL DE OPTIMIZACIÓN"
gcc -m32 -g -O0 pcount.c -o pcount
for (( i=1; i<=20; i++ )); do echo "Número $i"; ./pcount >> resultados_o0.txt; done

# Segundo nivel de optimización
echo "EJECUCION CON SEGUNDO NIVEL DE OPTIMIZACIÓN"
gcc -m32 -g -O1 pcount.c -o pcount
for (( i=1; i<=20; i++ )); do echo "Número $i"; ./pcount >> resultados_o1.txt; done

# Tercer nivel de optimización
echo "EJECUCION CON TERCER NIVEL DE OPTIMIZACIÓN"
gcc -m32 -g -O2 pcount.c -o pcount
for (( i=1; i<=20; i++ )); do echo "Número $i"; ./pcount >> resultados_o2.txt; done
