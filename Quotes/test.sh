#!/bin/bash

# Compilar el código C
gcc ft_take_comm.c ft_quotes.c ft_utils_quotes.c -o a.out

valid_combinations=(   "\"\"\"ls\"\"\$asd\""
                    "\"\"\"echo 'Hello'\"\"\$variable\""
                    "\"\"\"command1\"\" \$variable \"\"command2\"\""
                    "\"\"\"command1\"\"\$variable\"\"command2\"\""
                    "\"\"\"command with spaces\"\"\$variable\"")


# echo "Probando combinaciones válidas:"
echo "${valid_combinations}"
for combo in "${valid_combinations[@]}"; do
    resultado=$(./a.out "$combo")
    echo "Resultado: $resultado"
done

# echo "Probando combinaciones inválidas:"
for combo in "${invalid_combinations[@]}"; do
    resultado=$(./a.out "$combo")
    echo "Resultado: $resultado"
done

# Eliminar el archivo compilado
rm a.out