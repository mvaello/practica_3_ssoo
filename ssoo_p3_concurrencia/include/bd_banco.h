#ifndef _DB_BANCO_
#define _DB_BANCO_

/*
 * Funcion que inicializa la base de datos. Usar solo una vez al inicio.
 * Entrada:
 * Salida:
 * Valor de retorno: 0 -> ok, -1 -> error
 */
int db_banco_init();       

/*
 * Funcion que elimina los recusos utilizados de la base de datos. 
 * Usar solo una vez al finalizar.
 * Entrada:
 * Salida:
 * Valor de retorno: 0 -> ok, -1 -> error
 */
int db_banco_destroy();

/*
 * Funcion que crea una cuenta.
 * Entrada: nombre de la cuenta
 * Salida: 
 * Valor de retorno: 0 -> ok, -1 -> error
 */
int db_banco_crear_cuenta(char *cuenta);

/*
 * Funcion que devuelve el número de cuentas.
 * Salida: numero de cuentas del banco.
 * Valor de retorno: 0 -> ok, -1 -> error
 */
int db_banco_obtener_num_cuentas(int *num_cuentas);

/*
 * Funcion que borra una cuenta.
 * Entrada: nombre de la cuenta
 * Salida:
 * Valor de retorno: 0 -> ok, -1 -> error
 */
int db_banco_borrar_cuenta(char *cuenta);

/*
 * Función que indica si existe una cuenta.
 * Entrada: nombre de la cuenta a buscar.
 * Salida:
 * Valor de retorno: 1 -> existe, 0 -> No existe
 */
int db_banco_existe_cuenta(char *cuenta);

/*
 * Funcion que actualiza el saldo de una cuenta
 * Entrada: nombre de la cuenta y el saldo de la cuenta
 * Salida:
 * Valor de retorno: 0 -> ok, -1 -> error
 */
int db_banco_actualizar_cuenta(char *cuenta, int saldo);

/*
 * Funcion que devuelve el saldo de una cuenta
 * Entrada: nombre de la cuenta
 * Salida: saldo de la cuenta
 * Valor de retorno: 0 -> ok, -1 -> error
 */
int db_banco_obtener_saldo(char *cuenta, int *saldo);

/*
 * Función que permite asociar una serie de datos a una cuenta concreta.
 * Se puede utilizar para guardar en la cuenta datos relacionados con 
 * la sincronización de procesos ligeros.
 * Entrada: nombre de la cuenta, puntero a los datos y tamaño de los mismos
 * Salida:
 * Valor de retorno: 0 -> ok, -1 -> error
 */
int db_banco_insertar_datos_internos(char *cuenta, void *ptr, int size);

/*
 * Funcion que devuelve datos externos asociados a una cuenta.
 * Entrada: nombre de la cuenta, 
 * Salida: puntero a los datos y tamaño de los mismos
 * Valor de retorno: 0 -> ok, -1 -> error
 */
int db_banco_obtener_datos_internos(char *cuenta, void **ptr, int *size);

#endif //_DB_BANCO_
