# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include "include/lista.h"
# include <string.h>

void assert_vec(int *arr1, int *arr2, int n)
{
    for (int i = 0; i < n; i++)
        assert (arr1[i] == arr2[i]);
}

void print_vec(int *arr1, int n)
{   
    printf("[ ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr1[i]);
    printf("]\n");
}

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
    // print_vec(v, r);
}

/* Rearranja o vetor v[0..n-1] em ordem crescente */
void mergesortiterativa(int n, int v[], int flip){
    int *w = malloc(n * sizeof(int));
    int p,r;
    int b = 1;
    while (b < n){
        p = 0;
        while (p+b < n){
            r = p + 2*b;
            if (r > n) r = n;
            superintercala(p, p+b, r, v, w, flip);
            p = p + 2*b;
        }
        b = 2*b;
    }
    free(w);
}

/* 9.4.1 SEGMENTOS CRESCENTES MAXIMAIS. A versão iterativa do Mergesort
* começa por quebrar o vetor original em segmentos de comprimento 1.
* Quem sabe é melhor quebrar o vetor em seus segmentos crescentes
* maximais (os segmentos crescentes maximais de 1 2 3 0 2 4 6 4 5 6 7 8 9),
* por exemplo, são 1 2 3, 0 2 4 6 e 4 5 6 7 8 9). Escreva uma versão
* do Mergesort baseada nesta ideia. */

int maximal(int i, int n, int v[]){
    int valor = v[i];
    int k = i+1;
    while (k < n && v[k] >= valor) 
    {
        valor = v[k];
        k++;
    }
    return k;
}

// retorna uma lista com cabeca
celula *segmentos(int n, int v[]){
    int idxmax = 0;
    celula *lista = malloc(sizeof(celula));
    celula *loop = lista;
    while (idxmax < n){
        idxmax = maximal(idxmax, n, v);
        loop = next(loop);
        loop -> conteudo = idxmax;
    }
    loop -> seg = NULL;
    return lista;
}

void mergesortMaximal(int n, int v[])
{
    int *w = malloc(n * sizeof(int));
    celula *indices = segmentos(n, v) -> seg;
    while (indices -> seg != NULL){
        int indice1 = indices -> conteudo;
        int indice2 = indices -> seg -> conteudo;
        superintercala(0, indice1, indice2, v, w, 0 );
        indices = indices -> seg;
    }
    free(w);
}

/* 9.4.2 ORDENAÇÃO DE STRINGS. Escreva uma versão do algoritmo
* Mergesort que coloque um vetor de strings em ordem lexicográfica
* (veja Seção G.3). */
void intercalaString (int p, int q, int r, char **v, char **w, int flip){
    int i = p, j = q, k = 0;
    
    while (i < q && j < r){
        if ( (strcmp(v[i], v[j]) <= 0)  ^ flip) strcpy(w[k++], v[i++]);
        else strcpy(w[k++], v[j++]);
    }
    while (i < q) strcpy(w[k++], v[i++]);
    while (j < r) strcpy(w[k++], v[j++]);
    for (i = p; i < r; i++) strcpy(v[i], w[i-p]);
    // print_vec(v, r);
}

/* Rearranja o vetor v[0..n-1] em ordem crescente */
void mergesortString(int p, int r, char **v, char **w, int flip)
{
    if (p < r-1){
        int q = (p+r)/2;
        mergesortString(p, q, v, w, flip);
        mergesortString(q, r, v, w, flip);
        intercalaString(p, q, r, v, w, flip);
    }
}

char **malloc_string_vec(int n, int min_strlen){
    char **strings;
    strings = malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++){
        strings[i] = malloc(sizeof(char) * min_strlen);
    }
    return strings;
}

void copy_all(char **strings, char **copy, int len){
    for (int i = 0; i < len; i++){
        strcpy(strings[i], copy[i]);
    }
}

void assert_all(char **strings, char **assertion, int len){
    for (int i = 0; i < len; i++){
        assert(strcmp(strings[i], assertion[i]) == 0);
    }
}

int main(void)
{
    int vetor[10] = {5,12, 3, 14, 105, 99, 7, 44, 13, 12};
    int expected[10] = {3, 5, 7, 12, 12, 13, 14, 44, 99, 105};
    int expected2[10] = {105, 99, 44, 14, 13, 12, 12, 7, 5, 3};

    mergesortiterativa(10, vetor, 0);
    assert_vec(vetor, expected, 10);

    mergesortiterativa(10, vetor, 1);
    assert_vec(vetor, expected2, 10);

    int teste[10] = {3, 5, 12, 5, 10, 20, 12, 15, 17, 20};
    int sorted[10] = {3, 5, 5, 10, 12, 12, 15, 17, 20, 20};
    int array_exptected[3] = {3, 6, 10};

    celula *lista = segmentos(10, teste);
    celula *cel_expected = from_array(array_exptected, 3);
    assert_eq_celula(lista -> seg, cel_expected);

    // 9.4.1
    mergesortMaximal(10, teste);
    assert_vec(teste, sorted, 10);

    // 9.4.2
    char **strings = malloc_string_vec(5, 10);
    char **w = malloc_string_vec(5, 10);
    char *strings_copy[5] = {"banana", "maca", "qiwi", "laranja", "uva"};
    char *expected_strings[5] = {"banana", "laranja", "maca", "qiwi", "uva"};

    copy_all(strings, strings_copy, 5);
    mergesortString(0, 5, strings, w, 0);
    assert_all(strings, expected_strings, 5);

    printf("OK");
}