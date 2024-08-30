OPTIONS = -Wall -Wpedantic -Wno-unused-result -O0 -g
FILES = 13_2 13_3 13_4

all: exe

exe:
	for file in $(FILES) ; do \
		gcc $(OPTIONS) $$file.c -o build/$$file.exe ; \
	done