#pragma once
#include <stdlib.h>
#include "vec.h"

typedef struct mlist
{
    int *v;
    int n;
    struct mlist* next;
} Subconjunto;

typedef struct
{
    struct mlist* next;
} SubconjuntoHead;

/*push at position 0*/
void pushp0(Subconjunto* list, int a);
void pushp0all(SubconjuntoHead* head, int a);
/*remove vetores com primeiro valor igual a v*/
void filterp0(SubconjuntoHead* head, int v);

/*cria subconjunto com valores que estao na array*/
Subconjunto* from_array(int vetor[], int n);
/*printa todos os vetores*/
void printsub(SubconjuntoHead* head);
/*adiciona as listas l2 após l1 e remove o cabecalho de l2*/
void appendsub(Subconjunto* tail, SubconjuntoHead* l2);
/*go to the tail*/
Subconjunto* tailsub(Subconjunto* nottail);