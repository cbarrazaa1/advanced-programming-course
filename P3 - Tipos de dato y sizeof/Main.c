/*
  Author: César Francisco Barraza Aguilar
  ID: A01176786
  Date: 18/Feb/2020
*/
#include <stdio.h>
#include <float.h>

/*
  getUserInput
  Gets the input needed for the program.
  @param varInt Pointer to store read int.
  @param varChar Pointer to store read characater.
  @param varDouble Pointer to store read double.
*/
void getUserInput(int* varInt, char* varChar, double* varDouble) {
  printf("Enter integer: ");
  scanf("%i", varInt);

  printf("Enter character: ");
  scanf(" %c", varChar);

  printf("Enter double: ");
  scanf("%lf", varDouble);
}

/*
  printOutput
  Prints the results using the input from the user.
  @param varInt Integer to use for result.
  @param varChar Character to use for result.
  @param varDouble Double to use for result.
*/
void printOutput(int varInt, char varChar, double varDouble) {
  printf(
    "Your integer <%i> storage size is %i bytes.\n", 
    varInt,
    sizeof(int)
  );
  printf(
    "Your char <%c> storage size is %i bytes. And I can read it as <%c> or as <%i>.\n",
    varChar,
    sizeof(char),
    varChar,
    varChar
  );
  printf(
    "Your double <%lf> storage size is %i bytes, I can read any number from 0 to %.10e in this data type.\n",
    varDouble,
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
  int varInt = 0;
  char varChar = 0;
  double varDouble = 0.0;

  getUserInput(&varInt, &varChar, &varDouble);
  printOutput(varInt, varChar, varDouble);
  return 0;
}