#ifndef CPU_INCLUDE_CPU_H_
#define CPU_INCLUDE_CPU_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <commons/string.h>
#include <general/generalLib.h>

typedef struct t_config_cpu
{
	char* ip_cpu;
	int retardo_instruccion;
    char* ip_memoria;
    char* puerto_memoria;
    char* puerto_escucha;
    int tam_max_segmento;
} t_config_cpu;

t_config_cpu config_cpu;
t_log *logger;
t_config *config;

int conectar_con_memoria(int socket_cpu_serv);
void iniciar_config(char *path_config);
void confirmar_modulo(int *socket, modulo un_modulo);

int socket_memoria;

#endif
