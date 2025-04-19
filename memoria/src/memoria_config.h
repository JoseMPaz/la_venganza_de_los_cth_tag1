#include "utils/config.h"
#include "utils/logger.h"
#include <commons/string.h>


typedef struct 
{
    char * ip_memoria;
    char * puerto_escucha;
    char * tam_memoria;
    char * tam_pagina;
    char * entradas_por_tabla;
    char * cantidad_niveles;
    char * retardo_memoria;
    char * path_swapfile;
    char * retardo_swap;
    char * log_level;
    char * dump_path; 
} memoria_config_t;

void cargar_configuracion_memoria (char * path);

extern memoria_config_t* memoria_config; //Indica que hay una variable global llamada memoria_config que es externa



