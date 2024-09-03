OPTIONS = -Wall -Wpedantic -Wno-unused-result -O0 -g
FILES = 15_1 15_2 15_3 15_4
INCLUDE = include

all: exe

exe:
	for file in $(FILES) ; do \
		gcc $(OPTIONS) -I$(INCLUDE) $$file.c -o build/$$file.exe ; \
	done