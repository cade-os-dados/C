#include "separa.h"

void assert_separada(int v[], int n)
{
    int meio;
    for (int i = 0; i < n; i++)
        if (v[i] > 0) {meio = i; break;}
    for (int i = 0; i < meio; i++)
        assert(v[i] <= 0);
    for (int i = meio; i < n; i++)
        assert(v[i] > 0);
}

void assert_separada_j(int v[], int n, int j)
{
    for (int i = 0; i < j; i++) assert (v[i] <= v[j]);
    for (int i = j+1; i < n; i++) assert (v[i] > v[j]);
}

int separacao(int p, int r, int v[])
{
    int c, j, k, t;
    c = v[r]; j = p;
    for (k = p; k < r; k++)
        if (v[k] <= c)
        {
            t = v[j], v[j] = v[k], v[k] = t;
            j++;
        }
    v[r] = v[j], v[j] = c;
    return j;
}

void strswap(char *t, char *c1, char *c2)
{
    strcpy(t, c1);
    strcpy(c1, c2);
    strcpy(c2, t);
}

int strsep(int p, int r, char** v)
{
    char *c, *t;
    int j = p, k;

    int n = strlen(v[0]);
    c = malloc(sizeof(char) * n);
    t = malloc(sizeof(char) * n);

    strcpy(c, v[r]);
    for (k = p; k < r; k++)
    {
        if (strcmp(v[k], c) <= 0)
        {
            strswap(t, v[j], v[k]);
            j++;
        }
    }
    strcpy(v[r], v[j]);
    strcpy(v[j], c);
    return j;
}