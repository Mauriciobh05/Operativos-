##############################################################
#                Pontificia Universidad Javeriana
#
# Autor: Mauricio Beltran Huertas 
# Fichero: Automatización de Compilación con OpenMP
##############################################################

CC = gcc

CFLAGS = -fopenmp -lm

SRC = lab01.c lab02.c lab03.c lab04.c lab05.c lab06.c

EXEC = $(SRC:.c=)

all: $(EXEC)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXEC)
