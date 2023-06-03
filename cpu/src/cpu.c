#include "../include/cpu.h"

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

	config_cpu.ip_cpu = strdup(config_get_string_value(config,"IP_CPU"));
	config_cpu.retardo_instruccion = strdup(config_get_int_value(config,"RETARDO_INSTRUCCION"));
	config_cpu.ip_memoria = strdup(config_get_string_value(config,"IP_MEMORIA"));
	config_cpu.puerto_memoria = strdup(config_get_string_value(config,"PUERTO_MEMORIA"));
	config_cpu.puerto_escucha = strdup(config_get_string_value(config,"PUERTO_ESCUCHA"));
	config_cpu.tam_max_segmento = strdup(config_get_int_value(config,"TAM_MAX_SEGMENTO"));
}

