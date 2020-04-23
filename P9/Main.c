/*
  Author: César Francisco Barraza Aguilar
  ID: A01176786
  Date: 12/Mar/2020
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

/*
  asciiBinaryToInt
  @param s String to convert to int.
  @return Integer conversion from binary string.
*/
int asciiBinaryToInt(const char* s) {
  int n = strlen(s);
  int res = 0;

  for (int i = 0; i < n; i++) {
    if (s[i] == '1') {
      res += pow(2, n - i - 1);
    }
  }

  return res;
}

/*
  asciiHexToInt
  @param s String to convert to int.
  @return Integer conversion from hex string.
*/
int asciiHexToInt(const char* s) {
  int n = strlen(s);
  int res = 0;

  for (int i = n - 1; i >= 0; i--) {
    int num = 0;
    if (s[i] >= '0' && s[i] <= '9') {
      num = (int)(s[i] - '0');
    } else if (s[i] >= 'A' && s[i] <= 'F') {
      num = (int)(s[i] - 'A') + 10;
    } else if (s[i] >= 'a' && s[i] <= 'f') {
      num = (int)(s[i] - 'a') + 10;
    } else {
      printf("Hex to Int conversion error! Invalid character!\n");
      break;
    }

    res += num * pow(16, n - i - 1);
  }

  return res;
}

/*
  asciiToDouble
  @param s String to convert to double.
  @return Double conversion from string.
*/
double asciiToDouble(const char* s) {
  int n = strlen(s);
  bool positive = true;
  int i = 0;
  char* str = malloc(n + 1);
  double res = 0;

  if (isdigit(s[0]) == 0 && s[0] != '+' && s[0] != '-') {
    free(str);
    return 0;
  }

  if (s[0] == '+') {
    i = 1;
  }

  if (s[0] == '-') {
    positive = false;
    i = 1;
  }

  for (; i < n; i++) {
    if (s[i] < '0' && s[i] > '9') {
      break;
    }

    str[i] = s[i];
  }
  str[i] = '\0';

  res = atof(str + 1);
  free(str);
  return positive ? res : res * -1;
}

/*
  main
  Program entrypoint.
  @param argc Number of console arguments
  @param argv List of console arguments
  @return Exit status code
*/
int main(int argc, const char** argv) {
  char s[9];
  printf("Enter a hexadecimal number: ");
  scanf("%s", s);
  
  printf("Your hexadecimal number to integer: %d\n", asciiHexToInt(s));
  return 0;
}