#!/bin/bash

# Compilar el código C
gcc ft_take_comm.c -o a.out

# Combinaciones válidas
valid_combinations=("xx" "xddx" "sxxsdd" "xxssddxx" "sxsdxdxx" "ssxdxdss" "dxxxxdsxxxxsdd" "dxdxsxsxdxdxsxsdxdxsxs")

# Combinaciones inválidas
invalid_combinations=("ss" "dd" "xdx" "xsx" "sxx" "dxx" "sdds" "dssd" "sssxxds" "xxdds s" "xddssxsdxdxs" "ddssddss")

echo "Probando combinaciones válidas:"
for combo in "${valid_combinations[@]}"; do
    resultado=$(./a.out "$combo")
    echo "Resultado: $resultado"
done

echo "Probando combinaciones inválidas:"
for combo in "${invalid_combinations[@]}"; do
    resultado=$(./a.out "$combo")
    echo "Resultado: $resultado"
done

# Eliminar el archivo compilado
rm a.out