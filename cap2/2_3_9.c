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
    int r;
    if (r != 0){
        r = m % n;
        m = euclides_recursivo(n, r);
        return m;
    }
    else 
        return m;

}

int main(){
    int mdc = Euclides(60, 15);
    int mdc2 = euclides_recursivo(60,15);
    printf("O M.D.C calculado pela funcao eh: %d \n O M.D.C. calculado pela funcao recursiva eh %d", mdc, mdc2);
}