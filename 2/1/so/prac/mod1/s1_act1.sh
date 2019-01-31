#!/bin/bash

echo "Descomprimiendo archivos..."
cp *.gz /tmp
sudo gunzip /tmp/*.gz
cd /tmp/
chmod +x *
echo "Iniciando..."
./kernel32-3.0.4 ubda=./Fedora14-x86-root_fs mem=1024m
