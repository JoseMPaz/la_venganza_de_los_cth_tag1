#include <utils/cliente_servidor.h>
#include <memoria_config.h>
#include <utils/config.h>
#include <utils/logger.h>
#include <pthread.h>

/* Variables globales */
t_log * logger = NULL;
memoria_config_t * memoria_config = NULL;
/*Prototipo de funcion*/
void * enviar_saludo (void * socket_cpu);

/*Funcion Principal*/
int main(int argc, char* argv[]) 
{
	//int * socket_a_filesystem = (int *) malloc (sizeof(int)); 
	int * socket_escucha = (int *) malloc (sizeof(int));
	pthread_t hilo_escucha;//hilo_a_filesystem;
    // Iniciar el logger
    logger = crear_logger();
    log_info(logger, "********** Iniciando memoria **********");

    // Cargar la configuracion
    cargar_configuracion_memoria("memoria.config");//Carga la variable global memoria_config

	*socket_escucha = iniciar_servidor( memoria_config->ip_memoria , memoria_config->puerto_escucha);
        
    /* Atiende peticones de kernel y cpu */
	pthread_create (&hilo_escucha, NULL, atender_clientes , (void *) socket_escucha);
	pthread_detach(hilo_escucha);

	pthread_exit (NULL);

    return 0;
    
}

void * enviar_saludo (void * socket_cpu)
{
	int i;
	
	for (i = 0; i<5; i++)
	{
		enviar_mensaje ("HOLA FileSystem, SOY Memoria", *((int *)socket_cpu));
		sleep (2);
	}
	return NULL;
}
