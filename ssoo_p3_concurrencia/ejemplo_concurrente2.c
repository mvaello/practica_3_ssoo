#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "concurrente.h"

/*
 * Constantes con los tiempos de ejecucion de cada operacion
 */

#define TIEMPO_EXISTE_CUENTA 1
#define TIEMPO_CREAR_CUENTA_DB 1
#define OBTENER_NUM_CUENTAS 4

#define TIEMPO_CREAR_CUENTA (TIEMPO_EXISTE_CUENTA + TIEMPO_CREAR_CUENTA_DB)
#define TIEMPO_BORRAR_CUENTA 2
#define TIEMPO_CONTAR_CUENTAS OBTENER_NUM_CUENTAS

#define TIEMPO_OBTENER_SALDO 0.75
#define TIEMPO_ACTUALIZAR_CUENTA 0.75

#define TIEMPO_INCREMENTAR_SALDO (TIEMPO_OBTENER_SALDO + TIEMPO_ACTUALIZAR_CUENTA)
#define TIEMPO_DECREMENTAR_SALDO (TIEMPO_OBTENER_SALDO + TIEMPO_ACTUALIZAR_CUENTA)

#define UMBRAL_PERMITIDO 0.25


#define TRUE 1
#define FALSE 0
#define MAX 6

/*
 * Esta estructura se utiliza para poder pasar los datos de 
 * nombre de cuenta y saldo en un solo parametro.
 * cuenta: es un string con el nombre de la cuenta
 * saldo: es un entero con el saldo a incrementar/decrementar
 */
struct actualizar_saldo
{
    char cuenta[128];
	int saldo;
};

/**
 * Funciones para utilizar con hilos.
 * Operaciones sobre el banco.
 */
 
/*
 * Esta función, diseñada para ser ejecutada por un hilo,
 * crea una cuenta con el nombre pasado por parametro
 */
void *hilo_crear_cuenta(void *arg){
	char* cuenta;
	
	cuenta = (char*)malloc(strlen((char*)arg));
	strcpy(cuenta,(char*)arg);
	printf("Hilo %s \n",cuenta);
	
	concurrente_crear_cuenta(cuenta);
	
	free(cuenta);
	
	pthread_exit (NULL);
}

/*
 * Esta función, diseñada para ser ejecutada por un hilo,
 * borra una cuenta con el nombre pasado por parametro
 */
void *hilo_borrar_cuenta(void *arg){
	char* cuenta;
	
	cuenta = (char*)malloc(strlen((char*)arg));
	strcpy(cuenta,(char*)arg);
	printf("Hilo %s \n",cuenta);
	
	concurrente_borrar_cuenta(cuenta);
	
	free(cuenta);
	
	pthread_exit (NULL);
}

/*
 * Esta función, diseñada para ser ejecutada por un hilo,
 * cuenta el número de cuentas del banco
 */
void *hilo_contar_cuentas(void *arg){
	char* cuenta;
	int num_cuentas;
	
	cuenta = (char*)malloc(strlen((char*)arg));
	strcpy(cuenta,(char*)arg);
	printf("Hilo %s \n",cuenta);
	
	concurrente_obtener_num_cuentas(&num_cuentas);
	
	free(cuenta);
	
	pthread_exit (NULL);
}


/**
 * Funciones para utilizar con hilos.
 * Operaciones sobre cuentas.
 */

/*
 * Esta función, diseñada para ser ejecutada por un hilo,
 * incrementa el saldo de la cuenta pasada por parametro
 * en una estructura. En la estructura tambien entra la cantidad
 * que se quiere incrementar
 */
void *hilo_incrementar_saldo(void *arg){
	struct actualizar_saldo inc;
	int saldo_actualizado;
	
	memcpy(&inc, arg, sizeof(struct actualizar_saldo));
	
	concurrente_incrementar_saldo(inc.cuenta, inc.saldo, &saldo_actualizado);

	pthread_exit (NULL);
}

