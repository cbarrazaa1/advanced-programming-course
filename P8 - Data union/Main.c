/*
  Author: César Francisco Barraza Aguilar
  ID: A01176786
  Date: 10/Mar/2020
*/
#include <stdio.h>
#include <float.h>
#include <string.h>

// Data union that allows ints, doubles or max-len 100 character strings.
typedef union data {
  int varInt;
  char varChar[100];
  double varDouble;
} data;

/*
  process
  Gets the input needed for the program and processes it.
  @param data Pointer to data union.
*/
void process(data* data) {
  printf("Enter integer: ");
  scanf("%i", &data->varInt);
  printf(
    "Your integer <%i> storage size is %i bytes.\n", 
    data->varInt,
    sizeof(int)
  );

  printf("Enter string: ");
  scanf("%s", &data->varChar);
  printf(
    "Your char <%s> storage size is %i bytes.\n",
    data->varChar,
    strlen(data->varChar),
    data->varChar,
    data->varChar
  );

  printf("Enter double: ");
  scanf("%lf", &data->varDouble);
  printf(
    "Your double <%lf> storage size is %i bytes, I can read any number from 0 to %.10e in this data type.\n",
    data->varDouble,
    sizeof(double),
    DBL_MAX
  );
}

/*
  main
  Program entrypoint.
  @param argc Number of console arguments
  @param argv List of console arguments
  @return Exit status code
*/
int main(int argc, const char** argv) {
  data data = {0};
  
  process(&data);
  return 0;
}