##############################################################
#              Pontificia Universidad Javeriana
#
# Autor: Mauricio Beltrán Huertas
# Fecha: 05 noviembre 2025
# Clase: Sistemas Operativos
# Descripción: Automatiza la compilación de los laboratorios
#               usando OpenMP.
##############################################################

# Compilador
CC = gcc

# Flags de compilación OpenMP y librería matemática
CFLAGS = -fopenmp -lm

# Archivos fuente
SRC = lab01.c lab02.c lab03.c lab04.c lab05.c lab06.c

# Ejecutables generados 
EXEC = $(SRC:.c=)

#  compila todos los laboratorios
all: $(EXEC)

# compila cada archivo individualmente
%: %.c
	$(CC) $(CFLAGS) $< -o $@

# elimina los ejecutables generados
clean:
	rm -f $(EXEC)

