STD = -std=c99
COMPILER = gcc
LIB = build/lib/genericlib.a
I = -Iinclude
OPTIONS = -Wall -Wpedantic -Wno-unused-result -O0 -g
OPTIMIZED = -Wall -Wpedantic -Wno-unused-result -Ofast -g
OBJ = build/obj
BUILDER = ar rv

# ARQUIVOS .c
FILES = no pilha

# ARQUIVOS FINAIS .EXE
# (TEM QUE TER O ARQUIVO .C PARA COMPILAR)
EXES = 14_2 14_3

all: compile library exe

compile:
	for file in $(FILES) ; do \
		$(COMPILER) $(STD) -c src/$$file.c $(I) -o $(OBJ)/$$file.o ; \
	done

library:
	for file in $(FILES); do \
		$(BUILDER) $(LIB) $(OBJ)/$$file.o ; \
	done

exe:
	for e in $(EXES) ; do \
		$(COMPILER) $(STD) $(OPTIONS) $$e.c $(LIB) $(I) -o build/$$e.exe ; \
	done