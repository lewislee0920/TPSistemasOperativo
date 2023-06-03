#include "../../include/general/generalLib.h"

int crear_conexion(char *ip, char* puerto) {
	struct addrinfo hints;
	struct addrinfo *server_info;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(ip, puerto, &hints, &server_info);

	int socket_cliente = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);
	int estado_conexion = connect(socket_cliente, server_info->ai_addr, server_info->ai_addrlen);
	if(estado_conexion == -1) {
		return false;
	}
	freeaddrinfo(server_info);

	return socket_cliente;
}

void enviar_datos_consola(int socket, t_consola *consola) {
    t_operacion *operacion = crear_operacion(T_CONSOLA);
    setear_operacion(operacion, consola);
    enviar_operacion(operacion, socket);
    eliminar_operacion(operacion);
}

t_operacion *crear_operacion(codigo_operacion cod_op) {
	t_operacion *operacion = malloc(sizeof(t_operacion));
    operacion->cod_op = cod_op;
    crear_buffer_operacion(operacion);
	return operacion;
}

void crear_buffer_operacion(t_operacion *operacion) {
    operacion->buffer = malloc(sizeof(t_buffer));
    operacion->buffer->size = 0;
    operacion->buffer->stream = NULL;
}

void setear_operacion(t_operacion *operacion, void *valor) {
    int op_code = operacion->cod_op;
    int size;
    void *stream;

    switch (op_code) {
		case T_CONSOLA:
            stream = serializar_consola((t_consola *)valor, &size);
            operacion->buffer->size = size;
            operacion->buffer->stream = stream;
            break;
		case INICIO_PROCESO:
            size = sizeof(int32_t) + sizeof(unsigned int) + sizeof(int);
            stream = malloc(size);
            memcpy(stream, valor, size);
            operacion->buffer->size = size;
            operacion->buffer->stream = stream;
			break;
        case PCB:
		case BLOQUEO:
		case FIN_PROCESO:
			serializar_proceso_pcb((t_proceso_pcb *)valor,operacion);
			break;
		case INTERRUPCION:
		case FIN_PROCESO_MEMORIA:
		case SUSPENSION_PROCESO:
			size = sizeof(int);
			stream = malloc(size);
			memcpy(stream, valor, size);
			operacion->buffer->size = size;
            operacion->buffer->stream = stream;
			break;
        case PRIMERA_SOLICITUD:
        case SEGUNDA_SOLICITUD:
        case TERCERA_SOLICITUD:
            size = sizeof(int32_t) * 3 + sizeof(unsigned int)*2 + sizeof(int)*2 + sizeof(uint32_t);
            stream = malloc(size);
            memcpy(stream, valor, size);
            operacion->buffer->size = size;
            operacion->buffer->stream = stream;
            break;
    }
    return;
}

void *serializar_consola(t_consola *consola, int *size) {
    int size_cola = 0, desplazamiento = 0;
    void *instrucciones_serializadas = serializar_instrucciones(consola->instrucciones, &size_cola);
    *size = size_cola + 2 * sizeof(int);
    void *stream = malloc(*size);
    memcpy(stream, &(consola->tamanio),  sizeof(int));
    desplazamiento+=sizeof(int);
    memcpy(stream + desplazamiento, &size_cola,  sizeof(int));
    desplazamiento+=sizeof(int);
    memcpy(stream + desplazamiento, instrucciones_serializadas, size_cola);
    free(instrucciones_serializadas);

    return stream;
}

void *serializar_instrucciones(t_queue *instrucciones, int *size_cola) {
    *size_cola = queue_size(instrucciones) * 3 * sizeof(int);
    int desplazamiento = 0;
    void *stream = malloc(*size_cola);
    t_instruccion *instruccion;
    while (!queue_is_empty(instrucciones)) {
        instruccion = (t_instruccion *) queue_pop(instrucciones);
        memcpy(stream + desplazamiento, &(instruccion->instruc), sizeof(int));
        desplazamiento+= sizeof(int);
        memcpy(stream + desplazamiento, &(instruccion->parametro1), sizeof(int));
        desplazamiento+= sizeof(int);
        memcpy(stream + desplazamiento, &(instruccion->parametro2), sizeof(int));
        desplazamiento+= sizeof(int);
        free(instruccion);
    }

    return stream;
}

void serializar_proceso_pcb(t_proceso_pcb *proceso_bloqueo, t_operacion *operacion)
{
    int size_pcb;
    void *pcb_serializado = serializar_pcb(proceso_bloqueo->pcb,&size_pcb);
    operacion->buffer->size = sizeof(int) + size_pcb;
    operacion->buffer->stream = malloc(operacion->buffer->size);
    memcpy(operacion->buffer->stream, pcb_serializado, size_pcb);
    memcpy(operacion->buffer->stream + size_pcb,&(proceso_bloqueo->tiempo_bloqueo),sizeof(int));

    free(pcb_serializado);
}

void enviar_operacion(t_operacion *operacion, int socket_cliente) {
	int bytes;
	void* a_enviar;
	bytes = operacion->buffer->size + 2*sizeof(int);
	a_enviar = serializar_operacion(operacion, bytes);
	send(socket_cliente, a_enviar, bytes, 0);
	free(a_enviar);
}

void *serializar_operacion(t_operacion *operacion, int bytes) {
	void * magic = malloc(bytes);
	int desplazamiento = 0;

	memcpy(magic + desplazamiento, &(operacion->cod_op), sizeof(int));
	desplazamiento+= sizeof(int);
	memcpy(magic + desplazamiento, &(operacion->buffer->size), sizeof(int));
	desplazamiento+= sizeof(int);
	memcpy(magic + desplazamiento, operacion->buffer->stream, operacion->buffer->size);

	return magic;
}

void eliminar_operacion(t_operacion *operacion) {
	free(operacion->buffer->stream);
	free(operacion->buffer);
	free(operacion);
}

void enviar_handshake(int *socket, modulo modulo_solicitante) {
    void *buffer = malloc(sizeof(int)*2);
    codigo_operacion handshake = HANDSHAKE;
    memcpy(buffer, &handshake, sizeof(int));
    memcpy(buffer + sizeof(int), &modulo_solicitante, sizeof(int));
    send(*socket, buffer, sizeof(int)*2, 0);
    free(buffer);
}

char* obtener_nombre_modulo(modulo un_modulo) {
    switch (un_modulo)
    {
        case CPU:
            return "CPU";
        case MEMORIA:
            return "MEMORIA";
        case FILESYSTEM:
        	return "FILESYSTEM"
        default:
            return "ERROR";
    }
}

int esperar_cliente(int socket_servidor)
{
	struct sockaddr_in dir_cliente;
	int tam_direccion = sizeof(struct sockaddr_in);

	int socket_cliente = accept(socket_servidor,NULL,NULL);

	return socket_cliente;
}

int recibir_operacion(int socket_cliente)
{
	int cod_op;
	if(recv(socket_cliente, &cod_op, sizeof(int), MSG_WAITALL) != 0)
		return cod_op;
	else
	{
		close(socket_cliente);
		return -1;
	}
}

