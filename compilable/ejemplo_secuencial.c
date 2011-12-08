#include <stdio.h>
#include <pthread.h>
#include "secuencial.h"


void ejemplo (void) {
	int saldo = 100, saldo_actualizado = 0;
	char *cuenta= "cuenta1";

	printf ("Ejecutando ejemplo secuencial \n");
	
	printf ("Creando cuenta %s. \n", cuenta);
	secuencial_crear_cuenta(cuenta);
	printf ("Cuenta creada %s. \n",cuenta);
	
	printf ("Incrementando saldo en %d euros en cuenta %s. \n",saldo,cuenta);
	secuencial_incrementar_saldo(cuenta, saldo, &saldo_actualizado);
	printf ("Saldo incrementado en cuenta %s, nuevo saldo: %d euros. \n",cuenta,saldo_actualizado);
	
	printf ("Decrementando saldo en %d euros en cuenta %s. \n",saldo,cuenta);
	secuencial_decrementar_saldo(cuenta, saldo, &saldo_actualizado);
	printf ("Saldo decrementado en cuenta %s, nuevo saldo: %d euros. \n",cuenta,saldo_actualizado);	
	
	printf ("Obteniendo saldo de la cuenta %s. \n",cuenta);
	secuencial_obtener_saldo(cuenta, &saldo);
	printf ("Saldo obtenido. La cuenta %s tiene un saldo de %d euros. \n",cuenta,saldo);
	
	printf("Borrando cuenta %s. \n", cuenta);
	secuencial_borrar_cuenta(cuenta);
	printf("Cuenta %s borrada. \n",cuenta);

} 

int main(){

	secuencial_init();
	
	ejemplo();

	secuencial_destroy();

	return 0;
}
