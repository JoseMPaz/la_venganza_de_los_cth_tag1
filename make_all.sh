#!/bin/bash

echo "Inicio la creación de archivos intermedios de utils"
cd utils
make clean
make
cd ..
echo "Finalizo la creación de archivos intermedios de utils"

echo "Inicio la creación del ejecutable filesystem"
cd filesystem
make clean
make
cd ..
echo "Finalizo la creación del ejecutable filesystem"

echo "Inicio la creación del ejecutable memoria"
cd memoria
make clean
make
cd ..
echo "Finalizo la creación del ejecutable memoria"

echo "Inicio la creación del ejecutable cpu"
cd cpu
make clean
make
cd ..
echo "Finalizo la creación del ejecutable cpu"

echo "Inicio la creación del ejecutable kernel"
cd kernel
make clean
make
cd ..
echo "Finalizo la creación del ejecutable kernel"




