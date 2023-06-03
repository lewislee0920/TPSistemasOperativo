#include "../include/filesystem.h"

int main(int argc, char *argv[])
{
	if(argc < 1) {
	   printf("Faltan parameters\n");
	   return EXIT_FAILURE;
	}
	char *path = strdup(argv[1]);

	iniciar_config(path);

	int socket_filesystem_serv = iniciar_servidor(config_filesystem.ip_filesystem,config_filesystem.puerto_escucha);
	conectar_con_memoria(socket_filesystem_serv);

    return EXIT_SUCCESS;
}

int conectar_con_memoria(int socket_filesystem_serv) {
    socket_memoria = crear_conexion(config_filesystem.ip_memoria,config_filesystem.puerto_memoria);
    log_info(logger,"Enviando HANDSHAKE a MEMORIA");
    enviar_handshake(&socket_memoria,FILESYSTEM);

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

    config_filesystem.ip_filesystem = strdup(config_get_string_value(config,"IP_FILESYSTEM"));
    config_filesystem.ip_memoria = strdup(config_get_string_value(config,"IP_MEMORIA"));
    config_filesystem.puerto_memoria = strdup(config_get_string_value(config,"PUERTO_MEMORIA"));
    config_filesystem.puerto_escucha = strdup(config_get_string_value(config,"PUERTO_ESCUCHA"));
    config_filesystem.path_superbloque = strdup(config_get_string_value(config,"PATH_SUPERBLOQUE"));
    config_filesystem.path_bitmap = strdup(config_get_string_value(config,"PATH_BITMAP"));
    config_filesystem.path_bloques = strdup(config_get_string_value(config,"PATH_BLOQUES"));
    config_filesystem.path_fcb = strdup(config_get_string_value(config,"PATH_FCB"));
    config_filesystem.retardo_acceso_bloque = strdup(config_get_int_value(config,"RETARDO_ACCESO_BLOQUE"));

}


