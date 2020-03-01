/*
  Author: César Francisco Barraza Aguilar
  ID: A01176786
  Date: 25/Feb/2020
*/
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <math.h>

// Structure to hold information needed for LCG algorithm.
typedef struct {
  int a;
  int c;
  time_t seed;
} rand_gen;

/*
  createMSRand
  Creates a random structure with Microsoft's LCG constants.
*/
rand_gen createMSRand(time_t seed) {
  rand_gen gen = {214013, 2531011, seed};
  return gen;
}

/*
  lcgRand
  Generates a random number from 0 to 1.
  @param gen Generator structure holding necessary data.
  @return A random number between 0 and 1.
*/
float lcgRand(rand_gen* gen) {
  return (
    abs((gen->seed = (gen->a * gen->seed + gen->c) % INT_MAX) >> 16) % 10
  ) / 10.0f;
}

/*
  lcgRandRange
  Generates a random number in the specified range.
  @param low Lower-bound
  @param high Higher-bound
  @return A random integer between the specified range.
*/
int lcgRandRange(rand_gen* gen, int low, int high) {
  return ((int)(lcgRand(gen) * 1000)) % (high + 1 - low) + low;
}

/*
  main
  Program entrypoint.
  @param argc Number of console arguments
  @param argv List of console arguments
  @return Exit status code
*/
int main(int argc, const char** argv) {
  rand_gen msRand = createMSRand(time(0));

  printf("Between 0 and 1:\n");
  for (int i = 0; i < 10; i++) {
    printf("%.2f\n", lcgRand(&msRand));
  }

  printf("Between 0 and 50:\n");
  for (int i = 0; i < 10; i++) {
    printf("%d\n", lcgRandRange(&msRand, 0, 50));
  }
  return 0;
}