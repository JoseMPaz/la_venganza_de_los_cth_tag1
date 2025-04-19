#include "utils/config.h"
#include "utils/logger.h"
#include <commons/string.h>

typedef struct {
    char* ip_kernel;
    char* ip_memoria;
    char* puerto_memoria;
    char* ip_cpu;
    char* puerto_cpu_dispatch;
    char* puerto_cpu_interrupt;
    char* algoritmo_planificacion;
    char* quantum;
}kernel_config_t;

void cargar_configuracion_kernel(char* path);

extern kernel_config_t* kernel_config;