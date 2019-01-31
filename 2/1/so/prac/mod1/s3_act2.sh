#!/bin/bash

b=0

for i in `seq 1 $1` do
	a=$i-347
	b=$b+a++
done

echo "a=$a"
echo "b=$b"
echo "La variable es: $1"
