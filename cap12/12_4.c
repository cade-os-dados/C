#include <time.h>

#include "vec.h"
#include "lista.h"
#include "busca.h"
#include "fatorial.h"
#include "permutacao.h"
#include "exaustao.h"
#include "comb.h"

/* Ordem lexicográfica especial: dá preferência a 
* sequências mais longas... */

/* Recebe n >= 1 e imprime, em ordem lexicográfica especial,
* todas as subsequências não vazias de 1,2,...,n */
void subseqlexesp(int n)
{
    int *s, k;
    s = malloc((n+1) * sizeof(int));
    s[1] = 0; k = 1;
    while (1) 
    {
        if (s[k] == n) {
            k-=1;
            if (k == 0) break;
        } else {
            s[k] += 1;
            while (s[k] < n){
                s[k+1] = s[k] + 1;
                k += 1;
            }
        }
        print_vec(s, 1, k+1);
    }
    free (s);
}

/* 12.4.1 ORDEM MILITAR. A lista abaixo (leia a coluna)
* esquerda, depois a do meio, depois a direita) exibe
* as subsequências de 1,2,3,4 em "ordem militar". Analise 
* esta ordem. Escreva uma função que imprima todas as
* subsequências de 1,2,...,n em ordem militar. Escreva duas
* versões: uma iterativa e uma recursiva */
/*
    1           1   3       1   2   3
    2           1   4       1   2   4
    3           2   3       1   3   4
    4           2   4       2   3   4
    1   2       3   4       1   2   3   4
*/

/* Insere v[1..N] = {1..N} */
void seq(int* v, int N)
{
    for(int i = 0; i < N+1; i++)
        v[i] = i+1;
}

void ordem_militar(int n)
{
    int *s = malloc(sizeof(int) * n);

    int k;
    k = s[0] = 0;
    while (k < n-1)
    {
        if (s[k] < n)
            s[k] = s[k]+1;
        else if (s[k-1] < n - 1){
            s[k-1] = s[k-1] + 1;
            s[k] = s[k-1] + 1;
        }
        else {
            int t = 0;
            for (int i = k-1; i > 0; i--)
            {
                if (s[i-1] < s[i] - 1){
                    s[i-1] = s[i-1] + 1;
                    t++;
                }
            }
            if (t == 0){
                k++;
                seq(s, k);
            }
        }
        print_vec(s, 0, k+1);
    }
}

/* 12.4.2 SUBSET SUM. Suponha que você emitiu cheques com os valores
* p1, ..., pn ao longo de um mês. No fim do mês, o banco informa que
* uma quantia T foi descontada de sua conta. Quais dos cheques foram
* descontados? Por exemplo, se p = 61, 62, 63, 64 e T = 125 então só
* há duas possibilidades: ou foram descontados os cheques 1 e 4 ou
* foram descontados os cheques 2 e 3. Esta é uma instância do problema
* subset sum (soma de subconjunto): dado um número T e um vetor p[1..n],
* encontrar todas as subsequências s1, s2, .. sk de 1,2,...,n para as
* quais p[s1]+...+p[sk] = T. Escreva uma função que resolva o problema. */

int next(int *s, int *k, int n, int p)
{
    if (s[*k] < n) {
        s[*k+1] = s[*k] + 1;
        *k+=1;
    } else {
        s[*k-1] += 1;
        *k -= 1;
    }
    if (*k == 0) return 1;
    if (p == 1)
        print_vec(s, 1, *k+1);
    return 0;
}

/* Reescrita da funcao apenas para debug*/
void subseqlex (int n)
{
    int *s, k, t;
    s = malloc((n+1) * sizeof(int));
    s[0] = 0; k = 0;
    while (1) {
        t = next(s, &k, n, 1);
        if (t == 1) break;
    }
    free(s);
}

/* R: agora sim a funcao para calcular se a subset sum é igual a T*/
Subset *subset_sum(int *values, int n, int T)
{
    Subset *result = lnew();
    Subset *loop = result;
    darray d = dnew(0, 16);

    int *s = malloc((n+1) * sizeof(int));
    int k, t;
    s[0] = 0; k = 0;

    while (1)
    {
        t = next(s, &k, n, 0);
        int sum = 0;
        for (int i = 1; i < k+1; i++)
        {
            int idx = s[i] - 1;
            int valor = values[idx];
            push(&d, valor);
            sum += valor;     
        }
        if (sum == T)
        {
            farray *ptr = fnew(d.valores, d.allocated);
            loop -> vec = ptr;
            loop -> next = lnew();
            loop = loop -> next;
        }
        dclean(&d);
        if (t == 1) break;
    }
    free(s);
    loop -> next = NULL;
    return result;
}

