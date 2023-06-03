#include "../include/memoria.h"

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

	config_memoria.ip_memoria = strdup(config_get_string_value(config,"IP_MEMORIA"));
	config_memoria.puerto_escucha = strdup(config_get_string_value(config,"PUERTO_ESCUCHA"));
	config_memoria.tam_memoria = strdup(config_get_int_value(config,"TAM_MEMORIA"));
	config_memoria.tam_segmento = strdup(config_get_int_value(config,"TAM_SEGMENTO_0"));
	config_memoria.cant_segmento = strdup(config_get_int_value(config,"CANT_SEGMENTOS"));
	config_memoria.retardo_memoria = strdup(config_get_int_value(config,"RETARDO_MEMORIA"));
	config_memoria.retardo_compactacion = strdup(config_get_int_value(config,"RETARDO_COMPACTACION"));
	config_memoria.algoritmo_asignacion = strdup(config_get_string_value(config,"ALGORITMO_ASIGNACION"));

}

#endif
