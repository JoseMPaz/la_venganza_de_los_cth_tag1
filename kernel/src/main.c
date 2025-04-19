#include <utils/cliente_servidor.h>
#include <kernel_config.h>
#include <utils/config.h>
#include <utils/logger.h>
#include <pthread.h>

/* Variables globales */
t_log * logger = NULL;
kernel_config_t* kernel_config = NULL;

void * enviar_saludo_cpu (void * socket_cpu);
void * enviar_saludo_memoria (void * socket_memoria);

void validar_argumentos (int argc, char* argv[]);

int main(int argc, char* argv[]) {

    //int * socket_a_cpu_dis = (int *) malloc (sizeof(int));
    //int * socket_a_cpu_int = (int *) malloc (sizeof(int));
    int * socket_a_memoria = (int *) malloc (sizeof(int));
    pthread_t hilo_a_memoria;//hilo_dispatch, hilo_interrupt, hilo_a_memoria;
    //Iniciar el logger
    logger = crear_logger();
    //log_info(logger, "Iniciando kernel");

    //Cargar la configuracion
    cargar_configuracion_kernel("kernel.config");

    //Conexion con el servidor CPU
    //*socket_a_cpu_dis = conectar_a_servidor(kernel_config->ip_cpu,kernel_config->puerto_cpu_dispatch);
    //log_info(logger, "CPU dispatch conectado a Kernel, socket: %d", *socket_a_cpu_dis);

    //*socket_a_cpu_int = conectar_a_servidor(kernel_config->ip_cpu,kernel_config->puerto_cpu_interrupt);
    //log_info(logger, "CPU interrupt conectado a Kernel, socket: %d", *socket_a_cpu_int);

    //Conexion con el servidor Memoria
    *socket_a_memoria =conectar_a_servidor(kernel_config->ip_memoria,kernel_config->puerto_memoria);
    log_info(logger, "Memoria conectada a Kernel, socket: %d", *socket_a_memoria);

    //pthread_create(&hilo_dispatch, NULL, enviar_saludo_cpu, (void*)socket_a_cpu_dis);
    //pthread_detach(hilo_dispatch);

    //pthread_create(&hilo_interrupt, NULL, enviar_saludo_cpu, (void*)socket_a_cpu_int);
    //pthread_detach(hilo_interrupt);

    pthread_create(&hilo_a_memoria, NULL, enviar_saludo_memoria, (void*)socket_a_memoria);
    pthread_detach(hilo_a_memoria);

    pthread_exit (NULL);

    return 0;

}

void * enviar_saludo_cpu (void * socket_cpu)
{
	for (int i = 0; i < 5; i++)
	{
		enviar_mensaje ("HOLA CPU, SOY Kernel", *((int *)socket_cpu));
		sleep (2);
	}
	return NULL;
}

void * enviar_saludo_memoria (void * socket_memoria)
{
	for (int i = 0; i < 5; i++)
	{
		enviar_mensaje ("HOLA Memoria, SOY Kernel", *((int *)socket_memoria));
		sleep (2);
	}
	return NULL;
}

void validar_argumentos (int argc, char* argv[])
{
	int cantidad_de_argumentos = argc;
	char archivo_ensamblador[100];
	
	if (cantidad_de_argumentos < 3)
	{
		fprintf (stderr, "Error, faltan argumentos\n");
		exit(1);
	}
	
	strcpy (archivo_ensamblador, argv[1]);
	
	
	return;
}
