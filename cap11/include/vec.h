#ifndef VETOR
#define VETOR

# include <stdio.h>
# include <assert.h>
# include <time.h>
# include <stdlib.h>
# include <string.h>

void print_vec(int *, int, int);
void swap(int *, int, int);
void assert_vec(int *, int *, int, int);
int *rnd_vec(int, int);
int *sqt_vec(int);
char **strvec(int n, int m, char array[][m]);
void strlex(int n, char **v);
#endif
