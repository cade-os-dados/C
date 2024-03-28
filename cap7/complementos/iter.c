#include <stdio.h>
#include <assert.h>

int power_iterative(int k, int n) {
  int result = 1;
  while (n > 0) {
    if (n % 2 == 1) {
      result *= k;
    }
    k *= k;
    n /= 2;
  }
  return result;
}

int main() {
  int k = 2;
  int n = 5;
  int result = power_iterative(k, n);
  assert(result == 32);
  printf("OK");
}
