#!/bin/bash

b=0

for i in 100000 do
	a=`expr $i - 347`
	b=`expr $b + 1`
done

echo "a=$a"
echo "b=$b"
echo "La variable es: $1"
