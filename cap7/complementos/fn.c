#include <stdio.h>
#include <assert.h>

// fn(k, 0) -> k,
// fn(k, 1) -> 1
int f(int k, int b) {
    return k * (1 - b) + b;
    // return k - b*k + b;
}

int main() {
  int k = 5;
  int resultado = f(k, 1);
  printf("f(%d, 1) = %d\n", k, resultado);
  assert(resultado == 1);

  resultado = f(k, 0);
  printf("f(%d, 0) = %d\n", k, resultado);
  assert(resultado == k);

  return 0;
}
