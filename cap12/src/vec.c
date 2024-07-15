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

int eq_vec(int *ptr1, int *ptr2, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (ptr1[i] != ptr2[i])
            return 0;
    }
    return 1;
}

void copy_vec(int v[], int s[], int n)
{
    n = n-1;
    while (n >= 0)
    {
        s[n] = v[n];
        n--;
    }
}

void copy_vec2(int *sub, int *v, int ini, int n)
{
    int i = 0;
    while (ini < n)
    {
        v[ini] = sub[i];
        i++;
        ini++;
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
int *sqt_vec(int N, int shift)
{
    int *vetor = malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++)
        vetor[i] = i + shift;
    return vetor;
}

/* retorna um vetor de tamanho N com todos os seus valores iguais a V*/
int *tile(int N, int V)
{
    int *v = malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++)
        v[i] = V;
    return v;
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

darray dnew(int capacity, int buffer_size)
{
    darray d;
    d.valores = malloc(sizeof(int) * capacity);
    d.capacity = capacity;
    d.allocated = 0;
    d.buffer = buffer_size;
    return d;
}

void push(darray *d, int value)
{
    if (d -> allocated == d -> capacity)
    {
        d -> capacity = d -> capacity + d -> buffer;
        d -> valores = realloc(d -> valores, ( d -> capacity) * sizeof(int));
    }

    int index = d -> allocated;
    (d -> valores)[index] = value;
    d -> allocated = index + 1;
}

void dclean(darray *d)
{
    d->valores = realloc(d->valores, 0);
    d -> allocated = 0;
    d -> capacity = 0;
}

void print_darray(darray* d)
{
    printf("[ ");
    for (int i = 0; i < d -> allocated; i++)
    {
        printf("%d ", (d -> valores)[i]);
    }
    printf("]\n");
}

void print_by_index(int* v, darray* d)
{
    printf("[ ");
    for (int i = 0; i < d -> allocated; i++)
    {
        printf("%d ", v[d -> valores[i]]);
    }
    printf("]\n"); 
}

farray *fnew(int *val, int len)
{
    farray *n = malloc(sizeof(farray));
    n -> val = malloc(sizeof(int) * len);
    copy_vec(val, n -> val, len);
    n -> len = len;
    return n;
}