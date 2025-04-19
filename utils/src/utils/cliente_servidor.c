#include <utils/cliente_servidor.h>

int iniciar_servidor(char* ip, char* puerto) {

    //log_info(logger,"Iniciando servidor");

    int socket_servidor;

    struct addrinfo hints, * servinfo;

    // Configuramos las opciones para el socket
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    // Obtenemos la información de la dirección
    getaddrinfo(ip, puerto, &hints, &servinfo);

    // Creamos el socket de escucha del servidor
    socket_servidor = socket (servinfo->ai_family,
                             servinfo->ai_socktype,
                             servinfo->ai_protocol);

    bind(socket_servidor, servinfo->ai_addr, servinfo->ai_addrlen);

    listen(socket_servidor, SOMAXCONN);

    freeaddrinfo(servinfo);

    return socket_servidor;
    
}

int esperar_cliente(const char* name, int socket_servidor){
    struct sockaddr_in dir_cliente;
    socklen_t tam_direccion = sizeof(struct sockaddr_in);
    int socket_cliente = accept(socket_servidor, (void*) &dir_cliente, &tam_direccion);

    log_info(logger,"cliente conectado");

    return socket_cliente;
}

void desconectar_servidor(int socketServidor)
{
    close(socketServidor);
}

int conectar_a_servidor(char* ip, char* puerto){

    struct addrinfo hints;
    struct addrinfo *server_info;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC; 
    hints.ai_socktype = SOCK_STREAM; 
    hints.ai_flags = AI_PASSIVE; 

    getaddrinfo(ip, puerto, &hints, &server_info);

    int socket_cliente = socket(server_info->ai_family,
                                server_info->ai_socktype,
                                server_info->ai_protocol);

    connect(socket_cliente, server_info->ai_addr, server_info->ai_addrlen);

    log_info(logger, "Conectado a %s:%s", ip, puerto);

    freeaddrinfo(server_info);

    return socket_cliente;
}

void desconectar_cliente(int socketCliente){
    close(socketCliente);
}

void* serializar_paquete(t_paquete* paquete, int bytes)
{
	void * magic = malloc(bytes);
	int desplazamiento = 0;

	memcpy(magic + desplazamiento, &(paquete->codigo_operacion), sizeof(int));
	desplazamiento+= sizeof(int);
	memcpy(magic + desplazamiento, &(paquete->buffer->size), sizeof(int));
	desplazamiento+= sizeof(int);
	memcpy(magic + desplazamiento, paquete->buffer->stream, paquete->buffer->size);
	desplazamiento+= paquete->buffer->size;

	return magic;
}

void enviar_mensaje(char* mensaje, int socket_cliente)
{
	t_paquete* paquete = malloc(sizeof(t_paquete));

	paquete->codigo_operacion = MENSAJE;
	paquete->buffer = malloc(sizeof(t_buffer));
	paquete->buffer->size = strlen(mensaje) + 1;
	paquete->buffer->stream = malloc(paquete->buffer->size);
	memcpy(paquete->buffer->stream, mensaje, paquete->buffer->size);

	int bytes = paquete->buffer->size + 2*sizeof(int);

	void* a_enviar = serializar_paquete(paquete, bytes);

	send(socket_cliente, a_enviar, bytes, 0);

	free(a_enviar);
	eliminar_paquete(paquete);
}


void crear_buffer(t_paquete* paquete)
{
	paquete->buffer = malloc(sizeof(t_buffer));
	paquete->buffer->size = 0;
	paquete->buffer->stream = NULL;
}

t_paquete* crear_paquete(void)
{
	t_paquete* paquete = malloc(sizeof(t_paquete));
	paquete->codigo_operacion = PAQUETE;
	crear_buffer(paquete);
	return paquete;
}

void agregar_a_paquete(t_paquete* paquete, void* valor, int tamanio)
{
	paquete->buffer->stream = realloc(paquete->buffer->stream, paquete->buffer->size + tamanio + sizeof(int));

	memcpy(paquete->buffer->stream + paquete->buffer->size, &tamanio, sizeof(int));
	memcpy(paquete->buffer->stream + paquete->buffer->size + sizeof(int), valor, tamanio);

	paquete->buffer->size += tamanio + sizeof(int);
}

