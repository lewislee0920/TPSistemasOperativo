#include "../include/kernel.h"

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
