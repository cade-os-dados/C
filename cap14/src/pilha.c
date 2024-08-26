#include "pilha.h"

void* pop(pilha* p)
{
    (p -> idx)--;
    return p -> valores[(p -> idx) + 1];
}

void* get(pilha* p)
{
    return p -> valores[(p -> idx)];
}

void push(pilha* p, void* v)
{
    (p -> idx)++;
    (p -> valores)[p -> idx] = v; 
}