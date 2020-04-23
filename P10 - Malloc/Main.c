/*
  Author: César Francisco Barraza Aguilar
  ID: A01176786
  Date: 12/Mar/2020
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  extremelyLargeString
  Reads a dynamic size string from input.
  @return The read string.
*/
char* extremelyLargeString() {
  int size = 10, curr = 0;
  char* str = malloc(sizeof(char) + size);
  char input = 0;

  for (;;) {
    input = getchar();

    if (input == '\n') {
      break;
    }

    str[curr++] = input;
    
    // resize if larger
    if (curr == size) {
      size *= 2;
      str = realloc(str, size);
    }
  }

  str[curr] = '\0';

  return str;
}

/*
  main
  Program entrypoint.
  @param argc Number of console arguments
  @param argv List of console arguments
  @return Exit status code
*/
int main(int argc, const char** argv) {
  char* str = NULL;

  printf("Enter a string: ");
  str = extremelyLargeString();
  printf("Your string: %s", str);
  
  free(str);
  return 0;
}