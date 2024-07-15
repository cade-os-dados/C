# PADRÃO DO C
STD = -std=c99

# COMPILADOR
COMPILER = gcc

# STATIC LINK LIBRARY
LIB = build/lib/genericlib.a

# FLAG ARQUIVOS DE INCLUSÃO
I = -Iinclude

# OUTRAS OPÇÕES DO COMPILADOR
OPTIONS = -Wall -Wpedantic -Wno-unused-result -O0 -g
OPTIMIZED = -Wall -Wpedantic -Wno-unused-result -Ofast -g

# BUILD DA STATIC LIBRARY
OBJ = build/obj
BUILDER = ar rv

# ARQUIVOS .c
FILES = vec lista busca fatorial permutacao exaustao comb

# ARQUIVOS FINAIS .EXE
# (TEM QUE TER O ARQUIVO .C PARA COMPILAR)
EXES = 12_2 12_3 12_4

all: compile library exe

compile:
	for file in $(FILES) ; do \
		$(COMPILER) -c src/$$file.c $(I) -o $(OBJ)/$$file.o ; \
	done

library:
	for file in $(FILES); do \
		$(BUILDER) $(LIB) $(OBJ)/$$file.o ; \
	done

exe:
	for e in $(EXES) ; do \
		$(COMPILER) $(STD) $(OPTIONS) $$e.c $(LIB) $(I) -o build/$$e.exe ; \
	done
