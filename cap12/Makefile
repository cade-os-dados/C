STD = -std=c99

OPTIONS = -Wall -Wpedantic -Wno-unused-result -O0 -g
OPTIMIZED = -Wall -Wpedantic -Wno-unused-result -Ofast -g
LIB = cap12lib.a
I = -Iinclude
COMPILER = gcc
LIB-BUILDER = ar rv
OBJ = build/obj

all: vec lista ordenacao busca library 12_2 12_3 12_4

vec:
	$(COMPILER) -c include/vec.c -o $(OBJ)/vec.o

lista:
	$(COMPILER) -c include/lista.c -o $(OBJ)/lista.o

ordenacao:
	$(COMPILER) -c include/ordenacao.c -o $(OBJ)/ordenacao.o

busca:
	$(COMPILER) -c include/busca.c -o $(OBJ)/busca.o

library: 
	$(LIB-BUILDER) $(LIB) $(OBJ)/vec.o $(OBJ)/lista.o $(OBJ)/ordenacao.o $(OBJ)/busca.o

12_2:
	$(COMPILER) $(STD) $(OPTIONS) 12_2.c $(LIB) $(I) -o build/12_2.exe

12_3:
	$(COMPILER) $(STD) $(OPTIONS) 12_3.c $(LIB) $(I) -o build/12_3.exe

12_4:
	$(COMPILER) $(STD) $(OPTIONS) 12_4.c $(LIB) $(I) -o build/12_4.exe