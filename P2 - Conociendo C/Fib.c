#include <stdio.h>
#include <stdlib.h>

void printFibonacci(int n) {
  int* dp = malloc(sizeof(int) * (n + 1));
  dp[0] = 0;
  dp[1] = 1;

  for (int i = 2; i <= n; i++) {
    dp[i] = dp[i - 1] + dp[i - 2];
  }

  for (int i = 1; i <= n; i++) {
    printf("%i ", dp[i]);
  }
  printf("\n");

  free(dp);
}

int main(int argc, const char** argv) {
  int n = 0;
  printf("Enter how many fibonacci numbers you want: ");
  scanf("%i", &n);

  while (n <= 0) {
    printf("Please enter number greater than 0: ");
    scanf("%i", &n);
  }

  printFibonacci(n);
}