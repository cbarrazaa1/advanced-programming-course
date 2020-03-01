/*
  Author: César Francisco Barraza Aguilar
  ID: A01176786
  Date: 21/Feb/2020
*/
#include <stdio.h>

/*
  factorial
  Calculates the factorial of n.
  @param n Factorial to calculate.
  @return The result of n!.
*/
int factorial(int n) {
  if (n == 0) {
    return 1;
  }

  return n * factorial(n - 1);
}

/*
  fib
  Calculates the Nth number of the Fibonacci sequence.
  @param n Nth number to calculate.
  @return The Nth number of the Fibonacci sequence.
*/
int fib(int n) {
  if (n <= 1) {
    return 1;
  }

  return fib(n - 2) + fib(n - 1);
}

/*
  getUserInput
  Gets necessary input from user to perform calculations.
  @param factorialN Pointer to factorial to calculate.
  @param fibN Pointer to Fibonacci numbers to calculate.
*/
void getUserInput(int* factorialN, int* fibN) {
  printf("Enter factorial to calculate: ");
  scanf("%d", factorialN);

  printf("Enter Fibonacci numbers to calculate: ");
  scanf("%d", fibN);
}

/*
  printOutput
  Prints the calculations required by the program.
  @param factorialN The factorial to calculate.
  @param fibN Fibonacci numbers to calculate.
*/
void printOutput(int factorialN, int fibN) {
  printf("%d! = %d\n", factorialN, factorial(factorialN));
  
  printf("%d Fibonacci numbers: ", fibN);
  for (int i = 0; i <= fibN; i++) {
    printf("%d ", fib(i));
  }
}

/*
  main
  Program entrypoint.
  @param argc Number of console arguments
  @param argv List of console arguments
  @return Exit status code
*/
int main(int argc, const char** argv) {
  int factorialN = 0;
  int fibN = 0;

  getUserInput(&factorialN, &fibN);
  printOutput(factorialN, fibN);
  return 0;
}