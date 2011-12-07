#include <stdlib.h>
#include <stdio.h>
#include "bd_banco.h"
#include "secuencial.h"

int secuencial_init(){
	int ret;
	
	ret = db_banco_init();
 
	return ret;
}

int secuencial_destroy(){
	int ret;	
	
	ret = db_banco_destroy();

	return ret;
}

int secuencial_crear_cuenta(char *cuenta){
	int ret;
	int size;
	void *st_int;

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

	return ret;
}

int secuencial_obtener_num_cuentas(int *num_cuentas){
	int ret;
	int num_cuentas_aux = 0;
	
	// Se obtiene el número de cuentas del BD utilizando la librería proporcionada
	ret = db_banco_obtener_num_cuentas(&num_cuentas_aux);

	*num_cuentas = num_cuentas_aux;
	
	return ret;
}

int secuencial_borrar_cuenta(char *cuenta){
	int ret, size;
	void *st_int;

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

	return ret;
}

int secuencial_incrementar_saldo(char *cuenta, int saldo, int *saldo_actualizado){
	int ret, size;
	void *st_int;

	int saldo_aux=0;
	
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

int secuencial_decrementar_saldo(char *cuenta, int saldo, int *saldo_actualizado){
	int ret, size;
	void *st_int;

	int saldo_aux=0;
	
	// Se obtienen los datos internos para trabajar con ellos
	ret = db_banco_obtener_datos_internos(cuenta, &st_int, &size);
	if (ret == 0){
		// Se obtiene el saldo actual de la cuenta utilizando la librería proporcionada
		ret = db_banco_obtener_saldo(cuenta, &saldo_aux);

		// Se decrementa el saldo
		saldo_aux -= saldo;

		// Se actualiza el saldo de la cuenta utilizando la librería proporcionada
		ret = db_banco_actualizar_cuenta(cuenta, saldo_aux);
		*saldo_actualizado = saldo_aux;

	}

	return ret;
}

int secuencial_obtener_saldo(char *cuenta, int *saldo){
    int saldo_aux=0;
	int ret, size;
	void *st_int;

	// Se obtienen los datos internos para trabajar con ellos
	ret = db_banco_obtener_datos_internos(cuenta, &st_int, &size);
	if (ret == 0){
	
		// Se obtiene el saldo actual de la cuenta utilizando la librería proporcionada
		ret = db_banco_obtener_saldo(cuenta, &saldo_aux);
		*saldo = saldo_aux;
			
	}

    return ret;

}
