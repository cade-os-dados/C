#ifndef VETOR
#define VETOR

# include <stdio.h>
# include <assert.h>
# include <time.h>
# include <stdlib.h>
# include <string.h>

typedef struct DynamicArray{
    int *valores;
    int capacity;
    int allocated;
    int buffer;
} darray;

typedef struct FixedArray{
    int *val;
    int len;
} farray;

void print_vec(int *, int, int);
void swap(int *, int, int);
void assert_vec(int *, int *, int, int);
int eq_vec(int *, int *, int);
void copy_vec(int *, int *, int);
void copy_vec2(int *, int *, int, int);
int *rnd_vec(int, int);
int *sqt_vec(int, int);
int *tile(int, int);
char **strvec(int n, int m, char array[][m]);
void strlex(int n, char **v);

// struct functions
darray dnew(int, int);
void push(darray *, int);
void dclean(darray *);
void print_darray(darray* d);
void print_by_index(int *, darray *);
farray *fnew(int *, int);
#endif
