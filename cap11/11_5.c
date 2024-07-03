# include "separa.h"
# include "vec.h"

void quicksort(int p, int r, int v[])
{
    int j;
    while (p < r)
    {
        j = separacao(p ,r ,v);
        if (j - p < r - j) {
            quicksort(p, j-1, v);
            p = j+1;
        } else {
            quicksort(j+1, r, v);
            r = j - 1;
        }
    }
}

/* 11.5.1 A seguinte versão do algoritmo quicksort consta
* na primeira edição do livro de Cormen et al. [5]. 
* Verifique que ela se baseia na formulação (11.1) do
* problema da separação (Seção 11.1). Dê os invariantes
* do while externo. */
void quicksortCLR(int p, int r, int v[])
{
    int c = v[p], i = p - 1, j = r + 1, t;
    if (p < r)
    {
        /* v[p..j-1] <= v[j] < v[j+1..r] */
        while (1) {
            do --j; while (v[j] > c);
            do ++i; while (v[i] < c);
            if (i >= j) break;
            t = v[i], v[i] = v[j], v[j] = t;
        }
        quicksortCLR(p, j, v);
        quicksortCLR(j+1, r, v);
    }
}

/* 11.5.2 A versão abaixo do Quicksort é semelhante à do livro
* de Sedgewick [18]. Formule o problema da separação que esta
* versão resolve. Dê os invariantes do while externo*/
/* R: ele separa exatamente no meio o vetor */
void quicksortS(int p, int r, int v[])
{
    int c = v[(p+r)/2], i = p, j = r, t;
    if (p < r)
    {
        /*v[p..j-1] <= v[j] = v[(p+r)/2] < v[j+1..r]*/
        while(i <= j) 
        {
            while (v[i] < c) ++i;
            while (c < v[j]) --j;
            if (i <= j) 
            {
                t = v[i], v[i] = v[j], v[j] = t;
                ++i, --j;
            }
        }
    }
}

/* 1.5.3 QUICKSORT ALEATORIZADO. Para tentar evitar o comportamento de pior
* caso da função Separa, podemos escolher o pivô aleatoriamente, recorrendo
* à função InteiroAleatório (veja Apêndice I): */
/*obs: substitui InteiroAleatório pelo nome rndint*/
int rndint(int a, int b)
{
    double r, x, R = RAND_MAX;
    int i;
    r = rand();
    x = r / (R+1);
    i = x * (b-a+1);
    return a+i;
}

int rndsep(int p, int r, int v[])
{
    int i, t;
    i = rndint(p, r);
    t = v[p], v[p] = v[i], v[i] = t;
    return separacao(p, r, v);
}

void rndquicksort(int p, int r, int v[])
{
    int j;
    while (p < r)
    {
        j = rndsep(p ,r ,v);
        if (j - p < r - j) {
            quicksort(p, j-1, v);
            p = j+1;
        } else {
            quicksort(j+1, r, v);
            r = j - 1;
        }
    }
}

/* 11.5.6 Familiarize-se com a função qsort da biblioteca
* stdlib (veja Seção K.1)*/

/* a e b são read-only pointers
* a função retorna positivo se a > b, 0 se a == b
* ou negativo se a < b*/
int compar(const void *a, const void *b)
{
    return ( *(int*)a - *(int*)b );
}

int main(void)
{
    int vetor[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int vetor2[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int expected[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    rndquicksort(0, 9, vetor);
    assert_vec(vetor, expected, 0, 10);

    qsort(vetor2, 10, sizeof(int), compar);
    assert_vec(vetor2, expected, 0, 10);
    printf("OK");
}
