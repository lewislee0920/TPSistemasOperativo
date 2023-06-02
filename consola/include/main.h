#ifndef CONSOLA_INCLUDE_MAIN_H_
#define CONSOLA_INCLUDE_MAIN_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <commons/string.h>
#include <general/generalLib.h>

typedef struct t_config_consola
{
    char* ip_kernel;
    char* puerto_kernel;
} t_config_consola;

typedef struct t_instruccion{
    instruccion instruc;
    int parametro1;
    int parametro2;
    int parametro3;
} t_instruccion;

instruccion devolver_enum_instruccion(char* instruccion);
void leer_configuracion();
void conectar_a_kernel();
void enviar_informacion(char *tamanio);
void esperar_mensaje_finalizacion();
void liberar_memoria_y_conexiones();

t_queue *cola_instrucciones;
t_config_consola config_consola;
int conexion_kernel;

#endif
