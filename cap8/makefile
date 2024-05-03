# Exemplo muito simples de arquivo Makefile
# (veja a pagina "Como organizar, compilar e depurar 
# um programa C")


STD = -std=c99
# -std=c99: padrao C99 da linguagem C
# -ansi:    padrao C90 da linguagem C

OPTIONS = -Wall -Wpedantic -Wno-unused-result -O0 -g
# -O0: nao otimiza o codigo ao compilar
# -g:  prepara o terreno para que o gdb possa encontrar bugs

# LIBRARIES = -lm
# necessario no caso de usar math.h


# para produzir o arquivo executavel xxx, 
# basta dizer "make xxx"
all: 8_1 8_2 8_3 8_4

8_1: 8_1.c
	gcc $(STD) $(OPTIONS) 8_1.c -o build/8_1.exe

8_2 : 8_2.c
	gcc $(STD) $(OPTIONS) 8_2.c include/vec.c include/busca.c -o build/8_2.exe

8_3 : 8_3.c
	gcc $(STD) $(OPTIONS) 8_3.c include/vec.c include/busca.c -o build/8_3.exe

8_4 : 8_4.c
	gcc $(STD) $(OPTIONS) 8_4.c include/mystring.c include/lista.c -o build/8_4.exe 

# o que parecem ser espacos no comeco da linha anterior
# sao, na verdade, um unico caractere de tabulacao (\t) 