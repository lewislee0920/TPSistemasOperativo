#ifndef MEMORIA_INCLUDE_MEMORIA_H_
#define MEMORIA_INCLUDE_MEMORIA_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <commons/string.h>
#include <general/generalLib.h>

typedef struct t_config_memoria
{
	char* puerto_escucha;
	int tam_memoria;
	int tam_segmento;
	int cant_segmento;
	int retardo_memoria;
	int retardo_compactacion;
    char* algoritmo_asignacion;
} t_config_memoria;

t_config_memoria config_memoria;
void iniciar_config(char *path_config);

#endif