/*
 * Esta función, diseñada para ser ejecutada por un hilo,
 * decrementa el saldo de la cuenta pasada por parametro
 * en una estructura. En la estructura tambien entra la cantidad
 * que se quiere decrementar
 */
void *hilo_decrementar_saldo(void *arg){
	struct actualizar_saldo dec;
	int saldo_actualizado;
	
	memcpy(&dec, arg, sizeof(struct actualizar_saldo)); 
	
	concurrente_decrementar_saldo(dec.cuenta, dec.saldo, &saldo_actualizado);

	pthread_exit (NULL);
}

/*
 * Esta función, diseñada para ser ejecutada por un hilo,
 * obtiene el saldo de una cuenta pasada por parametro
 */
void *hilo_obtener_saldo(void *arg){
	char* cuenta;
	int saldo;
	
	cuenta = (char*)malloc(strlen((char*)arg));
	strcpy(cuenta,(char*)arg);
	
	concurrente_obtener_saldo(cuenta, &saldo);
	
	free(cuenta);

	pthread_exit (NULL);
}


/**
 * PRUEBAS
 */

/*
 * En esta prueba se lanzan seis operaciones de escritura sobre el banco
 * de forma simultanea. Se crean seis cuentas.
 */
int pruebaWWWWWWcrear(){
	int i;
	pthread_t th_prueba[MAX];
	void *st1;
	char cuenta[MAX][128];
	struct timeval start_time,end_time;
	double start,end;
	int res;
	int tiempo_estimado;
	
	printf("\n\n");
	printf("*************************************** \n");
	printf("************ PRUEBA WWWWWW1 *********** \n");
	printf("*************************************** \n");
	
	// Se mide el tiempo en el que comienza la prueba
	gettimeofday(&start_time, NULL);
	start = start_time.tv_sec + (start_time.tv_usec / 1000000.0);
	
	// Se crean los 6 hilos de escrituras sobre el banco
	for (i=0;i<MAX;i++){
		sprintf(cuenta[i], "cuenta%d", i);
		pthread_create (&th_prueba[i], NULL, hilo_crear_cuenta, cuenta[i]);
	}
	// Se espera a que finalicen los 6 hilos
	for (i=0;i<MAX;i++){
		pthread_join (th_prueba[i], (void **) &st1);
	}
	
	// Se toma el tiempo de fin
	gettimeofday(&end_time, NULL);
	end = end_time.tv_sec + (end_time.tv_usec / 1000000.0);
	
	// Como las operaciones son de escritura, se deben secuenciar (una detras de otra)
	tiempo_estimado = TIEMPO_CREAR_CUENTA*MAX;
	
	printf("*************************************** \n");
	if(end-start > tiempo_estimado && end-start < tiempo_estimado+UMBRAL_PERMITIDO){
		printf("********** PRUEBA WWWWWW1 OK! ********* \n");
		res = TRUE;
	}else{
		printf("********** PRUEBA WWWWWW1 ERR ********* \n");
		res = FALSE;
	}
	printf("*************************************** \n");
	printf("********** FIN PRUEBA WWWWWW1 ********* \n");
	printf("*************************************** \n");
	
	return res;
}

/*
 * En esta prueba se lanzan seis operaciones de escritura sobre el banco
 * de forma simultanea. Se borran seis cuentas.
 */
