// questao 2.3.2
// diferenca do menor para o maior valor do vetor
// usando recursividade
#ifndef MIN_MAX_H
#define MIN_MAX_H

void min_max(int v[], int n, int mm[2]) {
    if (n == 2) {
        if (v[0] < v[1]) {
            mm[0] = v[0];
            mm[1] = v[1];
        } else if (v[0] > v[1]) {
            mm[0] = v[1];
            mm[1] = v[0];
        } else {
            mm[0] = mm[1] = v[0];
        }
    } else if (n > 2) {
        // Chame recursivamente a função para o restante do vetor
        int sub_mm[2];
        min_max(v + 1, n - 1, sub_mm);

        if (v[0] > sub_mm[1]) {
            sub_mm[1] = v[0];
        }
        if (v[0] < sub_mm[0]) {
            sub_mm[0] = v[0];
        }

        mm[0] = sub_mm[0];
        mm[1] = sub_mm[1];
    }
}

#endif