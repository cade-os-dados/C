#pragma once

typedef struct VetorBidimensional
{
    int *x; // valores
    int c; // corte
    int n; // quantidade de vetores inseridos
} vec2;

vec2 init_vec2(int n, int c);
void insert_vec2(vec2 *, int *);
int *getPtr(vec2, int);
int verifica_sequencia(int *, vec2);