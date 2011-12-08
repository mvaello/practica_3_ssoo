#include <stdio.h>
#include <pthread.h>
#include "concurrente.h"


void *Hilo2 (void *arg) {
	int saldo = 100, saldo_actualizado = 0;
	int num_cuentas;
	char *cuenta= "cuenta1";

	printf ("%s\n", (char *)arg);
	concurrente_obtener_num_cuentas(&num_cuentas);
	concurrente_crear_cuenta(cuenta);	
	concurrente_incrementar_saldo(cuenta, saldo, &saldo_actualizado);	
	//concurrente_incrementar_saldo(cuenta, saldo, &saldo_actualizado);	
	//concurrente_incrementar_saldo(cuenta, saldo, &saldo_actualizado);	
	//concurrente_incrementar_saldo(cuenta, saldo, &saldo_actualizado);	
	concurrente_obtener_saldo(cuenta, &saldo);

	pthread_exit (NULL);
} /* Fin de Hilo */



void *Hilo1 (void *arg) {
	int saldo = 100, saldo_actualizado = 0;
	char *cuenta= "cuenta1";
	int num_cuentas;

	printf ("%s\n", (char *)arg);
	concurrente_obtener_num_cuentas(&num_cuentas);
	concurrente_crear_cuenta(cuenta);
	concurrente_incrementar_saldo(cuenta, saldo, &saldo_actualizado);
	//concurrente_decrementar_saldo(cuenta, saldo, &saldo_actualizado);	
	concurrente_obtener_saldo(cuenta, &saldo);

	pthread_exit (NULL);
} /* Fin de Hilo */




#define MAX 4
int main(){
	int i = 0;
	pthread_t th1[MAX];
	pthread_t th2;
	void *st1;

	concurrente_init();
	
	for (i=0;i<MAX;i++)
		pthread_create (&th1[i], NULL, Hilo1, "Hilo 1");
		pthread_create (&th2, NULL, Hilo2, "Hilo 2");
	for (i=0;i<MAX;i++)
		pthread_join (th1[i], (void **) &st1);
		pthread_join (th2, (void **) &st1);
	printf ("Retorno del hilo: %d\n", (int)((long)st1));	

	concurrente_destroy();

	return 0;
}