int pruebaWWWWWWborrar(){
	int i;
	pthread_t th_prueba[MAX];
	void *st1;
	char cuenta[MAX][128];
	struct timeval start_time,end_time;
	double start,end;
	int res;
	int tiempo_estimado;
	
	printf("\n\n");
	printf("*************************************** \n");
	printf("************ PRUEBA WWWWWW2 *********** \n");
	printf("*************************************** \n");
	
	// Se mide el tiempo en el que comienza la prueba
	gettimeofday(&start_time, NULL);
	start = start_time.tv_sec + (start_time.tv_usec / 1000000.0);
	
	// Se crean los 6 hilos de escrituras sobre el banco
	for (i=0;i<MAX;i++){
		sprintf(cuenta[i], "cuenta%d", i);
		pthread_create (&th_prueba[i], NULL, hilo_borrar_cuenta, cuenta[i]);
	}
	// Se espera a que finalicen los 6 hilos
	for (i=0;i<MAX;i++){
		pthread_join (th_prueba[i], (void **) &st1);
	}
	
	// Se toma el tiempo de fin
	gettimeofday(&end_time, NULL);
	end = end_time.tv_sec + (end_time.tv_usec / 1000000.0);
	
	// Como las operaciones son de escritura, se deben secuenciar (una detras de otra)
	tiempo_estimado = TIEMPO_BORRAR_CUENTA*MAX;
	
	printf("*************************************** \n");
	if(end-start > tiempo_estimado && end-start < tiempo_estimado+UMBRAL_PERMITIDO){
		printf("********** PRUEBA WWWWWW2 OK! ********* \n");
		res = TRUE;
	}else{
		printf("********** PRUEBA WWWWWW2 ERR ********* \n");
		res = FALSE;
	}
	printf("*************************************** \n");
	printf("********** FIN PRUEBA WWWWWW2 ********* \n");
	printf("*************************************** \n");
	
	return res;
}


/*
 * En esta prueba se lanzan seis operaciones de lectura sobre el banco
 * de forma simultanea.
 */
int pruebaRRRRRR(){
	int i;
	pthread_t th_prueba[MAX];
	void *st1;
	char cuenta[MAX][128];
	struct timeval start_time,end_time;
	double start,end;
	int res;
	int tiempo_estimado;
	
	printf("\n\n");
	printf("*************************************** \n");
	printf("************ PRUEBA RRRRRR ************ \n");
	printf("*************************************** \n");
	
	// Se mide el tiempo en el que comienza la prueba
	gettimeofday(&start_time, NULL);
	start = start_time.tv_sec + (start_time.tv_usec / 1000000.0);
	
	// Se crean los 6 hilos de lectura sobre el banco
	for (i=0;i<MAX;i++){
		sprintf(cuenta[i], "cuenta%d", i);
		pthread_create (&th_prueba[i], NULL, hilo_contar_cuentas, cuenta[i]);
	}
	// Se espera a que finalicen los 6 hilos
	for (i=0;i<MAX;i++){
		pthread_join (th_prueba[i], (void **) &st1);
	}
	
	// Se toma el tiempo de fin
	gettimeofday(&end_time, NULL);
	end = end_time.tv_sec + (end_time.tv_usec / 1000000.0);
	
	// Como las operaciones son de lectura, deben suceder en paralelo 
	//(tardan aprox. los mismo 6 lecturas o una)
	tiempo_estimado = TIEMPO_CONTAR_CUENTAS;
	
	printf("*************************************** \n");
	if(end-start > tiempo_estimado && end-start < tiempo_estimado+UMBRAL_PERMITIDO){
		printf("********** PRUEBA RRRRRR OK! ********** \n");
		res = TRUE;
	}else{
		printf("********** PRUEBA RRRRRR ERR ********** \n");
		res = FALSE;
	}
	printf("*************************************** \n");
	printf("********** FIN PRUEBA RRRRRR ********** \n");
	printf("*************************************** \n");
	
	return res;
}


/*
 * En esta prueba se lanzan cuatro operaciones de escritura (crear cuenta), 
 * seguidas de dos de lectura.
 */
