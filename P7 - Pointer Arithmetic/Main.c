/*
  Author: César Francisco Barraza Aguilar
  ID: A01176786
  Date: 22/Feb/2020
*/
#include <stdio.h>
#include <string.h>

/*
  getUserInput
  Gets the string to be converted.
  @param str Pointer to string to store the read input.
*/
void getUserInput(char* str) {
  printf("Enter a string: ");
  fgets(str, 99, stdin);
}

/*
  convertString
  Converts a string using the required mapping table.
  @param str Pointer to string to convert.
*/
void convertString(char* str) {
  for (char* c = str; c < (str + strlen(str)); c++) {
    if (*c == 'a') {
      *c = '4';
    } else if (*c == 'e') {
      *c = '3';
    } else if (*c == 'i') {
      *c = '1';
    } else if (*c == 'o') {
      *c = '0';
    } else if (*c == 'u') {
      *c = '2';
    }
  }
}

/*
  printOutput
  Prints the converted string to the user.
  @param str Pointer to string to print to the user.
*/
void printOutput(char* str) {
  convertString(str);
  printf("Converted string: %s", str);
}

/*
  main
  Program entrypoint.
  @param argc Number of console arguments
  @param argv List of console arguments
  @return Exit status code
*/
int main(int argc, const char** argv) {
  char str[100];
  getUserInput(str);
  printOutput(str);
  return 0;
}