void enviar_paquete(t_paquete* paquete, int socket_cliente)
{
	int bytes = paquete->buffer->size + 2*sizeof(int);
	void* a_enviar = serializar_paquete(paquete, bytes);

	send(socket_cliente, a_enviar, bytes, 0);

	free(a_enviar);
}

void eliminar_paquete(t_paquete* paquete)
{
	free(paquete->buffer->stream);
	free(paquete->buffer);
	free(paquete);
}

void liberar_conexion(int socket_cliente)
{
	close(socket_cliente);
}

void * atender_clientes (void * escucha)
{
	int * socket_escucha = (int *) escucha;
	int socket_servidor = *socket_escucha;
	
	log_info (logger, "%s", "Inicia Atencion a clientes");
	while (1)
	{
		pthread_t hilo;
		int * socket_bidireccional = (int *) malloc (sizeof(int));
		
		*socket_bidireccional =  accept (socket_servidor, NULL, NULL);	//se queda ahi hasta que se acepte un cliente
		log_info (logger, "%s", "Nueva conexion de un cliente");
		
		pthread_create (&hilo, NULL, atender, (void *) socket_bidireccional);
		pthread_detach(hilo);	
	}
	pthread_exit (NULL);
	return NULL;
}

void * atender (void * argumento)
{
	
	int * socket_bidireccional = (int *) argumento; 	
	t_list * lista = NULL;
	
	while (true) 
	{
		int codigo_operacion = recibir_operaciones (*socket_bidireccional);
		
		switch (codigo_operacion) 
		{
			case MENSAJE:
				recibir_mensaje (*socket_bidireccional, logger);
				break;
			case PAQUETE:
			lista = recibir_paquete (*socket_bidireccional);
			log_info(logger, "Mensajes recibidos:");
			loggear_mensajes (lista, logger);
			break;
			case -1:
				log_error (logger, "el cliente se desconecto. Terminando servidor");
				return NULL;
			default:
				log_warning(logger,"Operacion desconocida");
				return NULL;
		}
	}

	return NULL;
}

int recibir_operaciones(int socket_cliente)
{
	int codigo_operacion;
	
	if(recv(socket_cliente, &codigo_operacion, sizeof(int), MSG_WAITALL) > 0)
		return codigo_operacion;
	
	close(socket_cliente);
	
	return -1;
}

void loggear_mensajes (t_list * self, t_log * log) 
{
	t_link_element ** indirect = &self->head;
	
	while ((*indirect) != NULL) 
	{
		log_info(log,"%s", (char *)(*indirect)->data);
		indirect = &(*indirect)->next;
	}
	return;
}

t_list * recibir_paquete (int socket_cliente)
{
	int size;
	int desplazamiento = 0;
	void * buffer;
	t_list * valores = list_create();
	int tamanio;

	buffer = recibir_buffer (&size, socket_cliente);
	while(desplazamiento < size)
	{
		memcpy ( &tamanio, buffer + desplazamiento, sizeof (int) );
		desplazamiento += sizeof (int);
		char * valor = (char *) malloc ( tamanio );
		memcpy (valor, buffer + desplazamiento, tamanio);
		desplazamiento += tamanio;
		list_add (valores, valor);
	}
	free (buffer);
	
	return valores;
}

void recibir_mensaje (int socket_cliente, t_log * log)
{
	int size;
	char * buffer = recibir_buffer (&size, socket_cliente);
	log_info (log, "Me llego el mensaje %s", buffer);
	free(buffer);
	
	return;
}

void * recibir_buffer (int * size, int socket_cliente)
{
	void * buffer;

	recv (socket_cliente, size, sizeof(int), MSG_WAITALL);
	buffer = malloc(*size);
	recv (socket_cliente, buffer, *size, MSG_WAITALL);

	return buffer;
}
