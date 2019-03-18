#!/bin/bash

g++ -O2 -o $1 $2

if [ "$1" == "burbuja" ]; then
	for ((i=0;i<15;i++)) do
		./$1 salida$i.dat 400 800 1200 1600 2000 2400 2800 3200 3600 4000 4400 4800 5200 5600 6000 6400 6800 7200 7600 8000 8400 8800 9200 9600 10000
	done
else
	for ((i=5;i<31;i++)) do
		echo "Ejecución con valor $i"
		./$1 $i >> salida.dat
	done
fi
