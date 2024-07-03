# include "vec.h"

void print_vec(int v[], int i, int n)
{
    printf("[ ");
    for (; i < n; i++) printf("%d ", v[i]); 
    printf("]\n");
}

void swap(int v[], int a, int b)
{
    int valor = v[a];
    v[a] = v[b];
    v[b] = valor;
}

void assert_vec(int v[], int v2[], int i, int n)
{
    for (; i < n; i++)
    {
        assert (v[i] == v2[i]);
    }
}

int *rnd_vec(int N, int max)
{
    srand(time(NULL));
    int *vetor = malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++)
        vetor[i] = rand() % max;
    return vetor;
}

/* vetor sequencial de tamanho N*/
int *sqt_vec(int N)
{
    int *vetor = malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++)
        vetor[i] = i;
    return vetor;
}

char **strvec(int n, int m, char array[][m])
{
    char **vector = malloc(sizeof(char *) * n);

    for (int i = 0; i < n; i++) {
        vector[i] = malloc(sizeof(char) * m);
        strcpy(vector[i], array[i]);
    }
    return vector;
}

// verifica se está em ordem lexicográfica
void strlex(int n, char **v)
{
    for (int i = 1; i < n; i++)
        assert(strcmp(v[i], v[i-1]) > 0);
}   