#include <stdio.h>

// M.D.C
int Euclides(int m, int n){
    int r;
    do {
        r = m % n;
        m = n; n = r;
    } while (r != 0);
    return m;
}

int euclides_recursivo(int m, int n){
    int r = m % n;
    m = n; n = r;
    if (r != 0){
        m = euclides_recursivo(m, n);
        return m;
    }
    else 
        return m;
}

int main(){

    int mdc = Euclides(15,60);
    int mdc2 = euclides_recursivo(15,60);
    printf("O M.D.C calculado pela funcao eh: %d \nO M.D.C. calculado pela funcao recursiva eh %d\n", mdc, mdc2);
}