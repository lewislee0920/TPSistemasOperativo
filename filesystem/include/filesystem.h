#ifndef FILESYSTEM_INCLUDE_FILESYSTEM_H_
#define FILESYSTEM_INCLUDE_FILESYSTEM_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <commons/string.h>
#include <general/generalLib.h>

typedef struct t_config_filesystem
{
	char* ip_filesystem;
    char* ip_memoria;
    char* puerto_memoria;
    char* puerto_escucha;
    char* path_superbloque;
    char* path_bitmap;
    char* path_bloques;
    char* path_fcb;
    int retardo_acceso_bloque;
} t_config_filesystem;

t_config_filesystem config_filesystem;
t_config *config;

void iniciar_config(char *path_config);

#endif
