
==============================================
CODIGO PRACTICA 3 (ASIGNATURA SSOO 2011/2012)
==============================================

Contenido:
- ssoo_p3_concurrencia/
	Directorio con el contenido de la practica 3

- ssoo_p3_concurrencia/lib/
	Directorio con las bibliotecas del sistema

- ssoo_p3_concurrencia/lib/libbd_banco.a
	Biblioteca para el manejo de la base de datos 
	compilada en las aulas de la asignatura

- ssoo_p3_concurrencia/lib/libbd_banco-64bits.a
	Biblioteca para el manejo de la base de datos 
	compilada en en una máquina de 64 bits. Si 
	se quiere utilizar, renombrarla a libbd_banco.a 
	sustituyendo a la anterior.

- ssoo_p3_concurrencia/include/
	Directorio con los ficheros de cabeceras

- ssoo_p3_concurrencia/include/bd_banco.h
	Fichero de cabeceras con las funciones de manejo de la 
	base de datos del banco

- ssoo_p3_concurrencia/include/secuencial.h
	Fichero de cabecera con las funciones de manejor de la librería
	análogas a la que se desea codificar sin control de concurrencia
	
- ssoo_p3_concurrencia/secuencial.c
	Fichero de ejemplo de funcionamiento de la librería sin incluir
	control de concurrencia

- ssoo_p3_concurrencia/include/concurrente.h
	Fichero de cabeceras con las funciones de manejo de la 
	biblioteca que se desea codificar

- ssoo_p3_concurrencia/concurrente.c
	Fichero de base que se solicita para el desarrollo de la practica

- ssoo_p3_concurrencia/ejemplo_secuncial.c
	Fichero de ejemplo con las llamadas secuenciales a la base de 
	datos

- ssoo_p3_concurrencia/ejemplo_concurrente.c
	Fichero de ejemplo que utiliza las funciones descritas en la 
	biblioteca

- ssoo_p3_concurrencia/Makefile
	Fichero de compilacion (para ejecutar "make", para borrar 
	los ficheros "make clean")
