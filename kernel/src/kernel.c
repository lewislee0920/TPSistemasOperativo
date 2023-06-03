#include "../include/kernel.h"

int main(int argc, char *argv[])
{
	if(argc < 1) {
	   printf("Faltan parameters\n");
	   return EXIT_FAILURE;
	}
	char *path = strdup(argv[1]);

	iniciar_config(path);
	conexion();

    return EXIT_SUCCESS;
}

void conexion(void)
{
    int socket_kernel_serv = iniciar_servidor(config_kernel.ip_kernel,config_kernel.puerto_escucha);
    log_warning(un_logger, "Inicializando modulo KERNEL ... ");

    int socket_proceso = 0;

    conectar_con_cpu(socket_kernel_serv);
    conectar_con_memoria(socket_kernel_serv);
    conectar_con_filesystem(socket_kernel_serv);

    log_warning(un_logger, "KERNEL a la espera de procesos ... ");
}

int conectar_con_cpu(int socket_kernel_serv)
{
    socket_cpu = crear_conexion(config_kernel.ip_cpu, config_kernel.puerto_cpu);
    log_info(logger, "Enviando HANDSHAKE a CPU \n");
    enviar_handshake(&socket_cpu, KERNEL);

    return esperar_handshake(&socket_cpu, confirmar_modulo);
}

int conectar_con_memoria(int socket_kernel_serv)
{
    socket_memoria = crear_conexion(config_kernel.ip_memoria,config_kernel.puerto_memoria);
    log_info(logger,"Enviando HANDSHAKE a MEMORIA");
    enviar_handshake(&socket_memoria,KERNEL);

    return esperar_handshake(&socket_memoria,confirmar_modulo);
}

int conectar_con_filesystem(int socket_kernel_serv)
{
    socket_filesystem = crear_conexion(config_kernel.ip_filesystem, config_kernel.puerto_cpu);
    log_info(logger, "Enviando HANDSHAKE a CPU \n");
    enviar_handshake(&socket_filesystem, KERNEL);

    return esperar_handshake(&socket_filesystem, confirmar_modulo);
}

void confirmar_modulo(int *socket, modulo un_modulo) {
    if(un_modulo == CPU) {
       log_info(logger, "Handshake exitoso");
    }
    else if(un_modulo == MEMORIA) {
       log_info(logger,"Handshake exitoso");
    }
    else if(un_modulo == FILESYSTEM) {
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

    config_kernel.ip_kernel = strdup(config_get_string_value(config,"IP_KERNEL"));
    config_kernel.ip_memoria = strdup(config_get_string_value(config,"IP_MEMORIA"));
    config_kernel.puerto_memoria = strdup(config_get_string_value(config,"PUERTO_MEMORIA"));
    config_kernel.ip_filesystem = strdup(config_get_string_value(config,"IP_FILESYSTEM"));
    config_kernel.puerto_filesystem = strdup(config_get_string_value(config,"PUERTO_FILESYSTEM"));
    config_kernel.ip_cpu = strdup(config_get_string_value(config,"IP_CPU"));
    config_kernel.puerto_cpu = strdup(config_get_string_value(config,"PUERTO_CPU"));
    config_kernel.puerto_escucha = strdup(config_get_string_value(config,"PUERTO_ESCUCHA"));
    config_kernel.algoritmo_planificacion = strdup(config_get_string_value(config,"ALGORITMO_PLANIFICACION"));
    config_kernel.estimacion_inicial = strdup(config_get_int_value(config,"ESTIMACION_INICIAL"));
    config_kernel.hrrn_alfa = strdup(config_get_double_value(config,"HRRN_ALFA"));
    config_kernel.grado_max_multiprogramacion = strdup(config_get_int_value(config,"GRADO_MAX_PROGRAMACION"));
    config_kernel.recursos = strdup(config_get_array_value(config,"RECURSOS"));
    config_kernel.instancias_recursos = strdup(config_get_array_value(config,"INSTANCIAS_RECURSOS"));

}
