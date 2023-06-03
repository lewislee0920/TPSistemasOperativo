#include "../include/filesystem.h"

int main(int argc, char *argv[])
{
	if(argc < 1) {
	   printf("Faltan parameters\n");
	   return EXIT_FAILURE;
	}
	char *path = strdup(argv[1]);

	iniciar_config(path);

    return EXIT_SUCCESS;
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


