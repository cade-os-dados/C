# include "separa.h"
# include "vec.h"
# include <stdio.h>

/* 11.1.1 Escreva uma função que rearranje um vetor
* v[p..r] de números inteiros de modo que os elementos
* negativos e nulos fiquem à esquerda e os positivos
* fiquem à direita. Em outras palavras, rearranje o vetor
* de modo que tenhamos v[p..j-1] <= 0 e v[j..r] > 0 para 
* algum j em p..r+1. (Faz sentido exigir que j esteja em p..r?)
* Procure escrever uma função eficiente que não use vetor auxiliar.
* Repita o exercício depois de trocar "v[j..r] > 0" por "v[j..r]>=0" */

/* 11.1.2 Digamos que um vetor v[p..r] está arrumado se existe j em 
* p..r que satisfaz (11.2). Escreva um algoritmo que decida se v[p..r]
* está arrumado. Em caso afirmativo, o seu algoritmo deve devolver o
* valor de j. */

/*R: embora nao muito eficiente, na minha interface separa.h
* tem uma função que faz esta asserção, mas não devolve j*/

void rearranja(int v[], int n)
{
    int j = 0;
    for (int i = 0; i  < n; i++)
    {
        if (v[i] <= 0) {
            swap(v, j, i);
            j++;
        }
    }
}

int main(void)
{
    int vetor[6] = {-1,5,-2,13,0,8};
    rearranja(vetor, 6);
    print_vec(vetor, 0, 6);
    assert_separada(vetor, 6);
    printf("OK");
}
