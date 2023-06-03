#include "../include/cpu.h"

int main(int argc, char *argv[])
{
	if(argc < 1) {
	   printf("Faltan parameters\n");
	   return EXIT_FAILURE;
	}
	char *path = strdup(argv[1]);

	iniciar_config(path);

	int socket_cpu_serv = iniciar_servidor(config_cpu.ip_cpu, config_cpu.puerto_escucha);
	conectar_con_memoria(socket_cpu_serv);

	return EXIT_SUCCESS;
}

int conectar_con_memoria(int socket_cpu_serv)
{
    socket_memoria = crear_conexion(config_cpu.ip_memoria,config_cpu.puerto_memoria);
    log_info(logger,"Enviando HANDSHAKE a MEMORIA");
    enviar_handshake(&socket_memoria,CPU);

    return esperar_handshake(&socket_memoria,confirmar_modulo);
}

void confirmar_modulo(int *socket, modulo un_modulo) {
    else if(un_modulo == MEMORIA) {
       log_info(logger,"Handshake exitoso");
    }
    else {
       log_error(logger,"Fallo Handshake",
       obtener_nombre_modulo(un_modulo));
       exit(EXIT_FAILURE);
    }
}

void iniciar_config(char *path_config) {

	config = config_create(path_config);

	config_cpu.ip_cpu = strdup(config_get_string_value(config,"IP_CPU"));
	config_cpu.retardo_instruccion = strdup(config_get_int_value(config,"RETARDO_INSTRUCCION"));
	config_cpu.ip_memoria = strdup(config_get_string_value(config,"IP_MEMORIA"));
	config_cpu.puerto_memoria = strdup(config_get_string_value(config,"PUERTO_MEMORIA"));
	config_cpu.puerto_escucha = strdup(config_get_string_value(config,"PUERTO_ESCUCHA"));
	config_cpu.tam_max_segmento = strdup(config_get_int_value(config,"TAM_MAX_SEGMENTO"));
}

