#include "kernel_config.h"

void cargar_configuracion_kernel(char* path){
t_config* config = cargarConfiguracion(path);

    kernel_config = malloc(sizeof(kernel_config_t));

    kernel_config->ip_kernel = config_get_string_value(config,"IP_KERNEL");
    kernel_config->ip_memoria = config_get_string_value(config,"IP_MEMORIA");
    kernel_config->puerto_memoria = string_from_format("%d", config_get_int_value(config, "PUERTO_MEMORIA"));
    kernel_config->ip_cpu = config_get_string_value(config,"IP_CPU");
    kernel_config->puerto_cpu_dispatch = string_from_format("%d", config_get_int_value(config, "PUERTO_CPU_DISPATCH"));
    kernel_config->puerto_cpu_interrupt = string_from_format("%d", config_get_int_value(config, "PUERTO_CPU_INTERRUPT"));
    kernel_config->algoritmo_planificacion = config_get_string_value(config, "ALGORITMO_PLANIFICACION");
    kernel_config->quantum = string_from_format("%d", config_get_int_value(config, "QUANTUM"));

    log_info(logger,"Configuracion cargada");

}