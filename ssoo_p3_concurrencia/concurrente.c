/*
 * Incluir el resto de "includes" necesarios
 */
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "bd_banco.h"
#include "concurrente.h"

#define MAX_CUENTAS 16 //Se define el máximo de cuentas activas 

pthread_mutex_t mutex; // Para controlar el acceso a las cuentas
pthread_cond_t db_lleno;
pthread_cond_t db_vacio;


int concurrente_init()
{
	int ret;

	/*
	 *  Completar 	
	 */

	ret = db_banco_init();
 
	return ret;
}

int concurrente_destroy()
{
	int ret;
	
	/*
	 *  Completar 	
	 */
		
	ret = db_banco_destroy();

	return ret;
}

int concurrente_crear_cuenta(char *cuenta)
{
	int ret;
	int size;
	void *st_int;
	int n_cuentas = concurrente_obtener_num_cuentas();
	/*
	 *  Completar 	
	 */
	 pthread_mutex_lock(&mutex);
	 while(n_cuentas == MAX_CUENTAS)
	 {
	 	pthread_cond_wait(&db_lleno, &mutex); // Se bloquea para no crear más de 16 cuentas
	 }

	/* ------------------------------------------------- */
	/* ------------------------------------------------- */
	ret = db_banco_existe_cuenta(cuenta);	
	if (ret == 0){
		ret = db_banco_crear_cuenta(cuenta);
		if (ret == 0){
			/* 
			 * Generar datos internos para insertarlos
			 */
			size = 0;
			st_int = NULL;
			ret = db_banco_insertar_datos_internos(cuenta, st_int, size);
		}
	}
	/* ------------------------------------------------- */
	/* ------------------------------------------------- */

	if(n_cuentas == MAX_CUENTAS) // Duda: Al menos una cuenta o tiene que estar lleno ??
	{
		pthread_cond_signal(&db_vacio);
	}

	pthread_mutex_unlock(&mutex);

	return ret;
}

int concurrente_obtener_num_cuentas(int *num_cuentas)
{	
	int ret;
	int num_cuentas_aux = 0;
	
	/*
	 * Completar
	 */

	// Es necesario bloquear la creación de nuevas cuentas a la hora de contar
	

	
	// Se obtiene el n?mero de cuentas del BD utilizando la librer?a proporcionada
	ret = db_banco_obtener_num_cuentas(&num_cuentas_aux);

	*num_cuentas = num_cuentas_aux;
	
	return ret;
}

int concurrente_borrar_cuenta(char *cuenta)
{
	int ret, size;
	void *st_int;
	
	/*
	 *  Completar 	
	 */
	pthread_mutex_lock(&mutex);
	while(n_cuentas == 0)
	{
		pthread_cond_wait(&vacio, &mutex); // Se bloquea porque no hay cuentas
	}


	/* ------------------------------------------------- */
	/* ------------------------------------------------- */
	// Se borra la cuenta de la BD utilizando la librería proporcionada
	ret = db_banco_borrar_cuenta(cuenta);
	if(ret == 0){
		// Se leen los datos internos para resetearlos
		ret = db_banco_obtener_datos_internos(cuenta, &st_int, &size);
		if (ret == 0){
			st_int = NULL;
			size = 0;
			// Se guardan los datos internos reseteados
			ret = db_banco_insertar_datos_internos(cuenta, st_int, size);
		}
	}
	/* ------------------------------------------------- */
	/* ------------------------------------------------- */

	if(n_cuentas == MAX_CUENTAS - 1) // Duda: lleno pero no del todo??
	{
		pthread_cond_signal(&lleno);	// Si aun no se ha llenado la db de cuentas
	}

	pthread_mutex_unlock(&mutex); // Se consume la cuenta

	return ret;
}

int concurrente_incrementar_saldo(char *cuenta, int saldo, int *saldo_actualizado)
{
	int ret, size;
	void *st_int;

	int saldo_aux=0;
	
	/*
	 *  Completar 	
	 */
	
	// Se obtienen los datos internos para trabajar con ellos
	ret = db_banco_obtener_datos_internos(cuenta, &st_int, &size);
	if (ret == 0){
		// Se obtiene el saldo actual de la cuenta utilizando la librería proporcionada
		ret = db_banco_obtener_saldo(cuenta, &saldo_aux);

		// Se incrementa el saldo
		saldo_aux += saldo;

		// Se actualiza el saldo de la cuenta utilizando la librería proporcionada
		ret = db_banco_actualizar_cuenta(cuenta, saldo_aux);
		*saldo_actualizado = saldo_aux;
		
	}

	return ret;
}

int concurrente_decrementar_saldo(char *cuenta, int saldo, int *saldo_actualizado)
{
	int ret, size;
	void *st_int;

	int saldo_aux=0;

	/*
	 *  Completar 	
	 */
	
	// Se obtienen los datos internos para trabajar con ellos
	ret = db_banco_obtener_datos_internos(cuenta, &st_int, &size);
	if (ret == 0){
		// Se obtiene el saldo actual de la cuenta utilizando la librería proporcionada
		ret = db_banco_obtener_saldo(cuenta, &saldo_aux);

		// Se decrementa el saldo
		saldo_aux -= saldo;

		// Se actualiza el saldo de la cuenta utilizando la librerìa proporcionada
		ret = db_banco_actualizar_cuenta(cuenta, saldo_aux);
		*saldo_actualizado = saldo_aux;

	}

	return ret;
}

/*
* La funci?n "concurrente_obtener_saldo" retorna el saldo actual de la cuenta que 
* se desea consultar
*/	


int concurrente_obtener_saldo(char *cuenta, int *saldo)
{
	int saldo_aux=0;
	int ret, size;
	void *st_int;

	/*
	 *  Completar 	
	 */

	

	// Se obtienen los datos internos para trabajar con ellos
	ret = db_banco_obtener_datos_internos(cuenta, &st_int, &size);
	if (ret == 0){
	
		// Se obtiene el saldo actual de la cuenta utilizando la librería proporcionada
		ret = db_banco_obtener_saldo(cuenta, &saldo_aux);
		*saldo = saldo_aux;
			
	}

    return ret;
}
