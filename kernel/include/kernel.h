#ifndef KERNEL_INCLUDE_KERNEL_H_
#define KERNEL_INCLUDE_KERNEL_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <commons/string.h>
#include <general/generalLib.h>

typedef struct t_config_kernel
{
	char* ip_kernel;
    char* ip_memoria;
    char* puerto_memoria;
    char* ip_filesystem;
    char* puerto_filesystem;
    char* ip_cpu;
    char* puerto_cpu;
    char* puerto_escucha;
    char* algoritmo_planificacion;
    int estimacion_inicial;
    double hrrn_alfa;
    int grado_max_multiprogramacion;
    char*[] recursos;
    int[] instancias_recursos;
} t_config_kernel;

void conexion(void);
int conectar_con_memoria;
int conectar_con_cpu;
int conectar_con_filesystem;
void confirmar_modulo(int *socket, modulo un_modulo);
void iniciar_config(char *path_config);

t_config_kernel config_kernel;
t_log *logger;
t_config *config;

int socket_cpu;
int socket_filesystem;
int socket_memoria;

#endif
