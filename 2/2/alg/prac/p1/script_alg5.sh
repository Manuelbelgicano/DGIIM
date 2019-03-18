#!/bin/bash

g++ -O2 -o $1 $1.cpp

for ((i=0;i<=175000;i=i+7000)) do
	echo "Ejecución con valor $i"
	./$1 $i >> salida.dat
done

