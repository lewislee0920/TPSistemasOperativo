#ifndef GENERALIB_INCLUDE_GENERALLIB_H_
#define GENERALIB_INCLUDE_GENERALLIB_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <commons/log.h>
#include <commons/string.h>
#include <commons/collections/list.h>
#include <commons/collections/queue.h>
#include <commons/config.h>

int crear_conexion(char *ip, char* puerto);
void enviar_datos_consola(int socket, t_consola *consola);
void crear_buffer_operacion(t_operacion *operacion);
void setear_operacion(t_operacion *operacion, void *valor);
void *serializar_consola(t_consola *consola, int *size);
void *serializar_instrucciones(t_queue *instrucciones, int *size_cola);
void serializar_proceso_pcb(t_proceso_pcb *proceso_bloqueo, t_operacion *operacion);
void enviar_operacion(t_operacion *operacion, int socket_cliente);
void *serializar_operacion(t_operacion *operacion, int bytes);
void eliminar_operacion(t_operacion *operacion);
void enviar_handshake(int *socket, modulo modulo_solicitante);
char* obtener_nombre_modulo(modulo un_modulo);
int esperar_cliente(int socket_servidor);
int recibir_operacion(int socket_cliente);

typedef enum
{
   KERNEL,
   CPU,
   MEMORIA,
   FILESYSTEM
} modulo;

typedef struct
{
   codigo_operacion cod_op;
   t_buffer* buffer;
} t_operacion;

typedef struct
{
   int size;
   void* stream;
} t_buffer;

#endif
