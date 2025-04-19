#include "logger.h"

t_log* crear_logger(void){
    t_log* nuevo_logger = log_create("tp.log", "client", 1, LOG_LEVEL_INFO);
    return nuevo_logger;
}


