#ifndef _CONCURRENTE_H_
#define _CONCURRENTE_H_

/*
 * Incluir el resto de "includes" necesarios
 */
#include "bd_banco.h"

/*
 *  Descripción: función que inicializa los recursos utilizados en 
 *  la biblioteca, así como la base de datos utilizada. Usar solo una 
 *  vez al inicio.
 *  Valor de retorno: 0 -> ok, -1 -> error
 */
int concurrente_init();

/*
 *  Descripción: función que elimina los recursos utilizados en la 
 *  biblioteca, así como los utilizados en la base de datos. Usar solo 
 *  una vez al final del programa.
 *  Valor de retorno: 0 -> ok, -1 -> error
 */
int concurrente_destroy();

/*
 *  Descripción: función que crea una cuenta en la base de 
 *  datos utilizando gestión de la concurrencia. En caso de encontrar
 *  otra cuenta con el mismo nombre, se considera que la creación se
 *  ha realizado con éxito.
 *  Debe mantener la coherencia de la BD. No permite realizar otras 
 *  operaciones al mismo tiempo. 
 *  Entrada: nombre de la cuenta
 *  Valor de retorno: 0 -> ok, -1 -> error
 */
int concurrente_crear_cuenta(char *cuenta);


 /*
 *  Descripción: función que consulta en la base de datos el número 
 *  de cuentas existente utilizando gestión de la concurrencia. 
 *  Debe mantener la coherencia de la BD. Permite realizar otras
 *  operaciones de consulta al mismo tiempo.
 *  Salida: devuelve el número de cuentas existentes en el banco.
 *  Valor de retorno: 0 -> ok, -1 -> error
 */
int concurrente_obtener_num_cuentas(int *num_cuentas);


/*
 *  Descripción: función que borra una cuenta en la base de 
 *  datos utilizando gestión de la concurrencia. En caso de no encontrarse
 *  una cuenta con el mismo nombre, se considera que el borrado se
 *  ha realizado con éxito.
 *  Debe mantener la coherencia de la BD. No permite realizar otras 
 *  operaciones al mismo tiempo.
 *  Entrada: nombre de la cuenta
 *  Valor de retorno: 0 -> ok, -1 -> error
 */
int concurrente_borrar_cuenta(char *cuenta);

/*
 * Descripción: función que incrementa el saldo de una cuenta y devuelve 
 * el saldo actualizado. 
 * Debe permitir actualizar o leer otras cuentas en paralelo.
 * Entrada: nombre de la cuenta y el saldo a actualizar
 * Salida: devuelve el saldo actualizado
 * Valor de retorno: 0 -> ok, -1 -> error (cuenta no encontrada, etc.)
 */
int concurrente_incrementar_saldo(char *cuenta, int saldo, int *saldo_actualizado);


/*
 * Descripción: función que decrementa el saldo de una cuenta y devuelve 
 * el saldo actualizado
 * Debe permitir actualizar o leer otras cuentas en paralelo.
 * Entrada: nombre de la cuenta y el saldo a actualizar
 * Salida: devuelve el saldo actualizado
 * Valor de retorno: 0 -> ok, -1 -> error (cuenta no encontrada, etc.)
 */
int concurrente_decrementar_saldo(char *cuenta, int saldo, int *saldo_actualizado);


/*
 * Descripción: función que devuelve el saldo de una cuenta
 * Debe permitir actualizar o leer otras cuentas en paralelo.
 * Entrada: nombre de la cuenta
 * Salida: devuelve el saldo actualizado
 * Valor de retorno: 0 -> ok, -1 -> error (cuenta no encontrada, etc.)
 */
int concurrente_obtener_saldo(char *cuenta, int *saldo);

#endif// _CONCURRENTE_H_
