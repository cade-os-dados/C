#include "fatorial.h"

int fatorial(int n)
{
    int fatorial = n;
    while (n > 2)
    {
        n--;
        fatorial = fatorial * n;
    }
    return fatorial;
}
