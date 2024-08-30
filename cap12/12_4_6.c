#include "vec.h"
#include "particoes.h"
#include "bench.h"

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

/*
    {1 2 3} { 4 } -> 4
    {1 2} {3 4} -> 1 
    {1 3} {2 4} -> 1
    {1 4} {2 3} -> 1
    {1 2} {3} {4} -> 1
    {1 3} {2} {4} -> 1
    {1 4} {2} {3} -> 1
    {2 3} {1} {4} -> 1
    {2 4} {1} {3} -> 1
    {3 4} {1} {2} -> 1
*/

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

        vptr array_slices[sub->n];
        
        /* Cria array slices, armazenando ponteiro e a length*/
        int index=0;
        array_slices[0].ptr = vcopy;
        for(int i = 0; i < sub -> n; i++)
        {
            array_slices[i].len = (sub->v)[i];
            index += (sub->v)[i];
            if(index == n) break;
            array_slices[i+1].ptr = vcopy+index;
        }

        /*
            1. calcular quantidade de permutacoes
            2. calcular a ordem das permutacoes
            3. printar todas as permutacoes
        */

        /*
            Alternativa (brute force): criar um set, rearranjar o vetor
            em ordem lexicográfica e validar se a nova combinação
            já foi anteriormente printada
            para o algoritmo de equalizacao precisaremos ordenar
            os subconjuntos, do que tem maior numero de elementos
            para o que tem menor numero de elementos e cada
            subconjunto deve ter seus elementos ordenados
            internamente, assim conseguimos comparar particoes
        */

        for(int i = 0; i < sub->n;i++)
        {
            print_subconjunto(
                array_slices[i].ptr, // vec
                0, //idx i
                array_slices[i].len //idx f
            );   
        }
        printf("\n");

        swapVecs(array_slices[0].ptr, array_slices[1].ptr);
        for(int i = 0; i < sub->n;i++)
        {
            print_subconjunto(
                array_slices[i].ptr, // vec
                0, //idx i
                array_slices[i].len //idx f
            );
        }
        printf("\n");

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

/*
    {1,2,3}
    {{1,2,3}} => 1
    {{1},{2,3}}, {{2},{1,3}}, {{3},{1,2}} => 3
    {{1},{2},{3}} => 1
    soma = 5

    {1,2,3,4}
    {{1,2,3,4}}, => 1
    {{1}, {2,3,4}}, {{2}, {1,3,4}}, {{3}, {1,2,4}}, {{4}, {1,2,3}}, => 4
    {{1,2}, {3,4}}, {{1,3},{2,4}}, {{1,4}, {2,3}} => 3
    {{1,2}, {3}, {4}}, {{1,3}, {2}, {4}}, {{1,4}, {2}, {3}} => 3
    {{1},{2},{3},{4}} => 1
    soma = 12

    {1,2,3,4,5}
    {{1,2,3,4,5}}, => 1
    {{1},{2,3,4,5}}, {{2}, {1,3,4,5}}, {{3}, {1,2,4,5}}, {{4},{1,2,3,5}, {{5}, {1,2,3,4}}}, => 5
    {{1,2}, {3,4,5}}, {{1,3}, {2,4,5}}, {{1,4}, {2,3,5}}, => 3
    {{1,5}, {2,3,4}}, {{2,3}, {1,4,5}}, {{2,4},{1,3,5}}, => 3
    {{2,5}, {1,3,4}}, {{3,4}, {1,2,5}}, {{3,5}, {1,2,4}}, {{4,5}, {1,2,3}} => 4
    {{1,2,3}, {4}, {5}}, {{1,2,4}, {3}, {5}}, {{1,2,5}, {3}, {4}}, {{1,3,4}, {2}, {5}}, => 4
    {{1,3,5}, {2}, {4}}, {{1,4,5}, {2}, {3}}, {{2,3,4}, {1}, {5}}, {{2,3,5}, {1}, {4}} => 4
    {{2,4,5}, {1}, {3}}, {{3,4,5}, {1}, {2}} => 2
    {{1}, {2}, {3}, {4}, {5}} => 1
    soma = 27
    ...
*/

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
}