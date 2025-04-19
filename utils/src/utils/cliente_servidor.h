#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "logger.h"
#include<sys/socket.h>
#include<unistd.h>
#include<netdb.h>
#include<commons/log.h>
#include<commons/collections/list.h>
#include<string.h>
#include<assert.h>
#include <pthread.h>

typedef struct {
    int memoriaSocket;
    int kernelSocket;
    int socketCPU;
    int interruptSocket;
    int dispatchSocket;
    int filesystemSocket;
} socketsT;

typedef enum
{
	MENSAJE,
	PAQUETE
}op_code;




typedef struct
{
	int size;
	void* stream;
} t_buffer;

typedef struct
{
	op_code codigo_operacion;
	t_buffer* buffer;
} t_paquete;

int iniciar_servidor(char* ip, char* puerto);
int esperar_cliente(const char* name, int socket_servidor);
void desconectar_servidor(int socketServidor);
int conectar_a_servidor(char*, char*);
void desconectar_cliente(int);
void enviar_mensaje(char* mensaje, int socket_cliente);
t_paquete* crear_paquete(void);
void agregar_a_paquete(t_paquete* paquete, void* valor, int tamanio);
void enviar_paquete(t_paquete* paquete, int socket_cliente);
void liberar_conexion(int socket_cliente);
void eliminar_paquete(t_paquete* paquete);

int recibir_operaciones(int socket_cliente);
void * atender (void * argumento);
void loggear_mensajes (t_list * self, t_log * log);
t_list * recibir_paquete (int socket_cliente);
void recibir_mensaje (int socket_cliente, t_log * log);
void * recibir_buffer (int * size, int socket_cliente);
void * atender_clientes (void * escucha);

extern socketsT* sockets;
