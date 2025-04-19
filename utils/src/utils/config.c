#include "config.h"
t_config * cargarConfiguracion ( char* path ){
    t_config * nuevo_config = config_create(path);
    if(nuevo_config == NULL)
    {
        log_error(logger,ERROR_APERTURA_CONFIG);
        exit(1);
    }
    return nuevo_config;
}

