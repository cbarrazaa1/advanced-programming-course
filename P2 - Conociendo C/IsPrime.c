#include <stdio.h>
#include <stdbool.h>

bool isPrime(int num) {
  if (num <= 1) {
    return false;
  }

  for (int i = 2; i < num; i++) {
    if (num % i == 0) {
      return false;
    }
  }

  return true;
}

int main(int argc, const char** argv) {
  int num = 0;
  printf("Enter number to check if prime: ");
  scanf("%i", &num);

  printf("%s", isPrime(num) ? "True" : "False");
}