STD = -std=c99

OPTIONS = -Wall -Wpedantic -Wno-unused-result -O0 -g
OPTIMIZED = -Wall -Wpedantic -Wno-unused-result -Ofast -g

all: separa vec library 11_1 11_2

separa: 
	gcc -c include/separa.c -o build/separa.o

vec:
	gcc -c include/vec.c -o build/vec.o

library: 
	ar ruv cap11lib.a build/separa.o build/vec.o 

11_1:
	gcc $(STD) $(OPTIONS) 11_1.c cap11lib.a -Iinclude -o build/11_1.exe

11_2:
	gcc $(STD) $(OPTIONS) 11_2.c cap11lib.a -Iinclude -o build/11_2.exe