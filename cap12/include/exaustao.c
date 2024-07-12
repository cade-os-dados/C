#include "exaustao.h"
#include "vec.h"

vec2 init_vec2(int n, int c)
{
    vec2 vetor;
    vetor.x = malloc(sizeof(int)*n*c);
    vetor.c = c;
    vetor.n = 0;
    return vetor;
}

void insert_vec2(vec2 *vetor, int *insertion)
{
    int pos = vetor -> c * vetor -> n;
    copy_vec2(insertion, vetor -> x, pos, pos + vetor -> c);
    (vetor -> n)++;
}

int *getPtr(vec2 vetor, int i)
{
    return &vetor.x[i * vetor.c];
}

int verifica_sequencia(int *seq, vec2 exaust)
{
    int eq = 0;

    // verificar se a sequencia bate com algum
    // subvetor de exaust(vec2)
    for (int i = 0; i < exaust.n; i++)
    {
        int *ptr = getPtr(exaust, i);
        eq =  eq_vec(seq, ptr, exaust.c);
        if (eq == 1) return 1;
    }
    return 0;
}