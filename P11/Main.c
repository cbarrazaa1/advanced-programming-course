/*
  Author: César Francisco Barraza Aguilar
  ID: A01176786
  Date: 24/Mar/2020
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
  asciiHEXToInt
  Converts a hexadecimal string to an integer using string formats.
  @param s String to convert to int.
  @return Integer conversion from hex string.
*/
int asciiHEXToInt(const char* s) {
  char aux[30];

  // validate the input
  for (int i = 0; i < strlen(s); i++) {
    if (!(
      (s[i] >= '0' && s[i] <= '9')
      || (s[i] >= 'A' && s[i] <= 'F')
      || (s[i] >= 'a' && s[i] <= 'f')
    )) {
      printf("Hex to Int conversion error! Invalid character!\n");
      return 0;
    }
  }

  // convert using format
  sprintf(aux, "%d", (int)strtol(s, NULL, 16));
  return atoi(aux);
}

/*
  asciiBINToInt
  Converts a binary string to an integer using positional calculations.
  @param s String to convert to int.
  @return Integer conversion from binary string.
*/
int asciiBINToInt(const char* s) {
  int n = strlen(s);
  int res = 0;

  for (int i = 0; i < n; i++) {
    if (s[i] != '0' && s[i] != '1') {
      printf("Bin to Int conversion error! Invalid character!\n");
      return res;
    }

    if (s[i] == '1') {
      res += pow(2, n - i - 1);
    }
  }

  return res;
}

/*
  asciiOCTToInt
  Converts an octal string to an integer using string format.
  @param s String to convert to int.
  @return Integer conversion from octal string.
*/
int asciiOCTToInt(const char* s) {
  char aux[30];

  // validate the input
  for (int i = 0; i < strlen(s); i++) {
    if (!(s[i] >= '0' && s[i] <= '7')) {
      printf("Oct to Int conversion error! Invalid character!\n");
      return 0;
    }
  }

  // convert using format
  sprintf(aux, "%d", (int)strtol(s, NULL, 8));
  return atoi(aux);
}

/*
  divideByTwo
  Divides a number by two using bitshifting.
  @param i Number to divide.
  @return The number divided by two.
*/
int divideByTwo(int i) {
  return i >> 1;
}

/*
  multByTwo
  Multiplies a number by two using bitshifting.
  @param i Number to multiply.
  @return The number multiplied by two.
*/
int multByTwo(int i) {
  return i << 1;
}

/*
  main
  Program entrypoint.
  @param argc Number of console arguments
  @param argv List of console arguments
  @return Exit status code
*/
int main(int argc, const char** argv) {
  char input = 0;
  char numStr[9];
  int num = 0;

  printf("Welcome to the converter and bits program.\n");
  
  while (input != '6') {
    printf("1) Convert Hex to Int number.\n");
    printf("2) Convert Bin to Int number.\n");
    printf("3) Convert Oct to Int number.\n");
    printf("4) Divide a number by two.\n");
    printf("5) Multiply a number by two.\n");
    printf("6) Exit.\n");
    printf("Enter option: ");
    scanf(" %c", &input);

    switch ((input - '0')) {
      case 1:
        printf("Enter hexadecimal number: ");
        scanf("%s", numStr);
        printf("%s Hex => %d Dec\n", numStr, asciiHEXToInt(numStr));
        break;
      case 2:
        printf("Enter binary number: ");
        scanf("%s", numStr);
        printf("%s Bin => %d Dec\n", numStr, asciiBINToInt(numStr));
        break;
      case 3:
        printf("Enter octal number: ");
        scanf("%s", numStr);
        printf("%s Oct => %d Dec\n", numStr, asciiOCTToInt(numStr));
        break;
      case 4:
        printf("Enter number to divide: ");
        scanf("%d", &num);
        printf("%d / 2 = %d\n", num, divideByTwo(num));
        break;
      case 5:
        printf("Enter number to multiply: ");
        scanf("%d", &num);
        printf("%d * 2 = %d\n", num, multByTwo(num));
        break;

      default:
        if (input != '6') {
          printf("Invalid input.\n");
        }
        break;
    }
  }

  return 0;
}