/* 12.4.3 COMBINAÇÕES. Escreva uma função que imprima todas as subsequências de
* 1,2,...,n que têm exatamente k termos. (Isso corresponde aos subconjuntos de
* {1,2,...,n} que têm exatamente k elementos.) */
/*R: cabecalho comb.h + asserts na funcao main*/

/* PERMUTAÇÕES. Uma permutação da sequência 1,2,...,n é qualquer rearranjo 
* desta sequência. Por exemplo, as seis permutações de (1,2,3) são (1,2,3),
* (1,3,2), (2,1,3), (2,3,1), (3,1,2) e (3,2,1). Escreva uma função que imprima,
* exatamente uma vez, cada uma das n! permutações de 1,2,...,n.*/

/* v deve ser um vetor crescente */
void arranjar(int *v, int n, int *c, vec2* v2xptr)
{
    print_vec(v, 0, n);
    insert_vec2(v2xptr, v);
    while(nextArrangement(v, n))
    {
        print_vec(v, 0, n);
        (*c)++;

        // verifica se a sequencia esta se repetindo
        assert (verifica_sequencia(v, *v2xptr) == 0);
        insert_vec2(v2xptr, v);
    }
}

void endl() {printf("\n");}

/* 12.4.5 DESARRANJOS. Um desarranjo da sequência 1,2,...,n é qualquer permutação
* desta sequência que muda todos os termos de posição. Em outras palavras, um desarranjo
* de 1,2,...,n é qualquer permutação p1,p2,...,pn de 1,2,...,n tal que pi != i
* para todo i. Por exemplo, os nove desarranjo de (1,2,3,4) são (2,1,4,3), (2,3,4,1),
* (2,4,1,3), (3,1,4,2), (3,4,1,2), (3,4,2,1), (4,1,2,3), (4,3,1,2) e (4,3,2,1). Escreva
* uma função que imprima, exatamente uma vez, cada desarranjo de 1,2,...,n */

/* R: bom, vamos fazer um algoritmo bem lento, mas resolvemos rápido este problema... */
int dessaranjo(int *v, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (v[i] == i+1) return 0;
    }
    return 1;
}

void desarranjos(int *v, int n, int* c)
{
    while(nextArrangement(v, n))
    {
        if (dessaranjo(v, n))
        {
            print_vec(v, 0, n);
            (*c)++;
        }
    }
}

int main(void)
{
    printf("Ordem militar\n");
    ordem_militar(4);
    endl();

    printf("Subsequencias iterativo\n");
    subseqlex(4);
    endl();

    printf("Exercicio dos cheques\n");
    int values[4] = {61, 62, 63, 64};
    Subset *combinations = subset_sum(values, 4, 125);
    Subset *loop = combinations;
    while (loop -> next != NULL)
    {
        print_vec(loop -> vec-> val, 0, loop -> vec-> len);
        loop = loop -> next;
    }
    endl();

    // 12.4.3
    printf("Combinacoes: \n");
    int TAMANHO = 8;
    int *seq = sqt_vec(TAMANHO, 1);
    int K = 4;
    int contador = 0;

    // C(7,3) = 7! / 3! (7-3)! = 7*6*5*4! / 6 * 4! = 7*5 = 35
    // C(8,3) = 8! / 3! (8-3)! = 8*7*6*5! / 6 * 5! = 56
    // C(8,4) = 8! / 4! (8-4)! = 8*7*6*5 / 4! = 56*5/4 = 14*5 = 70
    assert (ncombs(7,3) == 35);
    assert (ncombs(8,3) == 56);
    assert (ncombs(8,4) == 70);

    combine(seq, TAMANHO, K, &contador);
    assert (contador == ncombs(8,4));
    endl();

    // 12.4.4
    printf("Permutacoes: \n");
    int N = 6;
    int total_arranjos = fatorial(N);

    int c = 1;
    int *sqt = sqt_vec(N, 1);
    vec2 v2x = init_vec2(total_arranjos, N);
    arranjar(sqt, N, &c, &v2x);
    printf("n arranjos: %d\n", c);
    assert (c == total_arranjos);
    
    // 12.4.5
    int *seq2 = sqt_vec(4, 1);
    int contador_desarranjo = 0;
    desarranjos(seq2, 4, &contador_desarranjo);
    assert(contador_desarranjo == 9);
    printf("OK\n");
}