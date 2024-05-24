# include <stdlib.h>
# include <stdio.h>
# include <assert.h>
# include "include/lista.h"

/* A função recebe vetores crescentes v[p..q-1] e v[q..r-1]
* e rearranja v[p..r-1] em ordem crescente */
void Intercala (int p, int q, int r, int v[]){
    int i, j, k, *w;
    w = malloc((r-p) * sizeof(int));
    i = p; j = q; k = 0;
    while (i < q && j < r){
        if (v[i] <= v[j]) w[k++] = v[i++];
        else w[k++] = v[j++];
    }
    while (i < q) w[k++] = v[i++];
    while (j < r) w[k++] = v[j++];
    for (i = p; i < r; i++) v[i] = w[i-p];
    free (w);
}

/* 9.1.1 A função Intercala está correta
* nos casos extemos p = q e q = r? */
/* Sim, neste caso só irá copiar um dos vetores*/

/*9.1.6 A seguinte alternativa para a função Intercala
* não usa vetor auxiliar. Ela está correta? Quais os
* invariantes do while? Qual o consumo de tempo?*/

/*R: o invariante foi adicionado na função abaixo
* O consumo de tempo é proporcional a n^2
* A função está correta, porém mais parece o algoritmo
* de inserção do que o mergesort*/
void IntercalaSemVetorAuxiliar (int p, int q, int r, int v[])
{
    int i = p, k, t;
    while (i < q && q < r)
    {
        /*v[p..i] é crescente*/
        if (v[i] >= v[q]){
            t = v[q];
            for (k = q-1; k >= i; k--) 
                v[k+1] = v[k];
            v[i] = t;
            q++;
        }
        i++;
    }
}

/* 9.1.7 VERSÃO RECURSIVA. Escreva uma versão recursiva do algoritmo
* da intercalação. Antes convém reformular o problema da seguinte maneira:
* dados vetores crescentes u[0..m-1] e v[0..n-1], produzir um vetor crescente
* w[0..m+n-1] que contenha o resultado da intercalação dos dois vetores*/

typedef struct vecControl{
    int i;
    int n;
    int *vec;
} vecc;

vecc new(int i, int n, int *vec){
    vecc novo;
    novo.i = i; novo.n = n; novo.vec = vec;
    return novo;
}

void print_vecc(vecc vetor){
    int i = 0;
    printf("[ ");
    while (i < vetor.n){
        printf("%d ", vetor.vec[i]);
        i++;
    }
    printf("]\n");
}

void asssert_vecc(vecc vetor, int referencia[]){
    int i = 0;
    while (i < vetor.n){
        assert (vetor.vec[i] == referencia[i]);
        i++;
    }
}

void intercalaRecursiva(vecc u, vecc v, vecc w)
{
    if (u.i == u.n){
        while (w.i != w.n){
            w.vec[w.i] = v.vec[v.i];
            v.i++; w.i++;
        }
    } else if (v.i == v.n){
        while (u.i != u.n){
            w.vec[w.i] = u.vec[u.i];
            u.i++; w.i++;
        }
    } else {
        int valor = u.vec[u.i];
        int valor2 = v.vec[v.i];

        if (valor < valor2){
            w.vec[w.i] = valor;
            u.i++;
        } else{
            w.vec[w.i] = valor2;
            v.i++;
        }
        w.i++;

        intercalaRecursiva(u, v, w);
    }
}

/* 9.1.8 ESTABILIDADE. Um algoritmo de intercalação é estável (veja seção 8.5)
* se não altera a posição relativa de elementos de mesmo valor. A função Intercala
* é estável? Se "v[i] <= v[j]" for trocada por "v[i] < v[j]", a função fica estável?*/

/* R: Sim, se substituir, a função ficará estável, pois para c E p..q
e v E q..r, index(c) < index(v) */

/* 9.1.10 LISTAS ENCADEADAS. Chame de LECR qualquer lista encadeada sem cabeça que contém
* uma sequência crescente de números inteiros. Escreva uma função que intercale duas LECR
* dadas, produzindo assim uma terceira LECR. Sua função não deve alocar novas células na
* memória, mas reaproveitar as células das duas listas dadas. */
celula *intercalaLista(celula *cel1, celula *cel2)
{
    celula *result;
    celula *loop1 = cel1;
    celula *loop2 = cel2;
    
    if (loop1 -> conteudo <= loop2 -> conteudo){
        result = loop1;
        loop1 = loop1 -> seg;
    } else {
        result = loop2;
        loop2 = loop2 -> seg;
    }
    celula *loop = result;

    while (loop1 != NULL && loop2 != NULL){
        if ((loop1 -> conteudo) <= (loop2 -> conteudo)){
            loop -> seg = loop1;
            loop1 = loop1 -> seg;
        } else {
            loop -> seg = loop2;
            loop2 = loop2 -> seg;
        }
        loop = loop -> seg;
    }
    if (loop1 != NULL)
        loop -> seg = loop1;
    if (loop2 != NULL)
        loop -> seg = loop2;

    return result;
}

int main(void){
    // 9.1.7
    int vetor1[6] = {1,6,12,15,21,30};
    int vetor2[4] = {0,3,18,42};
    int vetor3[10];
    int expected[10] = {0, 1, 3, 6, 12, 15, 18, 21, 30, 42};
    vecc u = new(0, 6, vetor1);
    vecc v = new(0, 4, vetor2);
    vecc w = new(0,10, vetor3);

    intercalaRecursiva(u, v, w);
    asssert_vecc(w, expected);
    
    // 9.1.10
    celula *cel1 = from_array(vetor1, 6);
    celula *cel2 = from_array(vetor2, 4);
    celula *cel_expected = from_array(vetor3, 10);
    celula *result = intercalaLista(cel1, cel2);
    assert_eq_celula(result, cel_expected);

    printf("OK");
}