int pruebaWWWWRRcrear(){
	int i;
	pthread_t th_prueba[MAX];
	void *st1;
	char cuenta[MAX][128];
	struct timeval start_time,end_time;
	double start,end;
	int res;
	int tiempo_estimado;
	
	printf("\n\n");
	printf("*************************************** \n");
	printf("************ PRUEBA WWWWRR1 *********** \n");
	printf("*************************************** \n");
	
	// Se mide el tiempo en el que comienza la prueba
	gettimeofday(&start_time, NULL);
	start = start_time.tv_sec + (start_time.tv_usec / 1000000.0);
	
	// Se crean los 6 hilos (4 de escritura y dos de lectura)
	// Dormimos un segundo entre cada creación para asegurar el orden
	for (i=0;i<MAX;i++){
		sprintf(cuenta[i], "cuenta%d", i);
	}
	pthread_create (&th_prueba[0], NULL, hilo_crear_cuenta, cuenta[0]);
	sleep(1);
	pthread_create (&th_prueba[1], NULL, hilo_crear_cuenta, cuenta[1]);
	sleep(1);
	pthread_create (&th_prueba[2], NULL, hilo_crear_cuenta, cuenta[2]);
	sleep(1);
	pthread_create (&th_prueba[3], NULL, hilo_crear_cuenta, cuenta[3]);
	sleep(1);
	pthread_create (&th_prueba[4], NULL, hilo_contar_cuentas, cuenta[4]);
	pthread_create (&th_prueba[5], NULL, hilo_contar_cuentas, cuenta[5]);
	// Se espera a que finalicen los 6 hilos
	for (i=0;i<MAX;i++){
		pthread_join (th_prueba[i], (void **) &st1);
	}
	
	// Se toma el tiempo de fin
	gettimeofday(&end_time, NULL);
	end = end_time.tv_sec + (end_time.tv_usec / 1000000.0);
	
	// Las operaciones de escritura se deben secuenciar, 
	// mientras que las lecturas deben ser simultáneas
	// Los sleep quedan ocultos por cada proceso de escritura.
	tiempo_estimado = TIEMPO_CREAR_CUENTA*4 + TIEMPO_CONTAR_CUENTAS;
	
	printf("*************************************** \n");
	printf("*************************************** \n");
	if(end-start > tiempo_estimado && end-start < tiempo_estimado+UMBRAL_PERMITIDO){
		printf("********** PRUEBA WWWWRR1 OK! ********* \n");
		res = TRUE;
	}else{
		printf("********** PRUEBA WWWWRR1 ERR ********* \n");
		res = FALSE;
	}
	printf("*************************************** \n");
	printf("********** FIN PRUEBA WWWWRR1 ********* \n");
	printf("*************************************** \n");
	
	return res;
}

/*
 * En esta prueba se lanzan cuatro operaciones de escritura (borrar cuenta), 
 * seguidas de dos de lectura.
 */
int pruebaWWWWRRborrar(){
	int i;
	pthread_t th_prueba[MAX];
	void *st1;
	char cuenta[MAX][128];
	struct timeval start_time,end_time;
	double start,end;
	int res;
	int tiempo_estimado;
	
	printf("\n\n");
	printf("*************************************** \n");
	printf("************ PRUEBA WWWWRR2 *********** \n");
	printf("*************************************** \n");
	
	// Se mide el tiempo en el que comienza la prueba
	gettimeofday(&start_time, NULL);
	start = start_time.tv_sec + (start_time.tv_usec / 1000000.0);
	
	// Se crean los 6 hilos (4 de escritura y dos de lectura)
	// Dormimos un segundo entre cada creación para asegurar el orden
	for (i=0;i<MAX;i++){
		sprintf(cuenta[i], "cuenta%d", i);
	}
	pthread_create (&th_prueba[0], NULL, hilo_borrar_cuenta, cuenta[0]);
	sleep(1);
	pthread_create (&th_prueba[1], NULL, hilo_borrar_cuenta, cuenta[1]);
	sleep(1);
	pthread_create (&th_prueba[2], NULL, hilo_borrar_cuenta, cuenta[2]);
	sleep(1);
	pthread_create (&th_prueba[3], NULL, hilo_borrar_cuenta, cuenta[3]);
	sleep(1);
	pthread_create (&th_prueba[4], NULL, hilo_contar_cuentas, cuenta[4]);
	pthread_create (&th_prueba[5], NULL, hilo_contar_cuentas, cuenta[5]);
	// Se espera a que finalicen los 6 hilos
	for (i=0;i<MAX;i++){
		pthread_join (th_prueba[i], (void **) &st1);
	}
	
	// Se toma el tiempo de fin
	gettimeofday(&end_time, NULL);
	end = end_time.tv_sec + (end_time.tv_usec / 1000000.0);
	
	// Las operaciones de escritura se deben secuenciar, 
	// mientras que las lecturas deben ser simultáneas
	// Los sleep quedan ocultos por cada proceso de escritura.
	tiempo_estimado = TIEMPO_BORRAR_CUENTA*4 + TIEMPO_CONTAR_CUENTAS;
	
	printf("*************************************** \n");
	if(end-start > tiempo_estimado && end-start < tiempo_estimado+UMBRAL_PERMITIDO){
		printf("********** PRUEBA WWWWRR2 OK! ********* \n");
		res = TRUE;
	}else{
		printf("********** PRUEBA WWWWRR2 ERR ********* \n");
		res = FALSE;
	}
	printf("*************************************** \n");
	printf("********** FIN PRUEBA WWWWRR2 ********* \n");
	printf("*************************************** \n");
	
	return res;
}


