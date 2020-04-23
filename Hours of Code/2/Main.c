/*
  Author: César Francisco Barraza Aguilar
  ID: A01176786
  Date: 27/Mar/2020
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "Numbers.h"

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
  validateAgentID
  Valides that an agent ID is well formed.
  @param s String containing agent ID to validate.
  @return Whether the ID is valid or not.
*/
bool validateAgentID(const char* s) {
  if (strlen(s) != 13) {
    return false;
  }

  // check first 4 letters
  for (int i = 0; i < 4; i++) {
    if (!isalpha(s[i])) {
      return false;
    }
  }

  // check last 9 digits
  for (int i = 4; i < 13; i++) {
    if (!isdigit(s[i])) {
      return false;
    }
  }

  return true;
}

/*
  parseNumber
  Parses a number written textually to an integer.
  @param Number to parse.
  @return Numerical representation of the string number.
*/
int parseNumber(const char* s) {
  int res = 0;
  int index = isInOnes(s);

  // check if in ones
  if (index != -1) {
    return mapOnesToNumber(index);
  }

  // check if tens
  index = isInTens(s);
  if (index != -1) {
    return mapTensToNumber(index);
  }

  // check if special character
  index = isInSpecial(s);
  if (index != -1) {
    return mapSpecialToNumber(index);
  }

  // check if hundreds
  index = isInHundreds(s);
  if (index != -1) {
    return mapHundredsToNumber(index);
  }

  // check if complex (tens + ones)
  char str[30] = "";
  strcpy(str, s);
  char* ten = strtok(str, " y ");
  index = isInTens(ten);
  if (index != -1) {
    res += mapTensToNumber(index);
  } else {
    return 0;
  }

  char* one = str + strlen(ten) + 3;
  index = isInOnes(one);
  if (index != -1) {
    res += mapOnesToNumber(index);
  } else {
    return 0;
  }

  return res;
}

/*
  getNumbers
  Reads the numbers from the user.
  @return The 9 digit string containing the numbers.
*/
char* getNumbers() {
  char* res = malloc(10);
  printf("Escribe numeros separados por coma hasta llenar 9 digitos (del 0 al 100, numeros invalidos se consideraran como 0):\n");
  getchar();
  int resPos = 0;

  for (;;) {
    char* input = extremelyLargeString();
    int size = strlen(input);
    char* token = strtok(input, ",");
    int pos = 0;
    bool hadSpace = false;
    resPos = 0;
    
    while (token != NULL && pos <= size) {
      // ignore possible initial space
      if (token[0] == ' ') {
        hadSpace = true;
        token++;
      }

      // parse number and convert into digits
      int num = parseNumber(token);
      char strNum[3] = "";
      itoa(num, strNum, 10);
      for (int i = 0; i < strlen(strNum); i++) {
        res[resPos++] = strNum[i];
      }

      // if we have 9 digits, we're done
      if (resPos > 9) {
        resPos = 9;
        break;
      }

      // move back if we ignored space
      if (hadSpace) {
        token--;
        hadSpace = false;
      }

      // look for next token
      pos += strlen(token) + 1;
      token = strtok(input + pos, ",");
    }

    free(input);

    if (resPos < 9) {
      printf("Debes completar al menos 9 digitos.\n");
    } else {
      break;
    }
  }
  
  res[resPos] = '\0';
  return res;
}

/*
  randRange
  Generates a random number in a range, inclusive.
  @param low Lower limit
  @param high Higher limit
  @return Random number between [low, high]
*/
int randRange(int low, int high) {
  return (rand() % (high - low + 1) + low);
}

/*
  generateNewID
  Generates a new agent ID using a set of digits.
  @param digits Digits to use to generate the ID.
  @param id The string where the generated id will be stored.
*/
void generateNewID(char* digits, char* id) {
  int n = strlen(digits);

  for (int i = 0; i < n; i++) {
    int index = randRange(0, n - 1);
    while (index == i) {
      index = randRange(0, n - 1);
    }
    char temp = digits[i];
    digits[i] = digits[index];
    digits[index] = temp;
  }

  strcpy(id + 4, digits);
}

/*
  main
  Program entrypoint.
  @param argc Number of console arguments
  @param argv List of console arguments
  @return Exit status code
*/
int main(int argc, const char** argv) {
  srand(time(0));
  char id[14] = "";

  printf("Escribe tu ID actual: ");
  scanf("%s", id);

  while (!validateAgentID(id)) {
    printf("ID incorrecto. Debe estar formado por 4 letras seguidas por 9 digitos: ");
    scanf("%s", id);
  }

  char* digits = getNumbers();
  printf("Numero a utilizar para generar nuevo ID: %s\n", digits);
  generateNewID(digits, id);
  printf("Muchas gracias, el nuevo ID es: %s\n", id);
  free(digits);

  return 0;
}