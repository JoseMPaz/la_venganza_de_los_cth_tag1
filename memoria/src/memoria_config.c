#include "memoria_config.h"
void cargar_configuracion_memoria(char* path)
{
    t_config* config = cargarConfiguracion(path);

    memoria_config = (memoria_config_t *) malloc (sizeof(memoria_config_t));

    memoria_config->ip_memoria 			= config_get_string_value (config,"IP_MEMORIA");
    memoria_config->puerto_escucha 		= config_get_string_value (config, "PUERTO_ESCUCHA");
    memoria_config->tam_memoria 		= config_get_string_value (config, "TAM_MEMORIA");
	memoria_config->tam_pagina			= config_get_string_value (config, "TAM_PAGINA");
	memoria_config->entradas_por_tabla	= config_get_string_value (config, "ENTRADAS_POR_TABLA");
	memoria_config->cantidad_niveles	= config_get_string_value (config, "CANTIDAD_NIVELES");
	memoria_config->retardo_memoria		= config_get_string_value (config, "RETARDO_MEMORI");
	memoria_config->path_swapfile		= config_get_string_value (config, "PATH_SWAPFILE");
	memoria_config->retardo_swap		= config_get_string_value (config, "RETARDO_SWAP");
	memoria_config->retardo_swap		= config_get_string_value (config, "LOG_LEVEL");
	memoria_config->dump_path			= config_get_string_value (config, "DUMP_PATH");
    
	return;
}