/*
 * En esta prueba se lanzan cuatro operaciones de lectura 
 * seguidas de dos de escritura (crear cuenta).
 */
int pruebaRRRRWWcrear(){
	int i;
	pthread_t th_prueba[MAX];
	void *st1;
	char cuenta[MAX][128];
	struct timeval start_time,end_time;
	double start,end;
	int res;
	int tiempo_estimado;
	
	printf("\n\n");
	printf("*************************************** \n");
	printf("************ PRUEBA RRRRWW1 *********** \n");
	printf("*************************************** \n");
	
	// Se mide el tiempo en el que comienza la prueba
	gettimeofday(&start_time, NULL);
	start = start_time.tv_sec + (start_time.tv_usec / 1000000.0);
	
	// Se crean los 6 hilos (4 de escritura y dos de lectura)
	// Dormimos un segundo entre cada creación para asegurar el orden
	for (i=0;i<MAX;i++){
		sprintf(cuenta[i], "cuenta%d", i);
	}
	pthread_create (&th_prueba[0], NULL, hilo_contar_cuentas, cuenta[0]);
	sleep(1);
	pthread_create (&th_prueba[1], NULL, hilo_contar_cuentas, cuenta[1]);
	sleep(1);
	pthread_create (&th_prueba[2], NULL, hilo_contar_cuentas, cuenta[2]);
	sleep(1);
	pthread_create (&th_prueba[3], NULL, hilo_contar_cuentas, cuenta[3]);
	sleep(1);
	pthread_create (&th_prueba[4], NULL, hilo_crear_cuenta, cuenta[4]);
	sleep(1);
	pthread_create (&th_prueba[5], NULL, hilo_crear_cuenta, cuenta[5]);
	sleep(1);
	// Se espera a que finalicen los 6 hilos
	for (i=0;i<MAX;i++){
		pthread_join (th_prueba[i], (void **) &st1);
	}
	
	// Se toma el tiempo de fin
	gettimeofday(&end_time, NULL);
	end = end_time.tv_sec + (end_time.tv_usec / 1000000.0);
	
	// Las operaciones de lecutra deben ser simultaneas, sin embargo,
	// la ultima empieza 3 segundos mas tarde que la primera por los sleep.
	// Las escrituras deben esperar a las lecturas y ser secuenciales.
	tiempo_estimado = (TIEMPO_CONTAR_CUENTAS + 3) + TIEMPO_CREAR_CUENTA*2;
	
	printf("*************************************** \n");
	if(end-start > tiempo_estimado && end-start < tiempo_estimado+UMBRAL_PERMITIDO){
		printf("********** PRUEBA RRRRWW1 OK! ********* \n");
		res = TRUE;
	}else{
		printf("********** PRUEBA RRRRWW1 ERR ********* \n");
		res = FALSE;
	}
	printf("*************************************** \n");
	printf("********** FIN PRUEBA RRRRWW1 ********* \n");
	printf("*************************************** \n");
	
	return res;
}


/*
 * En esta prueba se lanzan cuatro operaciones de lectura 
 * seguidas de dos de escritura (borrar cuenta).
 */
