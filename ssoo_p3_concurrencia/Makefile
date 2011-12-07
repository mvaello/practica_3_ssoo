#--------------------------
# Variables
#--------------------------
#
MAKE         = make -s
CC           = gcc
SOURCE_PATH  = ./
OBJECTS      = ejemplo_secuencial.c ejemplo_concurrente.c concurrente.c secuencial.c
EXE          = ejemplo_concurrente.exe ejemplo_secuencial.exe

INCLUDE_BASE = ./include/
LIB_BASE     = ./lib/

MYFLAGS      = -Wall -g
MYFLAGSBD	 = 

MYHEADERS    =  -I${INCLUDE_BASE} 
MYLIBS       =  -L${LIB_BASE} -lbd_banco -lpthread


#--------------------------
# Compilation rules                                           
#--------------------------                                   
#                                                               
#                                                                                                                             
all:  $(OBJECTS)
	@echo "                              Compilando "
	@echo -n "                              "
	@echo -n "Ejemplo de Concurrencia [.."
	@$(CC) ejemplo_concurrente.c concurrente.c $(MYFLAGS) $(MYHEADERS) $(MYLIBS) -o ejemplo_concurrente.exe
	@echo "..]"
	@echo "                              Ejemplo Compilado con Exito!"
	@echo ""
	@echo "                              Compilando "
	@echo -n "                              "
	@echo -n "Ejemplo Secuencial [.."
	@$(CC) ejemplo_secuencial.c secuencial.c $(MYFLAGS) $(MYHEADERS) $(MYLIBS) -o ejemplo_secuencial.exe
	@echo "..]"
	@echo "                              Ejemplo Compilado con Exito!"
                                                              
                                                              
clean:
	@echo "                              Eliminando ficheros!"
	@echo -n "                              "
	@rm -f *.o *exe 
	@echo  ""
        
