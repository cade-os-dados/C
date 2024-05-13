#include "busca.h"

int binaria(int x, int n, int v[]){
    int e, m, d;
    e = -1; d = n;
    while (e < d-1) {
        m = (e+d)/2;
        if (v[m] < x) e = m;
        else d = m;
    }
    return d;
}

const struct search busca = {
    .binaria = binaria
};
