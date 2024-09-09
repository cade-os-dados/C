#include "vec.h"
#include "particoes.h"
#include "permutacao.h"
#include "bench.h"

/* generate bin https://github.com/cade-os-dados/cset99*/
#include "cset99/set.h"
#include "cset99/safearray.h"

typedef struct vecPointer
{
    int* ptr;
    int len;
} vptr;

void print_subconjunto(int* v, int i, int f)
{
    printf("{ ");
    while(i < f){
        printf("%d ", v[i]); i++;
    }
    printf("}");
}

void print_last_subconjunto(int* v, int n)
{
    for(int i = 0; i<n;i++)
        printf("{ %d } ", v[i]);
    printf("\n");
}

void swapVecs(int* ptr1, int* ptr2)
{
    int t = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = t;
}

void print_slices(safeArrayPtr array_slices, int n)
{
    for(int i = 0; i < n;i++)
    {
        print_subconjunto(array_slices[i].array, 0, array_slices[i].n);
    }
}

safeArrayPtr make_slices(int* vetor, int* t, Subconjunto* sub, int n)
{
    safeArrayPtr array_slices = malloc(sizeof(safeArray)*(sub->n));

    
    /* Cria array slices, armazenando ponteiro e a length*/
    copy_vec(vetor, t, n);

    int index=0;
    array_slices[0].array = t;
    for(int i = 0; i < sub -> n; i++)
    {
        array_slices[i].n = (sub->v)[i];
        index += (sub->v)[i];
        if(index == n) break;
        array_slices[i+1].array = t+index;
    }
    return array_slices;
}

safeArrayPtr join_slices(safeArray slices[], int k, int n)
{
    safeArrayPtr r = malloc(sizeof(safeArray));
    r->array = malloc(sizeof(int)*n);
    r->n = n; int m = 0;
    for(int i = 0; i < k; i++)
    {
        safeArray t = slices[i];
        for(int j = 0; j < t.n; j++)
        {
            (r->array)[m] = t.array[j];
            m++;
        }
    }
    return r;
}

/* 12.4.6 PARTIÇÕES. Escreva uma função que imprima uma lista de todas as partições
* do conjunto {1,2,...,n} em m blocos não vazios. Uma tal partição pode ser
* representada por um vetor p[1..n] com valores no conjunto {1,2,...,m} dotado
* da seguinte propriedade: para cada i entre 1 e m, existe pelo menos um j tal
* que p[j] = i. */

/* https://stackoverflow.com/questions/400794/generating-the-partitions-of-a-number

q = { 1: [[1]] }

def decompose(n):
    try:
        return q[n]
    except:
        pass

    result = [[n]]

    for i in range(1, n):
        a = n-i
        R = decompose(i)
        for r in R:
            if r[0] <= a:
                result.append([a] + r)

    q[n] = result
    return result
*/

void tamanhoSubconjunto3(SubconjuntoHead* head)
{
    int a1[1] = {3}; int a2[2] = {2,1}; int a3[3] = {1,1,1};
    Subconjunto* p1 = from_array(a1,1);
    Subconjunto* p2 = from_array(a2,2);
    Subconjunto* p3 = from_array(a3,3);
    head -> next = p1; p1 -> next = p2; 
    p2 -> next = p3; p3 -> next = NULL;
}

/* descreve a quantidade de dados em cada subconjunto */
SubconjuntoHead* tamanhoSubconjunto(int n)
{
    SubconjuntoHead* head = malloc(sizeof(SubconjuntoHead));
    if (n == 3)
        tamanhoSubconjunto3(head);
    else {
        Subconjunto* loop = from_array(&n, 1);
        loop -> next = NULL;
        head -> next = loop;
        for(int i = 1; i < n; i++)
        {
            int pivot = n - i;
            SubconjuntoHead* r = tamanhoSubconjunto(i);
            filterp0(r, pivot);
            if (r != NULL)
            {
                pushp0all(r, pivot);
                appendsub(loop, r);
                loop = tailsub(loop);
            }
        }
    }
    return head;
} 

void print_permutacoes_subconjuntos(int* v, Subconjunto* sub, int n)
{
    if(sub->n == 1)
    {
        print_subconjunto(v, 0, n); 
        printf("\n");
    }
    else if (sub->n == n)
    {
        print_last_subconjunto(v, n);
    }
    else
    {
        /* Vetor copia para nao afetar o vetor original*/
        int* vcopy = sqt_vec(n,1);
        int t[n];

        /* Cria array slices, armazenando ponteiro e a length*/
        safeArrayPtr array_slices = make_slices(vcopy, t, sub, n);
        safeqsortElements(array_slices, sub->n);
        safeqsort(array_slices, 0, sub->n - 1);
        
        safeArrayPtr arr = join_slices(array_slices, sub->n, n);
        set mset = begin(*arr);

        while(nextArrangement(vcopy, n))
        {
            copy_vec(vcopy, t, n);
            safeqsortElements(array_slices, sub->n);
            safeqsort(array_slices, 0, sub->n - 1);
            arr = join_slices(array_slices, sub->n, n);
            if(search(mset, *arr) == NULL)
            {
                print_slices(array_slices, sub->n);
                printf("\n");
                insert(mset, *arr);
            }
        }
        free(array_slices);
        free(vcopy);
    }
}

void particoes(int n)
{
    int* seq = sqt_vec(n,1);
    SubconjuntoHead* head = tamanhoSubconjunto(n);
    Subconjunto* tamanho = head -> next;

    while(tamanho != NULL)
    {
        print_permutacoes_subconjuntos(seq,tamanho,n);
        tamanho = tamanho -> next;
    }
}

int main(void)
{
        // 12.4.6
    SubconjuntoHead* head = tamanhoSubconjunto(3);
    printsub(head);

    Subconjunto* myteste = head -> next;
    pushp0(myteste, 10);
    assert((myteste -> v)[0] == 10);
    assert((myteste -> v)[1] == 3);

    filterp0(head, 2);
    printsub(head);

    SubconjuntoHead* h2 = tamanhoSubconjunto(4);
    printf("\n");
    printsub(h2);

    SubconjuntoHead* h3 = tamanhoSubconjunto(5);
    printf("\n");
    printsub(h3);

    benchmark(tamanhoSubconjunto(25));

    particoes(4);
    benchmark(particoes(8));
}