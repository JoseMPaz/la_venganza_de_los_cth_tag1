#include <commons/config.h>
#include <stdlib.h>
#include <stdio.h>
#include "logger.h"

#define ERROR_APERTURA_CONFIG "Error: No se pudo abrir el archivo de cnfiguración"


t_config* cargarConfiguracion(char* path);