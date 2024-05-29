# include <stdlib.h>
#include <assert.h>
# include <stdio.h>

/* 9.3.1 Mostre que o consumo total de tempo de Intercala é proporcional
* a n em cada "rodada" de mergesort */

/* O algoritmo irá percorrer de p..r uma vez para ordenar
* o vetor e outra vez para copiar o vetor ordenado. Supondo
* p..r = n, então o algoritmo é proporcional a n*/

/* 9.3.2 INVOCAÇÕES REPETIDAS DE MALLOC. Durante uma execução de Mergesort
* (Seção 9.2), a função Intercala é invocada muitas vezes e cada
* execução de Intercala invoca as funções malloc e free. Para evitar
* as repetidas execuções de malloc e free, escreva uma versão da 
* função Mergesort que incorpore o código da função de intercalação
* e invoque malloc e free uma só vez. */

void intercala (int p, int q, int r, int v[], int *w){
    int i, j, k;
    
    i = p; j = q; k = 0;
    while (i < q && j < r){
        if (v[i] <= v[j]) w[k++] = v[i++];
        else w[k++] = v[j++];
    }
    while (i < q) w[k++] = v[i++];
    while (j < r) w[k++] = v[j++];
    for (i = p; i < r; i++) v[i] = w[i-p];
}

void mergesort(int p, int r, int v[])
{
    int *w = malloc((r-p) * sizeof(int));
    if (p < r-1){
        int q = (p+r)/2;
        mergesort(p, q, v);
        mergesort(q, r, v);
        intercala(p, q, r, v, w);
    }
    free(w);
}

/* 9.3.5 ORDEM DECRESCENTE. Escreva uma versão do algoritmo Mergesort
* que rearranje um vetor v[p..r-1] em ordem decrescente. (Será preciso
* reescrever o algoritmo da intercalação.) */
void superintercala (int p, int q, int r, int v[], int *w, int flip){
    int i, j, k;
    
    i = p; j = q; k = 0;
    while (i < q && j < r){
        if ( (v[i] <= v[j]) ^ flip) w[k++] = v[i++];
        else w[k++] = v[j++];
    }
    while (i < q) w[k++] = v[i++];
    while (j < r) w[k++] = v[j++];
    for (i = p; i < r; i++) v[i] = w[i-p];
}

void supermergesort(int p, int r, int v[], int flip)
{
    int *w = malloc((r-p) * sizeof(int));
    if (p < r-1){
        int q = (p+r)/2;
        supermergesort(p, q, v, flip);
        supermergesort(q, r, v, flip);
        superintercala(p, q, r, v, w, flip);
    }
    free(w);
}


int main(void)
{
    int vetor[10] = {5,12, 3, 14, 105, 99, 7, 44, 13, 12};
    int expected[10] = {3, 5, 7, 12, 12, 13, 14, 44, 99, 105};
    mergesort(0, 10, vetor);
    for (int i = 0; i < 10; i++)
        assert (vetor[i] == expected[i]);

    int expected2[10] = {105, 99, 44, 14, 13, 12, 12, 7, 5, 3};
    supermergesort(0, 10, vetor, 1);

    for (int i = 0; i < 10; i++)
        assert (vetor[i] == expected2[i]);
        
    printf("OK");
}