#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* clave;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"

	log_info(logger,"hola!,Soy un log!!");


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	ip = config_get_string_value(config,"IP");
	puerto = config_get_string_value(config,"PUERTO");
	clave= config_get_string_value(config,"CLAVE");
	log_info(logger,"Lei la ip %s con puerto %s y clave %s", ip, puerto, clave);


	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'
	/*valor= config_get_string_value(config, "CLAVE");
	ip = config_get_string_value(config,"IP");
	puerto=config_get_string_value(config,"PUERTO");*/



	// Loggeamos el valor de config

	/*log_info(logger, valor);
	log_destroy(logger);*/


	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje

	enviar_mensaje(clave, conexion);
	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	printf("\nCLIENTE CERRADO!!!");

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente

}




t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;

	if((nuevo_logger =log_create("tp0.log","TP0",1, LOG_LEVEL_INFO)) == NULL){
		printf("No se puede crear el log");
		exit(1);
	}

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;
	if((nuevo_config=config_create("/home/utnso/Documents/tp0/client/cliente.config"))==NULL){
		printf("no pude leer la config");
		exit(2);
	}

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	leido = readline("> ");
	log_info(logger, ">>%s",leido);

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío
		while(strcmp(leido, "")!=0){
			free(leido);
			leido=readline("> ");
			log_info(logger, ">>%s",leido);

		}

	// ¡No te olvides de liberar las lineas antes de regresar!
		free(leido);

}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido=NULL;
	t_paquete* paquete=crear_paquete();

	// Leemos y esta vez agregamos las lineas al paquete
		leido = readline("> ");

		while(strcmp(leido, "")!=0){
			agregar_a_paquete(paquete,leido,strlen(leido)+1);
				free(leido);
				leido=readline("> ");

			}

		free(leido);

		//enviar paquete
		enviar_paquete(paquete,conexion);

		//eliminar paquete

		eliminar_paquete(paquete);



	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */

	if(logger!=NULL){
		log_destroy(logger);
	}

	if(config!=NULL){
		log_destroy(config);
	}

	liberar_conexion(conexion);

}