int pruebaRRRRWWborrar(){
	int i;
	pthread_t th_prueba[MAX];
	void *st1;
	char cuenta[MAX][128];
	struct timeval start_time,end_time;
	double start,end;
	int res;
	int tiempo_estimado;
	
	printf("\n\n");
	printf("*************************************** \n");
	printf("************ PRUEBA RRRRWW2 *********** \n");
	printf("*************************************** \n");
	
	// Se mide el tiempo en el que comienza la prueba
	gettimeofday(&start_time, NULL);
	start = start_time.tv_sec + (start_time.tv_usec / 1000000.0);
	
	// Se crean los 6 hilos (4 de escritura y dos de lectura)
	// Dormimos un segundo entre cada creación para asegurar el orden
	for (i=0;i<MAX;i++){
		sprintf(cuenta[i], "cuenta%d", i);
	}
	pthread_create (&th_prueba[0], NULL, hilo_contar_cuentas, cuenta[0]);
	sleep(1);
	pthread_create (&th_prueba[1], NULL, hilo_contar_cuentas, cuenta[1]);
	sleep(1);
	pthread_create (&th_prueba[2], NULL, hilo_contar_cuentas, cuenta[2]);
	sleep(1);
	pthread_create (&th_prueba[3], NULL, hilo_contar_cuentas, cuenta[3]);
	sleep(1);
	pthread_create (&th_prueba[4], NULL, hilo_borrar_cuenta, cuenta[4]);
	sleep(1);
	pthread_create (&th_prueba[5], NULL, hilo_borrar_cuenta, cuenta[5]);
	sleep(1);
	// Se espera a que finalicen los 6 hilos
	for (i=0;i<MAX;i++){
		pthread_join (th_prueba[i], (void **) &st1);
	}
	
	// Se toma el tiempo de fin
	gettimeofday(&end_time, NULL);
	end = end_time.tv_sec + (end_time.tv_usec / 1000000.0);
	
	// Las operaciones de lecutra deben ser simultaneas, sin embargo,
	// la ultima empieza 3 segundos mas tarde que la primera por los sleep.
	// Las escrituras deben esperar a las lecturas y ser secuenciales.
	tiempo_estimado = (TIEMPO_CONTAR_CUENTAS + 3) + TIEMPO_BORRAR_CUENTA*2;
	
	printf("*************************************** \n");
	if(end-start > tiempo_estimado && end-start < tiempo_estimado+UMBRAL_PERMITIDO){
		printf("********** PRUEBA RRRRWW2 OK! ********* \n");
		res = TRUE;
	}else{
		printf("********** PRUEBA RRRRWW2 ERR ********* \n");
		res = FALSE;
	}
	printf("*************************************** \n");
	printf("********** FIN PRUEBA RRRRWW2 ********* \n");
	printf("*************************************** \n");
	
	return res;
}


/* Método main que se ejecutará */
int main(){
	int i = 0;
	// Se inicializa el banco
	concurrente_init();

	// Se pasan las pruebas que se desee
	// NOTA: si se desea que la base de datos del banco quede en un estado estable
	// es recomendable ejecutar siempre una operacion de creacion y una de borrado
	// del mismo tipo (por ejemplo WWWWWWcrear y WWWWWWborrar) y a ser posible 
	// en este orden para que se puedan borrar las cuentas creadas previamente
	pruebaWWWWWWcrear();
	pruebaWWWWWWborrar();
	pruebaRRRRRR();
	pruebaWWWWRRcrear();
	pruebaWWWWRRborrar();
	pruebaRRRRWWcrear();
	pruebaRRRRWWborrar();
	
	for(i = 0; i < 1000; i++){
		if(i % 100 == 0){
			fprintf(stderr,"i: %d \n",i);
		}
		if(pruebaWWWWRRcrear() != TRUE){
			fprintf(stderr,"ERROR!!!!!!!!!!!!!!!!!!!!!! \n");
		}
		if(pruebaWWWWRRborrar() != TRUE){
			fprintf(stderr,"ERROR!!!!!!!!!!!!!!!!!!!!!! \n");
		}
	}
	
	
	// Se destuye el banco
	concurrente_destroy();

	return 0;
}
