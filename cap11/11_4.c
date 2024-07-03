# include "separa.h"
# include "vec.h"

void tailquicksort(int p, int r, int v[])
{
    while (p < r)
    {
        int j = separacao(p, r, v);
        tailquicksort(p, j-1, v);
        p = j+1;
    }  
}

/* 11.4.1 Aplique a função Quicksort a um vetor crescente com n elementos. Mostre
* que o número de comparações entre elementos do vetor é proporcional a n^2. (Veja
* Exercício 11.2.2.) Repita o exercício com vetor decrescente. */
double bench(int n, int* vec)
{
    clock_t start, end;
    start = clock();
    tailquicksort(0, n, vec);
    end = clock();
    return (double) (end - start);
}

/* resultados: 
* normal: 3
* x2: 8
* x5: 71
* x10: 254
* which means,  2,67x / 23,67x / 84,67x
* log2(base2) = 1, x2 = 2
* log5(base2) = 2,3219, x5 = 11,6
* log10(base2) = 3,3219, x10 = 33,21
* a grosso modo está aproximando sim dessa distribuição nlogn
* sabendo que nlogn é só um comportamento e não um resultado exato
*/

/* 11.4.2 ORDENAÇÃO DE STRINGS. Escreva uma versão do algoritmo
* que coloque um vetor de strings em ordem lexicográfica (veja Seção G.3). */
void strquicksort(int p, int r, char **v)
{
    while (p < r)
    {
        int j = strsep(p, r, v);
        strquicksort(p, j-1, v);
        p = j+1;
    }
}

int main(void)
{
    double 
        cpu_time,
        cpu_time_x2,
        cpu_time_x5,
        cpu_time_x10;

    int *vec = sqt_vec(100000);

    cpu_time = bench(1000, vec);
    cpu_time_x2 = bench(2000, vec);
    cpu_time_x5 = bench(5000, vec);
    cpu_time_x10 = bench(10000, vec);

    printf(
        "normal: %f\nx2: %f\nx5: %f\nx10: %f\n", 
        cpu_time, cpu_time_x2, cpu_time_x5, cpu_time_x10
    );

    char ordem[5][10] = {"hello", "ola", "mundo", "vetor", "ordenado"};

    char** strings = strvec(5, 10, ordem);

    strquicksort(0, 4, strings);

    for (int i = 0; i < 5; i++)
        printf("%s ", strings[i]);

    strlex(5, strings);
    printf("\nOK");
}
