#include "../include/main.h"

#define MAX_LEN 256

int main(int argc, char *argv[])
{
    if(argc < 3) {
        printf("Faltan parametros\n");
        return EXIT_FAILURE;
    }

    FILE* archivo;
    char *path = strdup(argv[1]);
    archivo = fopen(path, "r");
    if (archivo == NULL) {
    	printf("No se pudo leer el archivo\n");
        return 1;
    }
    cola_instrucciones = queue_create();
    t_instruccion *una_instruccion = NULL;
    char *buffer = malloc(sizeof(MAX_LEN) + 90);
    char **aux;

    leer_configuracion();

    while (fgets(buffer, MAX_LEN, archivo)) {
        buffer[strcspn(buffer, "\n")] = 0;
        aux = string_split(buffer, " ");

        una_instruccion = malloc(sizeof(t_instruccion));
        una_instruccion->instruc = devolver_enum_instruccion(aux[0]);

        if(una_instruccion->instruc == F_READ || una_instruccion->instruc == F_WRITE){
        	una_instruccion->parametro1 = atoi(aux[1]);
            una_instruccion->parametro2 = atoi(aux[2]);
            una_instruccion->parametro3 = atoi(aux[3]);
            free(aux[1]);
            free(aux[2]);
            free(aux[3]);
        }

        if(una_instruccion->instruc == SET || una_instruccion->instruc == MOV_IN || una_instruccion->instruc == MOV_OUT || una_instruccion->instruc == F_TRUNCATE || una_instruccion->instruc == F_SEEK || una_instruccion->instruc == CREATE_SEGMENT){
		    una_instruccion->parametro1 = atoi(aux[1]);
            una_instruccion->parametro2 = atoi(aux[2]);
            una_instruccion->parametro3 = 0;
            free(aux[1]);
            free(aux[2]);
	    }

        if(una_instruccion->instruc == I/O || una_instruccion->instruc == WAIT || una_instruccion->instruc == SIGNAL || una_instruccion->instruc == F_OPEN || una_instruccion->instruc == F_CLOSE || una_instruccion->instruc == DELETE_SEGMENT){
            una_instruccion->parametro1 = atoi(aux[1]);
            una_instruccion->parametro2 = 0;
            una_instruccion->parametro3 = 0;
            free(aux[1]);
        }

        if(una_instruccion->instruc == EXIT || una_instruccion->instruc == YIELD                                 ) {
            una_instruccion->parametro1 = 0;
            una_instruccion->parametro2 = 0;
            una_instruccion->parametro3 = 0;
        }

        queue_push(cola_instrucciones, una_instruccion);
        free(aux[0]);
    	free(aux);
    }

    fclose(archivo);
    free(buffer);
    free(path);

    conectar_a_kernel();
    enviar_informacion();
    esperar_mensaje_finalizacion();

    return EXIT_SUCCESS;
}

instruccion devolver_enum_instruccion(char* instruccion) {
    if(strcmp(instruccion, "F_READ") == 0) return F_READ;
    if(strcmp(instruccion, "F_WRITE") == 0) return F_WRITE;
    if(strcmp(instruccion, "SET") == 0) return SET;
    if(strcmp(instruccion, "MOV_IN") == 0) return MOV_IN;
    if(strcmp(instruccion, "MOV_OUT") == 0) return MOV_OUT;
    if(strcmp(instruccion, "F_TRUNCATE") == 0) return F_TRUNCATE;
    if(strcmp(instruccion, "F_SEEK") == 0) return F_SEEK;
    if(strcmp(instruccion, "CREATE_SEGMENT") == 0) return CREATE_SEGMENT;
    if(strcmp(instruccion, "I/O") == 0) return I/O;
    if(strcmp(instruccion, "WAIT") == 0) return WAIT;
    if(strcmp(instruccion, "SIGNAL") == 0) return SIGNAL;
    if(strcmp(instruccion, "F_OPEN") == 0) return F_OPEN;
    if(strcmp(instruccion, "F_CLOSE") == 0) return F_CLOSE;
    if(strcmp(instruccion, "DELETE_SEGEMNT") == 0) return DELETE_SEGMENT;
    if(strcmp(instruccion, "EXIT") == 0) return EXIT;
    if(strcmp(instruccion, "YIELD") == 0) return YIELD;
    return -1;
}

void leer_configuracion() {
    t_config *un_config;

    un_config = config_create("./consola.config");

    config_consola.ip_kernel = strdup(config_get_string_value(un_config,"IP_KERNEL"));
    config_consola.puerto_kernel = strdup(config_get_string_value(un_config,"PUERTO_KERNEL"));

    config_destroy(un_config);
}

void conectar_a_kernel() {
    conexion_kernel = crear_conexion(config_consola.ip_kernel,config_consola.puerto_kernel);

    printf("Conectando con módulo Kernel... \n");

    if(conexion_kernel > 0) {
        printf("Conectado \n");
    }
    else {
        printf("No se pudo conectar al Kernel \n");
        exit(EXIT_FAILURE);
    }
}

void enviar_informacion() {
    t_queue *instucciones = malloc(sizeof(t_queue));
    consola->instrucciones = cola_instrucciones;

    enviar_datos_consola(conexion_kernel, consola);
    free(consola);
}

void esperar_mensaje_finalizacion() {
    int estado_finalizacion;
    recv(conexion_kernel, &estado_finalizacion, sizeof(int), MSG_WAITALL);
    estado_finalizacion == 1 ? liberar_memoria_y_conexiones() : printf("Error al finalizar consola \n");

    free(config_consola.ip_kernel);
    free(config_consola.puerto_kernel);
    close(conexion_kernel);
}

void liberar_memoria_y_conexiones()
{
    printf("Finalizando consola ... \n");
    queue_destroy_and_destroy_elements(cola_instrucciones,borrar_instruccion_consola);
}
