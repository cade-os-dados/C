#include "include/vec.h"
#include <stdlib.h>

/* Rearranja o vetor v[0..n-1] em ordem crescente */
void selecao (int n, int v[]) {
    int i, j, min, x;
    for (i = 0; /*A*/ i < n-1; i++){
        min = i;
        for (j=i+1; j < n; j++)
            if (v[j] < v[min]) min = j;
        x = v[i]; v[i] = v[min]; v[min] = x;
    }
}

/* Invariantes do processo iterativo
* 1. v[0..n-1] é uma permutação do vetor original,
* 2. v[0..i-1] está em ordem crescente e
* 3. v[i-1] <= v[j] para j = i, i+1, ..., n-1 */

/* 8.3.1 Que acontece se trocarmos "for (i=0" por
"for (i=1" no código da função seleção? Que acontece
se trocarmos "for (i=0; i < n-1" por "for (i=0; i<n"? */

/* R: se trocar i = 0 por i = 1, então só funcionará
* se o primeiro elemento já for o menor elemento.
* Se trocarmos n-1 por n então fará uma comparação
* desnecessária tendo em vista que o último elemento
* que sobrar já é o maior */

/* 8.3.2 Troque "v[j] < v[min]" por "v[j] <= v[min]" no código
* de seleção. A nova função continua produzindo uma ordenação
* crescente de v[0..n-1]? */

void selecaoAlternativa (int n, int v[]) {
    int i, j, min, x;
    for (i = 0; /*A*/ i < n-1; i++){
        min = i;
        for (j=i+1; j < n; j++)
            if (v[j] <= v[min]) min = j;
        x = v[i]; v[i] = v[min]; v[min] = x;
    }
}

/* R: funciona, ele só faz uma atribuição a mais
* desnecessariamente caso hajam dados repetidos */

/* 8.3.3 ORDEM DECRESCENTE. Escreva uma função que permute os
* elementos de um vetor v[0..n-1] de modo que eles fiquem em
* ordem decrescente. */

void permutar(int i, int j, int v[]){
    // i e j são indices
    int x = v[i];
    v[i] = v[j];
    v[j] = x;
}

void decrescente (int v[], int n){
    int i, j, idx_max;
    for (i = 0; i < n - 1; i++){
        idx_max = i;
        for (j=i+1; j < n; j++)
            if (v[j] > v[idx_max]) idx_max = j;
        permutar(idx_max, i, v);
    }
}

/* 8.3.4 VERSÃO RECURSIVA. Escreva uma versão recursiva do
* algoritmo de ordenação por seleção */

void selecaoRecur (int v[], int n){
    if (n > 1){
        int max = n-1;
        for (int i = n-2; i >= 0; i--){
            if (v[i] > v[max]) max = i;
        }
        permutar(max, n-1, v);
        selecaoRecur(v, n-1);
    }
}

/* 8.3.5 ANIMAÇÕES. Veja animações do algoritmo de seleção
* nas páginas de Harrison [8] e Morin [13] */

/* Leia o verbete Selection sort na Wikipedia [21] */

int main(void){
    int v[6] = {5, 6, 12, 7, 3, 15};
    int vetor_esperado[6] = {3, 5, 6, 7, 12, 15};

    selecao(6, v);
    libvec.assert_eq(v, vetor_esperado, 6);

    // 8.3.2
    int *v2 = copy_vec(v, 6);
    selecaoAlternativa(6, v2);
    libvec.assert_eq(v2, vetor_esperado, 6);

    // teste com dados repetidos
    int v3[6] = {4, 6, 2, 5, 1, 2};
    int vetor_esperado_2[6] = {1, 2, 2, 4, 5, 6};
    selecaoAlternativa(6, v3);
    libvec.assert_eq(v3, vetor_esperado_2, 6);

    int *v4 = copy_vec(v3, 6);
    selecao(6, v4);
    libvec.assert_eq(v4, vetor_esperado_2, 6);

    decrescente(v, 6);
    int vetor_esperado_3[6] = {15, 12, 7, 6, 5, 3};
    libvec.assert_eq(v, vetor_esperado_3, 6);

    selecaoRecur(v, 6);
    libvec.assert_eq(v, vetor_esperado, 6);

    printf("OK");
}
